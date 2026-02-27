#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent) , m_ui(new Ui::MainWindow) {
    m_ui->setupUi(this);

    m_ui->leRoad->setDisabled(true);

    connect(m_ui->pbLoadCities, &QPushButton::clicked, this, &MainWindow::onLoadCities);
    connect(m_ui->pbBeginVisits, &QPushButton::clicked, this, &MainWindow::onBeginVisits);
}

MainWindow::~MainWindow() {
    qDeleteAll(m_cities);
    delete m_ui;
}

void MainWindow::onLoadCities() {
    loadCities();
    showCities();
}

void MainWindow::loadCities() {
    QList<QString> filesNames = QFileDialog::getOpenFileNames(this, "select json file", "", "*.json");
                                    // omogucava selektovanje vise fajlova
    if(filesNames.isEmpty()) {
        return;
    }

    qDeleteAll(m_cities);
    m_cities.clear();

    for(const auto& fileName : filesNames) {
        QFile file(fileName);
        if(!file.open(QIODevice::ReadOnly)) {
            return;
        }

        const auto doc = QJsonDocument::fromJson(file.readAll());
        file.close();

        const auto dataVar = doc.toVariant().toMap();
        m_cities.append(new City(dataVar));
    }
}

void MainWindow::onBeginVisits() {
    if(m_cities.isEmpty()) {
        return;
    }

    bool valid;
    const unsigned numOfVisitors = m_ui->leNumofVisitors->text().toUInt(&valid);
    if(!valid || numOfVisitors <= 0) {
        return;
    }

    m_ui->pbLoadCities->setDisabled(true);
    m_ui->pbBeginVisits->setDisabled(true);
    m_ui->leRoad->clear();
    m_ui->lwArticles->clear();

    m_numOfWorkers = numOfVisitors;
    m_totalDistance = 0;
    m_map.clear();
    for(unsigned i = 0; i < numOfVisitors; i++) {
        auto* worker = new TravelerWorker(&m_cities);

        connect(worker, &TravelerWorker::tookArticle, this, &MainWindow::onTookArticle);
        connect(worker, &TravelerWorker::menhetnDistance, this, &MainWindow::onMenhetnDistance);

        connect(worker, &QThread::finished, worker, &QObject::deleteLater);

        worker->start();
    }
}


void MainWindow::onTookArticle(const QString& article) {
    if(article.isEmpty()) {
        return;
    }
    showCities();
    m_map[article]++;
    showArticles();
}

void MainWindow::onMenhetnDistance(unsigned distance) {
    m_totalDistance += distance;
    m_numOfWorkers--;

    if(m_numOfWorkers == 0) {
        m_ui->pbLoadCities->setEnabled(true);
        m_ui->pbBeginVisits->setEnabled(true);
        m_ui->leRoad->setText(QString::number(m_totalDistance));
    }
}

void MainWindow::showCities() {
    m_ui->lwCities->clear();
    for(const auto& c : m_cities) {
        m_ui->lwCities->addItem(c->toQString());
    }
}

void MainWindow::showArticles() {
    m_ui->lwArticles->clear();
    for(auto it = m_map.begin(); it != m_map.end(); it++) {
        m_ui->lwArticles->addItem(it.key() + ": " + QString::number(it.value()));
    }
}
