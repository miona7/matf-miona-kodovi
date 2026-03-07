#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QList>
#include <QFile>
#include <QFileDialog>
#include <QJsonDocument>

#include "street.h"

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
    void onLoadStreets();

private:
    Ui::MainWindow* m_ui;
    QList<Street*> m_streets;

    void loadStreets();
    void showStreets();
};
#endif // MAINWINDOW_H
