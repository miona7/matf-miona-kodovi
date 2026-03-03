#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QFile>
#include <QFileDialog>
#include <QJsonDocument>
#include <QMessageBox>

#include <vector>
#include <algorithm>

#include "competitor.h"
#include "competitorworker.h"

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
    void onLoad();
    void onBeginMatch();

    void onGoal(bool, unsigned);
    void onFinish();

private:
    Ui::MainWindow* m_ui;
    QList<Competitor*> m_competitors;
    unsigned m_numOfWorkers;

    void loadCompetitors();
    void showCompetitors();
    void removeAndShowCompetitorsMedian();
    unsigned calculateMedian() const;
};
#endif // MAINWINDOW_H
