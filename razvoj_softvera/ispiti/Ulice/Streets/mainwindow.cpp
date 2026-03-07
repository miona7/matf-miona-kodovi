#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), m_ui(new Ui::MainWindow) {
    m_ui->setupUi(this);
    m_ui->pteLog->setEnabled(false);
}

MainWindow::~MainWindow() {
    delete m_ui;
}
