#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), m_ui(new Ui::MainWindow) {
    m_ui->setupUi(this);
    m_ui->pteLog->setEnabled(false);

    connect(m_ui->pbLoadStreets, &QPushButton::clicked, this, &MainWindow::onLoadStreets);
}

MainWindow::~MainWindow() {
    qDeleteAll(m_streets);
    delete m_ui;
}

void MainWindow::onLoadStreets() {
    loadStreets();
    showStreets();
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
