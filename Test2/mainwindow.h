#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "packetadmin.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <cv.h>
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
    void processFrameAndUpdateGUI();
    void callGarbageCollector();

private slots:
    void on_pushButton_clicked();
    void on_horizontalScrollBar_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    CvCapture* capwebcam;
    IplImage* matOriginal;
    QPoint* playerPosition;
    packetAdmin* packetAdm;
    QTimer* timer;
    QTimer* guiTimer;
    QTimer* cleanerTimer;
    QImage* pixmap;
    QObjectCleanupHandler* cleaner;

    void TrackObject(IplImage* imgThresh);
    QImage IplImagetoQImage(const IplImage *iplImage);


protected:
    void paintEvent(/*QPaintEvent * e*/);
};

#endif // MAINWINDOW_H
