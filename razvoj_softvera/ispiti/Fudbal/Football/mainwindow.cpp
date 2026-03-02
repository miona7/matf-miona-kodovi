#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), m_ui(new Ui::MainWindow) {
    m_ui->setupUi(this);

    connect(m_ui->pbLoad, &QPushButton::clicked, this, &MainWindow::onLoad);
    connect(m_ui->pbBeginMatch, &QPushButton::clicked, this, &MainWindow::onBeginMatch);
}

MainWindow::~MainWindow() {
    qDeleteAll(m_competitors);
    delete m_ui;
}

void MainWindow::onLoad() {
    loadCompetitors();
    showCompetitors();
}

void MainWindow::onBeginMatch() {
    if(m_competitors.size() < 2) {
        QMessageBox::warning(this, "Greska", "Pogresan broj igraca");
        return;
    }

    m_ui->pbLoad->setDisabled(true);
    m_ui->pbBeginMatch->setDisabled(true);

    unsigned numOfTries = m_ui->sbNumOfTries->value();

    m_numOfWorkers = 0;
    for(unsigned i = 0; i < m_competitors.size(); i++) {
        auto* worker = new CompetitorWorker(&m_competitors, i, numOfTries);
        m_numOfWorkers++;

        connect(worker, &CompetitorWorker::goal, this, &MainWindow::onGoal);

        connect(worker, &QThread::finished, this, &MainWindow::onFinish);
        connect(worker, &QThread::finished, worker, &QObject::deleteLater);

        worker->start();
    }
}

void MainWindow::onGoal(bool goal, unsigned i) {
    if(goal) {
        m_ui->lwMatch->addItem(m_competitors[i]->getName() + " je pogodio");
    } else {
        m_ui->lwMatch->addItem(m_competitors[i]->getName() + " je pogresio");
    }
}

void MainWindow::onFinish() {
    if(m_numOfWorkers == 0) {
        m_ui->pbLoad->setDisabled(false);
        m_ui->pbBeginMatch->setDisabled(false);
    }
}

void MainWindow::loadCompetitors() {
    QString fileName = QFileDialog::getOpenFileName(this, "select json file", "", "*.json");
    if(fileName.isEmpty()) {
        return;
    }

    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly)) {
        return;
    }

    const auto doc = QJsonDocument::fromJson(file.readAll());
    file.close();

    qDeleteAll(m_competitors);
    m_competitors.clear();

    const auto footballersVariant = doc.toVariant().toList();
    for(const auto& footballerVariant : footballersVariant) {
        m_competitors.append(new Competitor(footballerVariant));
    }
}

void MainWindow::showCompetitors() {
    m_ui->lwFootballers->clear();
    for(const auto& c : m_competitors) {
        m_ui->lwFootballers->addItem(c->toQString());
    }
}
