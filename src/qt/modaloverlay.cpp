// Copyright (c) 2016-2017 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <qt/modaloverlay.h>
#include <qt/forms/ui_modaloverlay.h>

#include <qt/guiutil.h>
#include <qt/clientmodel.h>

#include <chainparams.h>
#include <qt/platformstyle.h>
#include <init.h>  // For StartShutdown

#include <QResizeEvent>
#include <QPropertyAnimation>

ModalOverlay::ModalOverlay(const PlatformStyle *_platformStyle, QWidget *parent) :
QWidget(parent),
ui(new Ui::ModalOverlay),
bestHeaderHeight(0),
bestHeaderDate(QDateTime()),
layerIsVisible(false),
userClosed(false),
platformStyle(_platformStyle)
{
    ui->setupUi(this);
    connect(ui->quickSyncButton, &QPushButton::clicked, this, &ModalOverlay::onQuickSyncClicked);
    connect(ui->cancelPushButton, &QPushButton::clicked, this, &ModalOverlay::onCancelButtonClicked);
    connect(ui->closeButton, SIGNAL(clicked()), this, SLOT(closeClicked()));
    connect(ui->quicksyncoptionsButton, &QPushButton::clicked,this,&ModalOverlay::onQuickSyncOptionsClicked);
    connect(ui->editServerAddressButton,&QPushButton::clicked, this, &ModalOverlay::onEditServerAddressButton);
    connect(ui->proxycheckBox, &QCheckBox::stateChanged, this, &ModalOverlay::onProxyActivated);
    connect(&m_downloader, &Downloader::updateDownloadProgress, this, &ModalOverlay::onUpdateProgress);
    connect(&m_downloader, &Downloader::onFinished, this, &ModalOverlay::onDownloadFinished);
    connect(&quickS, &GUIUtil::QuickSync::updateDeflateProgress, this, &ModalOverlay::onProgessBarUpdated,Qt::QueuedConnection);
    connect(&quickS, &GUIUtil::QuickSync::deflateFinished, this, &ModalOverlay::onDeflateFinished,Qt::QueuedConnection);
    connect(&quickS, &GUIUtil::QuickSync::untarFinished, this, &ModalOverlay::onUntarFinished, Qt::QueuedConnection);

    if (parent) {
        parent->installEventFilter(this);
        raise();
    }
    ui->downloadProgressBar->setAlignment(Qt::AlignCenter);
    ui->downloadProgressBar->setValue(0);
    ui->bootstrapServerAddressEdit->setText(blockchain_url.toString());
    ui->proxycheckBox->setChecked(true);
    blockProcessTime.clear();
    deflationrequested = true;
    setVisible(false);

    //QuickSync Configuration
    showQuickSyncOptions = false;


    // DeepOnion: Theme
    ui->contentWidget->setStyleSheet(platformStyle->getThemeManager()->getCurrent()->getStyleSheet());
    ui->warningIcon->setIcon(platformStyle->SingleColorIcon(platformStyle->getThemeManager()->getCurrent()->getWarningIco()));
    ui->warningIcon->setStyleSheet(platformStyle->getThemeManager()->getCurrent()->getQFrameGeneralStyle());
}

ModalOverlay::~ModalOverlay()
{
    delete ui;
}

bool ModalOverlay::eventFilter(QObject * obj, QEvent * ev) {
    if (obj == parent()) {
        if (ev->type() == QEvent::Resize) {
            QResizeEvent * rev = static_cast<QResizeEvent*>(ev);
            resize(rev->size());
            if (!layerIsVisible)
                setGeometry(0, height(), width(), height());

        }
        else if (ev->type() == QEvent::ChildAdded) {
            raise();
        }
    }
    return QWidget::eventFilter(obj, ev);
}

//! Tracks parent widget changes
bool ModalOverlay::event(QEvent* ev) {
    if (ev->type() == QEvent::ParentAboutToChange) {
        if (parent()) parent()->removeEventFilter(this);
    }
    else if (ev->type() == QEvent::ParentChange) {
        if (parent()) {
            parent()->installEventFilter(this);
            raise();
        }
    }
    return QWidget::event(ev);
}

void ModalOverlay::setKnownBestHeight(int count, const QDateTime& blockDate)
{
    if (count > bestHeaderHeight) {
        bestHeaderHeight = count;
        bestHeaderDate = blockDate;
    }
}

void ModalOverlay::tipUpdate(int count, const QDateTime& blockDate, double nVerificationProgress)
{
    if(nVerificationProgress > 0.7)
        showQuickSync = false;
    else
        showQuickSync = true;
    updateQuickSyncVisibility();


    QDateTime currentDate = QDateTime::currentDateTime();

    // keep a vector of samples of verification progress at height
    blockProcessTime.push_front(qMakePair(currentDate.toMSecsSinceEpoch(), nVerificationProgress));

    // show progress speed if we have more then one sample
    if (blockProcessTime.size() >= 2) {
        double progressDelta = 0;
        double progressPerHour = 0;
        qint64 timeDelta = 0;
        qint64 remainingMSecs = 0;
        double remainingProgress = 1.0 - nVerificationProgress;
        for (int i = 1; i < blockProcessTime.size(); i++) {
            QPair<qint64, double> sample = blockProcessTime[i];

            // take first sample after 500 seconds or last available one
            if (sample.first < (currentDate.toMSecsSinceEpoch() - 500 * 1000) || i == blockProcessTime.size() - 1) {
                progressDelta = blockProcessTime[0].second - sample.second;
                timeDelta = blockProcessTime[0].first - sample.first;
                progressPerHour = progressDelta / (double) timeDelta * 1000 * 3600;
                remainingMSecs = (progressDelta > 0) ? remainingProgress / progressDelta * timeDelta : -1;
                break;
            }
        }
        // show progress increase per hour
        ui->progressIncreasePerH->setText(QString::number(progressPerHour * 100, 'f', 2)+"%");

        // show expected remaining time
        if(remainingMSecs >= 0) {	
            ui->expectedTimeLeft->setText(GUIUtil::formatNiceTimeOffset(remainingMSecs / 1000.0));
        } else {
            ui->expectedTimeLeft->setText(QObject::tr("unknown"));
        }

        static const int MAX_SAMPLES = 5000;
        if (blockProcessTime.count() > MAX_SAMPLES) {
            blockProcessTime.remove(MAX_SAMPLES, blockProcessTime.count() - MAX_SAMPLES);
        }
    }

    // show the last block date
    ui->newestBlockDate->setText(blockDate.toString());

    // show the percentage done according to nVerificationProgress
    ui->percentageProgress->setText(QString::number(nVerificationProgress*100, 'f', 2)+"%");
    ui->progressBar->setValue(nVerificationProgress*100);

    if (!bestHeaderDate.isValid())
        // not syncing
        return;

    // estimate the number of headers left based on nPowTargetSpacing
    // and check if the gui is not aware of the best header (happens rarely)
    int estimateNumHeadersLeft = bestHeaderDate.secsTo(currentDate) / Params().GetConsensus().nPowTargetSpacing;
    bool hasBestHeader = bestHeaderHeight >= count;

    // show remaining number of blocks
    if (estimateNumHeadersLeft < HEADER_HEIGHT_DELTA_SYNC && hasBestHeader) {
        ui->numberOfBlocksLeft->setText(QString::number(bestHeaderHeight - count));
    } else {
        ui->numberOfBlocksLeft->setText(tr("Unknown. Syncing Headers (%1)...").arg(bestHeaderHeight));
        ui->expectedTimeLeft->setText(tr("Unknown..."));
    }
}

QString ModalOverlay::getQuickSyncStatus()
{
    switch(quickSyncStatus){

        case QuickSyncStatus::CANCELED:
            return QString("Canceled");

        case QuickSyncStatus::DOWNLOADING:
            return QString("Downloading...");

        case QuickSyncStatus::DECODING:
            return QString("Decoding...");

        case QuickSyncStatus::EXTRACTING:
            return QString("Extracting...");

        case QuickSyncStatus::PREPARING:
            return QString("Preparing...");

        case QuickSyncStatus::TIMEOUT:
            return QString("Timout...");

        default:
            return QString("");
    }
}

void ModalOverlay::toggleVisibility()
{
    showHide(layerIsVisible, true);
    if (!layerIsVisible)
        userClosed = true;
}

void ModalOverlay::showHide(bool hide, bool userRequested)
{
    if ( (layerIsVisible && !hide) || (!layerIsVisible && hide) || (!hide && userClosed && !userRequested))
        return;

    if (!isVisible() && !hide)
        setVisible(true);

    setGeometry(0, hide ? 0 : height(), width(), height());

    QPropertyAnimation* animation = new QPropertyAnimation(this, "pos");
    animation->setDuration(300);
    animation->setStartValue(QPoint(0, hide ? 0 : this->height()));
    animation->setEndValue(QPoint(0, hide ? this->height() : 0));
    animation->setEasingCurve(QEasingCurve::OutQuad);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
    layerIsVisible = !hide;
}

void ModalOverlay::closeClicked()
{
    showHide(true);
    userClosed = true;
}

void ModalOverlay::refreshStyle()
{
    // DeepOnion: Theme
    ui->contentWidget->setStyleSheet(platformStyle->getThemeManager()->getCurrent()->getStyleSheet());
    ui->warningIcon->setIcon(platformStyle->SingleColorIcon(platformStyle->getThemeManager()->getCurrent()->getWarningIco()));
    ui->warningIcon->setStyleSheet(platformStyle->getThemeManager()->getCurrent()->getQFrameGeneralStyle());
}

void ModalOverlay::onQuickSyncClicked()
{
    setNetworkStatus(false);
    quickSyncStatus = QuickSyncStatus::PREPARING;
    ui->downloadProgressBar->setFormat(getQuickSyncStatus());

    //Create temp folder for downloading
    tempquickSyncDir= GetDataDir() / fs::unique_path();
    fs::create_directory(tempquickSyncDir);

    m_downloader.get(GUIUtil::boostPathToQString(tempquickSyncDir), blockchain_url, proxyActivated);
    downloadStartTime = std::chrono::high_resolution_clock::now();
    quickSyncStatus = QuickSyncStatus::DOWNLOADING;
}

void ModalOverlay::onCancelButtonClicked()
{
    m_downloader.cancelDownload();
    fs::remove_all(tempquickSyncDir);
    ui->downloadProgressBar->setMaximum(100);
    ui->downloadProgressBar->setValue(0);
    quickSyncStatus = QuickSyncStatus::CANCELED;
    ui->downloadProgressBar->setFormat(getQuickSyncStatus());
    deflationrequested = false;
    //Free Network
    setNetworkStatus(true);
}

void ModalOverlay::onUpdateProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    ui->downloadProgressBar->setMaximum(bytesTotal);
    ui->downloadProgressBar->setValue(bytesReceived);
    double downloaded_Size = (double)bytesReceived;
    double total_Size = (double)bytesTotal;
    double progress = (downloaded_Size/total_Size) * 100;

    auto elapsedTime = std::chrono::high_resolution_clock::now()-downloadStartTime;
    auto remainingTime = (elapsedTime.count() * total_Size/downloaded_Size)/ 1000000000.0;
    int hours;
    int minutes;
    int seconds;
    if(remainingTime > (60 *60))
    {
        hours = remainingTime/(60*60);
        minutes = (int)remainingTime%(60*60)/60;
        seconds= (int)remainingTime%60;
        ui->downloadProgressBar->setFormat(getQuickSyncStatus()+QString::number(progress,'f',1)+"% ("+QString::number(hours,'f',0)+"h "+QString::number(minutes,'f',0)+ "m " + QString::number(seconds,'f',0) +"s)");
    }
    else if(remainingTime > 60)
    {

        minutes = remainingTime/60;
        seconds= (int)remainingTime%60;
        ui->downloadProgressBar->setFormat(getQuickSyncStatus()+QString::number(progress,'f',1)+"% ("+QString::number(minutes,'f',0)+ "m " + QString::number(seconds,'f',0) +"s)");
    }
    else
        ui->downloadProgressBar->setFormat(getQuickSyncStatus()+QString::number(progress,'f',1)+"% ("+QString::number(remainingTime,'f',0) +"s)");

}

void ModalOverlay::onDownloadFinished()
{
    if(deflationrequested)
    {
        ui->downloadProgressBar->setFormat(getQuickSyncStatus());
        deflationrequested = false;
        prepareDeflateData(m_downloader.getDataName());
    }
}

void ModalOverlay::prepareDeflateData(QString file)
{
      quickSyncStatus = QuickSyncStatus::DECODING;
      std::string filename = file.toStdString();
      fs::path datadir2= tempquickSyncDir / fs::path(filename);

      size_t lastindex = filename.find_last_of(".");
      std::string rawname = filename.substr(0, lastindex);
      tardatadir= tempquickSyncDir / fs::path(rawname);

      //Deflate in seperate thread to obtain UI responsive
      new std::thread(&GUIUtil::QuickSync::deflate,&quickS,datadir2,tardatadir);
}

void ModalOverlay::untar()
{
    FILE * pFile;
    pFile = fopen (tardatadir.c_str() ,"rb");
    std::string targetpath = GetDataDir().string() + "/";
    //Untar in seperate thread to obtain UI responsive
    new std::thread(&GUIUtil::QuickSync::untar,&quickS,pFile, tardatadir.c_str(),targetpath);
}

void ModalOverlay::onProgessBarUpdated(qint64 processedData, qint64 data)
{
    ui->downloadProgressBar->setMaximum(data);
    ui->downloadProgressBar->setValue(processedData);
    double processed = double(processedData);
    double total_Size = double(data);
    double progress = (processed/total_Size) * 100;
    ui->downloadProgressBar->setFormat(getQuickSyncStatus()+QString::number(progress,'f',1)+"%");

}

void ModalOverlay::onDeflateFinished()
{
    quickSyncStatus = QuickSyncStatus::EXTRACTING;
    ui->downloadProgressBar->setFormat(getQuickSyncStatus());
    untar();
}

void ModalOverlay::onUntarFinished()
{
    fs::remove_all(tempquickSyncDir);
    //Quicksync data is downloaded and untard
    //Announce it and prepare for closing wallet for restart
    quickSyncFinishedMessageBox = new QMessageBox;
    quickSyncFinishedMessageBox->setWindowTitle("QuickSync is prepared for wallet restart");
    quickSyncFinishedMessageBox->setText("The wallet will close now. Restart the wallet to initialize the blockchain!");
    quickSyncFinishedMessageBox->setStandardButtons(QMessageBox::Yes);

    if(quickSyncFinishedMessageBox->exec() == QMessageBox::Yes)
    {
        StartShutdown();
    }
}
void ModalOverlay::setClientModel(ClientModel *clientmodel)
{
    this->clientmodel = clientmodel;
    // Deactivate network for quick sync operations
    connect(this,SIGNAL(setNetworkStatus(bool)), clientmodel, SLOT(updateNetwork(bool)));
}

void ModalOverlay::onQuickSyncOptionsClicked()
{
    if(showQuickSyncOptions)
        showQuickSyncOptions = false;
    else
        showQuickSyncOptions = true;

    updateQuickSyncVisibility();
}

void ModalOverlay::onEditServerAddressButton()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Set Address"),
                                            tr("Address name:"), QLineEdit::Normal,
                                            blockchain_url.toString(), &ok);
    if (ok && !text.isEmpty())
    {
        ui->bootstrapServerAddressEdit->setText(text);
        blockchain_url = text;
     }
}

void ModalOverlay::onProxyActivated(int state)
{
    if(state == 0)
        setProxyActivated(false);
    else if(state == 2)
        setProxyActivated(true);
}

bool ModalOverlay::getProxyActivated()
{
    return proxyActivated;
}

void ModalOverlay::setProxyActivated(bool value)
{
    proxyActivated = value;
}
void ModalOverlay::updateQuickSyncVisibility()
{
    if(!showQuickSync)
    {
        ui->quickSyncButton->hide();
        ui->downloadProgressBar->hide();
        ui->quicksyncoptionsButton->hide();
        ui->cancelPushButton->hide();

        ui->bootstrapServerAddressEdit->hide();
        ui->proxycheckBox->hide();
        ui->editServerAddressButton->hide();
    }
    else
    {
        ui->quickSyncButton->show();
        ui->downloadProgressBar->show();
        ui->quicksyncoptionsButton->show();
        ui->cancelPushButton->show();

        if(showQuickSyncOptions)
        {
            ui->bootstrapServerAddressEdit->show();
            ui->proxycheckBox->show();
            ui->editServerAddressButton->show();
        }
        else
        {
            ui->bootstrapServerAddressEdit->hide();
            ui->proxycheckBox->hide();
            ui->editServerAddressButton->hide();
        }
    }

}
