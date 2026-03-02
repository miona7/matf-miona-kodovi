#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), m_ui(new Ui::MainWindow) {
    m_ui->setupUi(this);

    connect(m_ui->pbLoad, &QPushButton::clicked, this, &MainWindow::onLoad);
    // connect();
}

MainWindow::~MainWindow() {
    qDeleteAll(m_competitors);
    delete m_ui;
}

void MainWindow::onLoad() {
    loadCompetitors();
    showCompetitors();
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
