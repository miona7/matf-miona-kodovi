#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), m_ui(new Ui::MainWindow) {
    m_ui->setupUi(this);
    this->setWindowTitle("Januar 1");

    m_ui->leTotalSourcesVolume->setDisabled(true);
    m_ui->leCurrentReservoirVolume->setDisabled(true);
    m_ui->leLoss->setDisabled(true);

    connect(m_ui->pbFillSource, &QPushButton::clicked, this, &MainWindow::onFillSources);
    connect(m_ui->pbBeginTransfer, &QPushButton::clicked, this, &MainWindow::onBeginTransfer);
}

MainWindow::~MainWindow() {
    qDeleteAll(m_sources);
    delete m_ui;
}

void MainWindow::onFillSources() {
    loadSources();
    showSources();
}

void MainWindow::onBeginTransfer() {
    auto totalResVolume = (m_ui->leTotalReservoirVolume->text()).toInt();
    if(totalResVolume <= 0) {
        return;
    }

    m_totalResVolume = static_cast<unsigned>(totalResVolume);
    m_ui->leCurrentReservoirVolume->setText("0");
    m_ui->leLoss->setText("0");

    for(const auto& s : m_sources) {
        auto* worker = new TransferWorker(&m_sources, &m_mutex);

        connect(worker, &TransferWorker::sourceFinished, this, &MainWindow::onSourceFinished);

        connect(worker, &QThread::finished, worker, &QObject::deleteLater);

        worker->start();
    }
}

void MainWindow::onSourceFinished(unsigned volume) {
    showSources();

    auto currVolume = m_ui->leCurrentReservoirVolume->text().toUInt();
    currVolume += volume;

    if(currVolume > m_totalResVolume) {
        m_ui->leCurrentReservoirVolume->setText(QString::number(m_totalResVolume));

        auto currLoss = m_ui->leLoss->text().toUInt();
        currLoss += (currVolume - m_totalResVolume);
        m_ui->leLoss->setText(QString::number(currLoss));
    } else {
        m_ui->leCurrentReservoirVolume->setText(QString::number(currVolume));
    }
}

void MainWindow::loadSources() {
    QString fileName = QFileDialog::getOpenFileName(this, "select xml fajl", "", "*.xml");
    if(fileName.isEmpty()) {
        return;
    }

    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly)) {
        return;
    }

    QXmlStreamReader xmlReader(&file);

    qDeleteAll(m_sources);
    m_sources.clear();

    m_totalSourceVolume = 0;

    xmlReader.readNextStartElement();
    while(xmlReader.readNextStartElement()) {
        QVariantMap map;

        xmlReader.readNextStartElement();

        auto volume = xmlReader.readElementText().toUInt();
        map["volume"] = volume;
        m_totalSourceVolume += volume;

        xmlReader.readNextStartElement();
        auto name = xmlReader.readElementText();
        map["name"] = name;

        m_sources.append(new Source(map));

        xmlReader.readNextStartElement();
    }

    file.close();
}

void MainWindow::showSources() {
    m_ui->lwSources->clear();
    for(const auto& s : m_sources) {
        m_ui->lwSources->addItem(s->toQString());
    }
    m_ui->leTotalSourcesVolume->setText(QString::number(m_totalSourceVolume));
}
