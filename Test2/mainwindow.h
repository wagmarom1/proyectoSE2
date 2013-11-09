#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <cv.h>
#include <QTimer>

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
private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    CvCapture* capwebcam;

    IplImage* matOriginal;
    cv::Mat matProcessed;

    std::vector<cv::Vec3f>::iterator itrCircles;
    std::vector<cv::Vec3f> vecCircles;

    void TrackObject(IplImage* imgThresh);
    QImage IplImagetoQImage(const IplImage *iplImage);

    QTimer* tmrTimer;
};

#endif // MAINWINDOW_H
