#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QJsonDocument>
#include <QList>

#include <algorithm>

#include "singer.h"
#include "voteworker.h"

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
    void onLoadSingers();
    void onBeginVoting();
    void onVoted();

private:
    Ui::MainWindow* m_ui;
    QList<Singer*> m_singers;

    void loadSingers();
    void showSingers();
    void showVotes();
};
#endif // MAINWINDOW_H
