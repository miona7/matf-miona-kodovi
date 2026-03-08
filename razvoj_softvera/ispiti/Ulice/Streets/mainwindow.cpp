#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), m_ui(new Ui::MainWindow) {
    m_ui->setupUi(this);
    m_ui->pteLog->setReadOnly(true);

    connect(m_ui->pbLoadStreets, &QPushButton::clicked, this, &MainWindow::onLoadStreets);
    connect(m_ui->pbBeginWork, &QPushButton::clicked, this, &MainWindow::onBeginWork);
    connect(m_ui->pbSaveLog, &QPushButton::clicked, this, &MainWindow::onSaveLog);
}

MainWindow::~MainWindow() {
    qDeleteAll(m_streets);
    delete m_ui;
}

void MainWindow::onLoadStreets() {
    loadStreets();
    showStreets();
}

void MainWindow::onBeginWork() {
    if(m_streets.isEmpty()) {
        return;
    }

    m_ui->pbLoadStreets->setDisabled(true);
    m_ui->pbBeginWork->setDisabled(true);
    m_ui->pbSaveLog->setDisabled(true);

    m_numOfTeams = m_ui->sbNumOfTeams->text().toUInt();
    m_ui->sbNumOfTeams->setDisabled(true);

    m_ui->pteLog->clear();

    m_numOfWorkers = 0;
    for(auto* s : m_streets) {
        for(unsigned i = 0; i < m_numOfTeams; i++) {
            auto* worker = new Worker(s, i);
            m_numOfWorkers++;

            connect(worker, &QThread::finished, worker, &QObject::deleteLater);
            connect(worker, &Worker::finishedNormally, this, &MainWindow::onWorkersFinished);
            connect(worker, &Worker::removed, this, &MainWindow::onRemoved);

            worker->start();
        }
    }
}

void MainWindow::onWorkersFinished(Street* street, unsigned index, bool normally) {
    m_numOfWorkers--;

    if(normally) {
        if(m_numOfWorkers == 0) {
            m_ui->pbLoadStreets->setEnabled(true);
            m_ui->pbBeginWork->setEnabled(true);
            m_ui->pbSaveLog->setEnabled(true);
            m_ui->sbNumOfTeams->setEnabled(true);
        }
        showStreets();
        m_ui->pteLog->appendPlainText("Ekipa " + QString::number(index) + " u ulici " + street->getName() + " je zavrsila rad");
    } else {
        m_ui->pteLog->appendPlainText("Ekipa " + QString::number(index) + " u ulici " + street->getName() + " se pokvarila");

        auto* worker = new Worker(street, m_numOfTeams + index);
        m_numOfWorkers++;

        connect(worker, &QThread::finished, worker, &QObject::deleteLater);
        connect(worker, &Worker::finishedNormally, this, &MainWindow::onWorkersFinished);
        connect(worker, &Worker::removed, this, &MainWindow::onRemoved);

        worker->start();
    }
}

void MainWindow::onRemoved(Street* street, unsigned index, unsigned decor) {
    showStreets();
    m_ui->pteLog->appendPlainText("Ekipa " + QString::number(index) + " u ulici " + street->getName() + " je uklonila " + QString::number(decor));
}

void MainWindow::onSaveLog() {
    QString fileName = QFileDialog::getSaveFileName(this, "select file", "", "*.txt");
    if(fileName.isEmpty()) {
        return;
    }

    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }

    QTextStream out(&file);
    out << m_ui->pteLog->toPlainText();
    file.close();
}

void MainWindow::loadStreets() {
    auto filesNames = QFileDialog::getOpenFileNames(this, "select json file", "", "*.json");

    qDeleteAll(m_streets);
    m_streets.clear();

    for(auto fileName : filesNames) {
        QFile file(fileName);
        if(fileName.isEmpty()) {
            continue;
        }

        if(!file.open(QIODevice::ReadOnly)) {
            return;
        }

        auto doc = QJsonDocument::fromJson(file.readAll());
        file.close();

        auto streets = doc.toVariant().toMap()["streets"].toList();
        for(const auto& s : streets) {
            m_streets.append(new Street(s));
        }
    }
}

void MainWindow::showStreets() {
    m_ui->lwStreets->clear();
    for(auto* s : m_streets) {
        m_ui->lwStreets->addItem(s->toQString());
    }
}
