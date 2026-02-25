#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->leNajvisePobeda->setDisabled(true);
    ui->leBrojRobota->setDisabled(true);
}

MainWindow::~MainWindow() {
    delete ui;
}
