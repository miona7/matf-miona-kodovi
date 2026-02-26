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

    for(unsigned i = 0; i < rows; ++i) {
        for(unsigned j = 0; j < columns; ++j) {
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
}
