#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QFile>
#include <QFileDialog>
#include <QJsonDocument>
#include <QString>
#include <QMap>

#include "city.h"
#include "travelerworker.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* = nullptr);
    ~MainWindow();

public slots:
    void onLoadCities();
    void onBeginVisits();

    void onTookArticle(const QString&);
    void onMenhetnDistance(unsigned);

private:
    Ui::MainWindow* m_ui;
    QList<City*> m_cities;
    unsigned m_numOfWorkers;
    unsigned m_totalDistance;
    QMap<QString, unsigned> m_map;

    void loadCities();
    void showCities();
    void showArticles();
};
#endif // MAINWINDOW_H
