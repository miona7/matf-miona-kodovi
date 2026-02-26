#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), m_ui(new Ui::MainWindow) {
    m_ui->setupUi(this);

    m_ui->leNumOfRobots->setDisabled(true);
    m_ui->leMostWins->setDisabled(true);

    connect(m_ui->pbLoadRobots, &QPushButton::clicked, this, &MainWindow::onLoadRobotsClicked);
    connect(m_ui->pbBeginBattles, &QPushButton::clicked, this, &MainWindow::onBeginBattlesClicked);
}

MainWindow::~MainWindow() {
    qDeleteAll(m_robots);
    delete m_ui;
}

void MainWindow::onLoadRobotsClicked() {
    loadRobots();
    fillRobotsList();
}

void MainWindow::onBeginBattlesClicked() {
    if(m_robots.isEmpty()) {
        return;
    }

    m_ui->pbLoadRobots->setDisabled(true);
    m_ui->pbBeginBattles->setDisabled(true);

    m_ui->leMostWins->clear();

    initBattleTable();
    startThreads();
}

void MainWindow::loadRobots() {
    QString fileName = QFileDialog::getOpenFileName(this, "select robot file", "", "*.json");
    if(fileName.isEmpty()) {
        return;
    }

    QFile file = QFile(fileName);
    if(!file.open(QIODevice::ReadOnly)) {
        return;
    }

    auto doc = QJsonDocument::fromJson(file.readAll());

    file.close();

    qDeleteAll(m_robots);
    m_robots.clear();

    auto robotsVariant = doc.toVariant().toList();
    for(const auto& robotVariant : robotsVariant) {
        Robot* robot = new Robot(robotVariant);
        m_robots.append(robot);
    }
}

void MainWindow::fillRobotsList() {
    m_ui->lwRobotsList->clear();
    for(int i = 0; i < m_robots.size(); i++) {
        m_ui->lwRobotsList->addItem(QString::number(i+1) + ": " + m_robots[i]->toQString());
    }

    m_ui->leNumOfRobots->setText(QString::number(m_robots.size()));
}

void MainWindow::initBattleTable() {
    m_ui->twRobotsTable->clear();

    int numOfRobots = m_robots.size();

    m_ui->twRobotsTable->setRowCount(numOfRobots);
    m_ui->twRobotsTable->setColumnCount(numOfRobots);

    for(int i = 0; i < numOfRobots; ++i) {
        for(int j = 0; j < numOfRobots; ++j) {
            auto* tableItem = new QTableWidgetItem();
            if(i == j) {
                tableItem->setText("\\");
            }
            m_ui->twRobotsTable->setItem(i, j, tableItem);
        }
    }
}

void MainWindow::startThreads() {
}
