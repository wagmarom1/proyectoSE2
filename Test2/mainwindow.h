#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "packetadmin.h"
#include "trackfigure.h"
#include <QTimer>
#include <QtCore>
#include <QObjectCleanupHandler>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
public slots:
    void callGarbageCollector();

private slots:
    void on_pushButton_clicked();
    void on_horizontalScrollBar_valueChanged(int value);
    void repaint(QImage qimgOriginal);
    void on_rbTriangle_toggled(bool checked);

private:
    Ui::MainWindow *ui;
    packetAdmin* packetAdm;
    QTimer* timer;
    QTimer* guiTimer;
    QTimer* cleanerTimer;
    QImage* pixmap;
    QObjectCleanupHandler* cleaner;
    trackFigure* tracker;


protected:
    void paintEvent(/*QPaintEvent * e*/);
};

#endif // MAINWINDOW_H
