#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QJsonDocument>
#include <QList>
#include <QThread>

#include "robot.h"
#include "robotworker.h"

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

private slots:
    void onLoadRobotsClicked();
    void onBeginBattlesClicked();
    void setBattleWinner(int, int);

private:
    Ui::MainWindow* m_ui;
    QList<Robot*> m_robots;
    int m_numOfUnfinishedBattles = 0;

    void loadRobots();
    void fillRobotsList();
    void initBattleTable();
    void startThreads();
    void setCompetitionWinner();
};
#endif // MAINWINDOW_H
