#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QJsonDocument>
#include <QList>

#include "treasurehunter.h"
#include "treasuremap.h"

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
    void onLoadDataClicked();
    void onBeginHuntingClicked();

private:
    Ui::MainWindow* m_ui;
    QList<TreasureHunter*> m_hunters;
    TreasureMap m_map;

    void loadData();
    void showHunters();
    void showMap();
};
#endif // MAINWINDOW_H
