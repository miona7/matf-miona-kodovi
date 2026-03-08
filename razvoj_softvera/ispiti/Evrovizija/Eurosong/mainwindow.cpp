#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), m_ui(new Ui::MainWindow) {
    m_ui->setupUi(this);

    connect(m_ui->pbLoadSingers, &QPushButton::clicked, this, &MainWindow::onLoadSingers);
    connect(m_ui->pbBeginVoting, &QPushButton::clicked, this, &MainWindow::onBeginVoting);
}

MainWindow::~MainWindow() {
    qDeleteAll(m_singers);
    delete m_ui;
}

void MainWindow::onLoadSingers() {
    loadSingers();
    showSingers();
}

void MainWindow::onBeginVoting() {
    for(auto* s : m_singers) {
        auto* worker = new VoteWorker(s, &m_singers);

        connect(worker, &VoteWorker::voted, this, &MainWindow::onVoted);
        connect(worker, &QThread::finished, worker, &QObject::deleteLater);

        worker->start();
    }
}

void MainWindow::onVoted() {
    std::sort(m_singers.begin(), m_singers.end(), [](const auto* s1, const auto* s2) {
        return s1->getPoints() >= s2->getPoints();
    });

    showVotes();
}

void MainWindow::loadSingers() {
    QString fileName = QFileDialog::getOpenFileName(this, "select json file", "", "*.json");
    if(fileName.isEmpty()) {
        return;
    }

    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly)) {
        return;
    }

    auto doc = QJsonDocument::fromJson(file.readAll());
    file.close();

    qDeleteAll(m_singers);
    m_singers.clear();

    const auto singersVariant = doc.toVariant().toMap()["countries"].toList();
    for(const auto& singerVariant : singersVariant) {
        m_singers.append(new Singer(singerVariant));
    }
}

void MainWindow::showSingers() {
    m_ui->lwSingers->clear();
    for(const auto* s : m_singers) {
        m_ui->lwSingers->addItem(s->toQString());
    }
}

void MainWindow::showVotes() {
    m_ui->lwVoting->clear();
    for(const auto* s : m_singers) {
        m_ui->lwVoting->addItem(s->toQString());
    }
}
