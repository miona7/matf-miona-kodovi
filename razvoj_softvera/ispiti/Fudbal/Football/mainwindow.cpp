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

    for(auto& c : m_competitors) {
        c->setPoints(0);
    }

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
    m_numOfWorkers--;
    if(m_numOfWorkers == 0) {
        removeAndShowCompetitorsMedian();

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
    m_ui->lwMatch->clear();
    m_ui->lwFootballersMedian->clear();
    for(const auto& c : m_competitors) {
        m_ui->lwFootballers->addItem(c->toQString());
    }
}

void MainWindow::removeAndShowCompetitorsMedian() {
    auto median = calculateMedian();
    for(const auto& c : m_competitors) {
        if(c->getPoints() < median) {
            m_ui->lwFootballersMedian->addItem(c->toQString());
        }
    }

    m_competitors.removeIf([&median](const auto& c) {
        if(c->getPoints() < median) {
            delete c;
            return true;
        }
        return false;
    });

    if(m_competitors.size() == 1) {
        QMessageBox::information(this, "Pobednik", "Pobednik je " + m_competitors[0]->getName());
    }
}

unsigned MainWindow::calculateMedian() const {
    std::vector<unsigned> v;
    for(const auto& c : m_competitors) {
        v.push_back(c->getPoints());
    }

    std::sort(v.begin(), v.end());

    if(v.size() % 2 == 0) {
        return (v[v.size()/2 - 1] + v[v.size()/2]) / 2;
    } else {
        return v[v.size()/2];
    }
}
