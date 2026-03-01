#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QXmlStreamReader>
#include <QString>
#include <QList>
#include <QFile>
#include <QFileDialog>
#include <QMutex>

#include "source.h"
#include "transferworker.h"

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
    void onFillSources();
    void onBeginTransfer();

    void onSourceFinished(unsigned);

private:
    Ui::MainWindow* m_ui;
    QList<Source*> m_sources;
    QMutex m_mutex;
    unsigned m_totalSourceVolume;
    unsigned m_totalResVolume;

    void loadSources();
    void showSources();
};
#endif // MAINWINDOW_H
