// Copyright (c) 2016-2017 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <qt/forms/ui_modaloverlay.h>
#include <qt/modaloverlay.h>

#include <qt/clientmodel.h>
#include <qt/guiutil.h>

#include <chainparams.h>
#include <init.h> // For StartShutdown
#include <qt/platformstyle.h>

#include <QPropertyAnimation>
#include <QResizeEvent>

//Threshold for enabling deepsync
const double DEEPSYNC_THRESH = 0.7;

ModalOverlay::ModalOverlay(const PlatformStyle* _platformStyle, QWidget* parent) : QWidget(parent),
                                                                                   ui(new Ui::ModalOverlay),
                                                                                   bestHeaderHeight(0),
                                                                                   bestHeaderDate(QDateTime()),
                                                                                   layerIsVisible(false),
                                                                                   userClosed(false),
                                                                                   platformStyle(_platformStyle)
{
    ui->setupUi(this);
    connect(ui->deepSyncButton, &QPushButton::clicked, this, &ModalOverlay::onDeepSyncClicked);
    connect(ui->cancelPushButton, &QPushButton::clicked, this, &ModalOverlay::onCancelButtonClicked);
    connect(ui->closeButton, SIGNAL(clicked()), this, SLOT(closeClicked()));
    connect(ui->deepsyncoptionsButton, &QPushButton::clicked, this, &ModalOverlay::onDeepSyncOptionsClicked);
    connect(ui->editServerAddressButton, &QPushButton::clicked, this, &ModalOverlay::onEditServerAddressButton);
    connect(ui->proxycheckBox, &QCheckBox::stateChanged, this, &ModalOverlay::onProxyActivated);
    connect(&m_downloader, &Downloader::updateDownloadProgress, this, &ModalOverlay::onUpdateProgress);
    connect(&m_downloader, &Downloader::onFinished, this, &ModalOverlay::onDownloadFinished);
    //connect(&deepS, &GUIUtil::DeepSync::updateInflateProgress, this, &ModalOverlay::onProgessBarUpdated,Qt::QueuedConnection);
    connect(&deepS, &GUIUtil::DeepSync::inflateFinished, this, &ModalOverlay::onInflateFinished, Qt::QueuedConnection);

    if (parent) {
        parent->installEventFilter(this);
        raise();
    }
    refreshStyle();
    ui->downloadProgressBar->setAlignment(Qt::AlignCenter);
    ui->downloadProgressBar->setValue(0);
    ui->downloadProgressBar->setTextVisible(true);
    ui->downloadProgressBar->show();

    ui->bootstrapServerAddressEdit->setText(blockchain_url.toString());
    ui->proxycheckBox->setChecked(true);
    blockProcessTime.clear();
    deflationrequested = true;
    setVisible(false);

    //DeepSync Configuration
    showDeepSyncOptions = false;

    // DeepOnion: Theme
    ui->contentWidget->setStyleSheet(platformStyle->getThemeManager()->getCurrent()->getStyleSheet());
    ui->warningIcon->setIcon(platformStyle->SingleColorIcon(platformStyle->getThemeManager()->getCurrent()->getWarningIco()));
    ui->warningIcon->setStyleSheet(platformStyle->getThemeManager()->getCurrent()->getQFrameGeneralStyle());
}

ModalOverlay::~ModalOverlay()
{
    delete ui;
}

bool ModalOverlay::eventFilter(QObject* obj, QEvent* ev)
{
    if (obj == parent()) {
        if (ev->type() == QEvent::Resize) {
            QResizeEvent* rev = static_cast<QResizeEvent*>(ev);
            resize(rev->size());
            if (!layerIsVisible)
                setGeometry(0, height(), width(), height());

        } else if (ev->type() == QEvent::ChildAdded) {
            raise();
        }
    }
    return QWidget::eventFilter(obj, ev);
}

//! Tracks parent widget changes
bool ModalOverlay::event(QEvent* ev)
{
    if (ev->type() == QEvent::ParentAboutToChange) {
        if (parent()) parent()->removeEventFilter(this);
    } else if (ev->type() == QEvent::ParentChange) {
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
    if (nVerificationProgress > DEEPSYNC_THRESH)
        showDeepSync = false;
    else
        showDeepSync = true;

    updateDeepSyncVisibility();


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
                progressPerHour = progressDelta / (double)timeDelta * 1000 * 3600;
                remainingMSecs = (progressDelta > 0) ? remainingProgress / progressDelta * timeDelta : -1;
                break;
            }
        }
        // show progress increase per hour
        ui->progressIncreasePerH->setText(QString::number(progressPerHour * 100, 'f', 2) + "%");

        // show expected remaining time
        if (remainingMSecs >= 0) {
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
    ui->percentageProgress->setText(QString::number(nVerificationProgress * 100, 'f', 2) + "%");
    ui->progressBar->setValue(nVerificationProgress * 100);

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

QString ModalOverlay::getDeepSyncStatus()
{
    switch (deepSyncStatus) {
    case DeepSyncStatus::CANCELED:
        return QString("Canceled");

    case DeepSyncStatus::DOWNLOADING:
        return QString("Downloading...");

    case DeepSyncStatus::DECODING:
        return QString("Decoding...");

    case DeepSyncStatus::EXTRACTING:
        return QString("Extracting...");

    case DeepSyncStatus::PREPARING:
        return QString("Preparing...");

    case DeepSyncStatus::TIMEOUT:
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
    if ((layerIsVisible && !hide) || (!layerIsVisible && hide) || (!hide && userClosed && !userRequested))
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
    ui->downloadProgressBar->setStyleSheet(platformStyle->getThemeManager()->getCurrent()->getStatusBarBackgroundColor());
}

void ModalOverlay::onDeepSyncClicked()
{
    QString cstatus = getDeepSyncStatus();
    if (cstatus != "" && cstatus != "Canceled")
        return;
    setNetworkStatus(false);
    deflationrequested = true;
    deepSyncStatus = DeepSyncStatus::PREPARING;
    ui->downloadProgressBar->setFormat(getDeepSyncStatus());

    //Create temp folder for downloading
    tempdeepSyncDir = GetDataDir() / fs::unique_path();
    fs::create_directory(tempdeepSyncDir);

    LogPrint(BCLog::DEEPSYNC, "Starting deepsync download thread\n");
    m_downloader.get(GUIUtil::boostPathToQString(tempdeepSyncDir), blockchain_url, proxyActivated);
    downloadStartTime.start();
    deepSyncStatus = DeepSyncStatus::DOWNLOADING;
}

void ModalOverlay::onCancelButtonClicked()
{
    LogPrint(BCLog::DEEPSYNC, "DeepSync canceled.\n");

    QString cstring = getDeepSyncStatus();
    if (deepSyncStatus == DeepSyncStatus::CANCELED || cstring == "")
        return;
    deflationrequested = false;
    if (deepSyncStatus != DeepSyncStatus::PREPARING)
        m_downloader.cancelDownload();
    if (fs::is_directory(tempdeepSyncDir))
        fs::remove_all(tempdeepSyncDir);
    ui->downloadProgressBar->setValue(0);
    deepSyncStatus = DeepSyncStatus::CANCELED;
    ui->downloadProgressBar->setFormat(getDeepSyncStatus());


    //Free Network
    setNetworkStatus(true);
}

void ModalOverlay::onUpdateProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    ui->downloadProgressBar->setMaximum(bytesTotal);
    ui->downloadProgressBar->setValue(bytesReceived);
    double downloaded_Size = (double)bytesReceived;
    double total_Size = (double)bytesTotal;
    double progress = (downloaded_Size / total_Size) * 100;
    auto elapsedTime = downloadStartTime.elapsed();
    auto allTimeForDownloading = elapsedTime * total_Size / downloaded_Size;
    double remainingTime = (allTimeForDownloading - elapsedTime) / 1000;
    unsigned int hours;
    unsigned int minutes;
    unsigned int seconds;

    ui->downloadProgressBar->setTextVisible(true);
    if (remainingTime > (60 * 60)) {
        hours = remainingTime / (60 * 60);
        minutes = (int)remainingTime % (60 * 60) / 60;
        seconds = (int)remainingTime % 60;
        ui->downloadProgressBar->setFormat(getDeepSyncStatus() + QString::number(progress, 'f', 1) + "% (" + QString::number(hours, 'f', 0) + "h " + QString::number(minutes, 'f', 0) + "m " + QString::number(seconds, 'f', 0) + "s)");
    } else if (remainingTime > 60) {
        minutes = remainingTime / 60;
        seconds = (int)remainingTime % 60;
        ui->downloadProgressBar->setFormat(getDeepSyncStatus() + QString::number(progress, 'f', 1) + "% (" + QString::number(minutes, 'f', 0) + "m " + QString::number(seconds, 'f', 0) + "s)");
    } else
        ui->downloadProgressBar->setFormat(getDeepSyncStatus() + QString::number(progress, 'f', 1) + "% (" + QString::number(remainingTime, 'f', 0) + "s)");
}

void ModalOverlay::onDownloadFinished()
{
    if (deflationrequested) {
        ui->downloadProgressBar->setFormat(getDeepSyncStatus());
        deflationrequested = false;
        prepareInflateData(m_downloader.getDataName());
    }
}

void ModalOverlay::prepareInflateData(QString file)
{
    deepSyncStatus = DeepSyncStatus::DECODING;
    ui->downloadProgressBar->setFormat(getDeepSyncStatus());
    std::string filename = file.toStdString();
    fs::path datadir2 = tempdeepSyncDir / fs::path(filename);

    size_t lastindex = filename.find_last_of(".");
    std::string rawname = filename.substr(0, lastindex);
    tardatadir = tempdeepSyncDir / fs::path(rawname);

    //inflate in seperate thread to obtain UI responsive
    new std::thread(&GUIUtil::DeepSync::inf, &deepS, datadir2, tardatadir);
}

void ModalOverlay::onInflateFinished()
{
    deepSyncStatus = DeepSyncStatus::EXTRACTING;
    ui->downloadProgressBar->setFormat(getDeepSyncStatus());
#ifdef WIN32
    std::string tpath = GetDataDir().string() + "\\";
#else
    std::string tpath = GetDataDir().string() + "/";
#endif

    //Prepare info data for Main Application to access when closing
    clientmodel->setDSUntaringRequested(true);
    clientmodel->setDeepSyncUntarInfo(tardatadir, tpath, tempdeepSyncDir);

    deepSyncFinishedMessageBox = new QMessageBox;
    deepSyncFinishedMessageBox->setWindowTitle("DeepSync is prepared for wallet restart");
    deepSyncFinishedMessageBox->setText("The wallet will close now. Restart the wallet to initialize the blockchain!");
    deepSyncFinishedMessageBox->setStandardButtons(QMessageBox::Yes);

    if (deepSyncFinishedMessageBox->exec() == QMessageBox::Yes) {
        StartShutdown();
    }
}

void ModalOverlay::setClientModel(ClientModel* clientmodel)
{
    this->clientmodel = clientmodel;
    // Deactivate network for quick sync operations
    connect(this, SIGNAL(setNetworkStatus(bool)), clientmodel, SLOT(updateNetwork(bool)));
}

void ModalOverlay::onDeepSyncOptionsClicked()
{
    if (showDeepSyncOptions)
        showDeepSyncOptions = false;
    else
        showDeepSyncOptions = true;

    updateDeepSyncVisibility();
}

void ModalOverlay::onEditServerAddressButton()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Set Address"),
        tr("Address name:"), QLineEdit::Normal,
        blockchain_url.toString(), &ok);
    if (ok && !text.isEmpty()) {
        ui->bootstrapServerAddressEdit->setText(text);
        blockchain_url = text;
    }
}

void ModalOverlay::onProxyActivated(int state)
{
    if (state == 0)
        setProxyActivated(false);
    else if (state == 2)
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
void ModalOverlay::updateDeepSyncVisibility()
{
    if (!showDeepSync) {
        ui->deepSyncButton->hide();
        ui->downloadProgressBar->hide();
        ui->deepsyncoptionsButton->hide();
        ui->cancelPushButton->hide();

        ui->bootstrapServerAddressEdit->hide();
        ui->proxycheckBox->hide();
        ui->editServerAddressButton->hide();
    } else {
        ui->deepSyncButton->show();
        ui->downloadProgressBar->show();
        ui->deepsyncoptionsButton->show();
        ui->cancelPushButton->show();

        if (showDeepSyncOptions) {
            ui->bootstrapServerAddressEdit->show();
            ui->proxycheckBox->show();
            ui->editServerAddressButton->show();
        } else {
            ui->bootstrapServerAddressEdit->hide();
            ui->proxycheckBox->hide();
            ui->editServerAddressButton->hide();
        }
    }
}
