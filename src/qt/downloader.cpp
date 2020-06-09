#include "qt/downloader.h"
#include <univalue.h>
#include <rpc/net.cpp>
#include <netaddress.h>
#include <netaddress.cpp>


#include <QNetworkProxy>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QMessageBox>
#include <QFile>
#include <QDir>
#include <QDebug>


Downloader::Downloader(QObject* parent) :
    BaseClass(parent)
{
    connect(m_manager, &QNetworkAccessManager::finished, this, &Downloader::onReply);
}

Downloader::~Downloader(){}


bool Downloader::get(const QString& targetFolder, QUrl& url, bool& proxy)
{    
    if (targetFolder.isEmpty() || url.isEmpty())
    {
        return false;
    }
    m_targetfolder = targetFolder;
    m_proxy = proxy;
    m_manager = new QNetworkAccessManager();
    m_url = url;

    m_file = new QFile(targetFolder + QDir::separator() + url.fileName());
    if (!m_file->open(QIODevice::WriteOnly))
    {
        delete m_file;
        m_file = nullptr;
        return false;
    }  
    requestAborted = false;

    //Set Proxy
    if(proxy)
    {
        QNetworkProxy proxy;
        proxy.setType(QNetworkProxy::Socks5Proxy);

        for(int n=0; n<NET_MAX; ++n)
        {
            enum Network network = static_cast<enum Network>(n);
            if(network == NET_UNROUTABLE || network == NET_INTERNAL)
                continue;
            proxyType _proxy;
            GetProxy(network, _proxy);
            std::string hostname;
            std::string port;
            if (_proxy.IsValid())
            {
                hostname = _proxy.proxy.ToStringIP();
                port = _proxy.proxy.ToStringPort();
            }
            proxy.setHostName(QString::fromStdString(hostname));
            proxy.setPort(QString::fromStdString(port).toShort());
        }

        m_manager->setProxy(proxy);
     }

    QNetworkRequest request(url);
    request.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);
    request.setRawHeader("Accept-Encoding", "gzip");

    LogPrint(BCLog::DEEPSYNC, "DeepSync Blockchain Download Requested: Url: %s, Proxy: %s\n", url.toString().toStdString(), proxy ? "true" : "false");

    m_currentReply = m_manager->get(request);
    SetDataName(url.fileName());

    connect(m_currentReply, &QNetworkReply::metaDataChanged, this, &Downloader::replyMetaDataChanged);
    connect(m_currentReply, &QNetworkReply::readyRead, this, &Downloader::onReadyRead);
    connect(m_currentReply, &QNetworkReply::downloadProgress, this, &Downloader::updateDownloadProgress);
    connect(m_currentReply, &QNetworkReply::finished, this, &Downloader::onFinished);
    connect(m_currentReply, &QNetworkReply::finished, this, &Downloader::Finished);

    return true;
}

void Downloader::replyMetaDataChanged() {
    size = m_currentReply->header(QNetworkRequest::ContentLengthHeader).toLongLong();
}

void Downloader::onReadyRead()
{
    if (m_file)
    {
        m_file->write(m_currentReply->readAll());
    }
}

void Downloader::cancelDownload()
{
    requestAborted = true;
    if (m_currentReply->isRunning())
    {
        m_currentReply->abort();
    }
}

void Downloader::onReply(QNetworkReply* reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        m_file->flush();
        m_file->close();
    }
    else
    {
        m_file->remove();
    }

    delete m_file;
    m_file = nullptr;
    reply->deleteLater();
}

void Downloader::SetDataName(QString name)
{
    fileName = name;
}

QString Downloader::getDataName()
{
    return fileName;
}

qint64 Downloader::getSize()
{
    return size;
}

void Downloader::Finished()
{
    // when canceled
    if (requestAborted) {
        if (m_file) {
            m_file->close();
            m_file->remove();
            delete m_file;
            m_file = 0;
        }
        m_currentReply->abort();
        return;
    }

    // download finished normally
    if(m_file)
    {
        m_file->flush();
        m_file->close();
    }

    m_currentReply->abort();
    delete m_file;
}

