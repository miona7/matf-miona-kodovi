#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QJsonDocument>
#include <QList>

#include "robot.h"

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

private:
    Ui::MainWindow* m_ui;
    QList<Robot*> m_robots;

    void loadRobots();
    void fillRobotsList();
    void initBattleTable();
    void startThreads();
};
#endif // MAINWINDOW_H
