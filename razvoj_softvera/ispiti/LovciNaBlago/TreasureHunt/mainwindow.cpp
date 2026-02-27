#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), m_ui(new Ui::MainWindow) {
    m_ui->setupUi(this);
    this->setWindowTitle(QString("Potraga za blagom"));

    connect(m_ui->pbLoadData, &QPushButton::clicked, this, &MainWindow::onLoadDataClicked);
    connect(m_ui->pbBeginHunting, &QPushButton::clicked, this, &MainWindow::onBeginHuntingClicked);
}

MainWindow::~MainWindow() {
    qDeleteAll(m_hunters);
    delete m_ui;
}

void MainWindow::onLoadDataClicked() {
    loadData();
    showHunters();
    showMap();
}

void MainWindow::onBeginHuntingClicked() {
    if(m_hunters.isEmpty()) {
        return;
    }
    if(m_map.getMapSize().first == 0) {
        return;
    }

    m_ui->pbLoadData->setDisabled(true);
    m_ui->pbBeginHunting->setDisabled(true);
    m_ui->sbSpeed->setDisabled(true);

    m_numOfWorkers = 0;
    for(unsigned i = 0; i < m_hunters.size(); i++) {
        auto* worker = new HunterWorker(&m_hunters, i, &m_mutex, &m_map, m_ui->sbSpeed->value());
        m_numOfWorkers++;

        connect(worker, &HunterWorker::hunterMoved, this, &MainWindow::onHunterMoved);
        connect(worker, &HunterWorker::hunterFoundTreasure, this, &MainWindow::onHunterFoundTreasure);

        connect(worker, &QThread::finished, this, &MainWindow::onHunterThreadFinished);
        connect(worker, &QThread::finished, worker, &QObject::deleteLater);

        worker->start();
    }
}

void MainWindow::onHunterMoved(QPair<unsigned, unsigned> from, QPair<unsigned, unsigned> to) {
    const auto tag = m_ui->twMap->item(from.first, from.second)->text();
    m_ui->twMap->item(from.first, from.second)->setText("");
    m_ui->twMap->item(to.first, to.second)->setText(tag);
}

void MainWindow::onHunterFoundTreasure(unsigned index) {
    m_ui->lwHuntersList->item(index)->setText(m_hunters[index]->toQString());
}

void MainWindow::onHunterThreadFinished() {
    m_numOfWorkers--;
    if(m_numOfWorkers == 0) {
        m_ui->pbLoadData->setEnabled(true);
        m_ui->pbBeginHunting->setEnabled(true);
        m_ui->sbSpeed->setEnabled(true);

        const auto winner = *std::max_element(m_hunters.begin(), m_hunters.end(), [](const auto& l, const auto& r) {
            return l->getDucats() < r->getDucats();
        });

        const auto mess = "Pobednik je " + winner->getName() + ", sa " + QString::number(winner->getDucats()) + " novcica!";
        QMessageBox::information(this, "Pobednik!", mess);
    }
}

void MainWindow::loadData() {
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

    qDeleteAll(m_hunters);
    m_hunters.clear();

    const auto data = doc.toVariant().toMap();

    m_map.fromQVariant(data["mapa"]);

    const auto huntersVariant = data["tragaci"].toList();
    for(const auto& hunterVariant : huntersVariant) {
        m_hunters.append(new TreasureHunter(hunterVariant));
    }
}

void MainWindow::showHunters() {
    m_ui->lwHuntersList->clear();
    for(auto* h : m_hunters) {
        m_ui->lwHuntersList->addItem(h->toQString());
    }
}

void MainWindow::showMap() {
    m_ui->twMap->clear();

    const auto [rows, columns] = m_map.getMapSize();
    m_ui->twMap->setRowCount(rows);
    m_ui->twMap->setColumnCount(columns);

    for(unsigned i = 0; i < rows; i++) {
        for(unsigned j = 0; j < columns; j++) {
            auto* tableItem = new QTableWidgetItem();

            const auto tile = m_map.getTileAt({i, j});
            switch(tile) {
            case TreasureMap::Tile::Wall:
                tableItem->setText("#");
                break;
            case TreasureMap::Tile::Treasure:
                tableItem->setText("@");
                break;
            default:
                break;
            }
            m_ui->twMap->setItem(i, j, tableItem);
        }
    }

    for(const auto& h : m_hunters) {
        const auto [row, col] = h->getPosition();
        const auto name = h->getName();
        m_ui->twMap->item(row, col)->setText(name.isEmpty() ? "?" : name.sliced(0, 1));
    }
}
