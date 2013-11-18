#ifndef TRACKFIGURE_H
#define TRACKFIGURE_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <cv.h>
#include <QtCore>
#include <QPixmap>
using namespace std;

class trackFigure :public QObject
{
     Q_OBJECT
public:
    explicit trackFigure(QObject *parent = 0);
    CvCapture* capwebcam;
    IplImage* matOriginal;
    bool triangleIsChecked;
    QPoint* playerPosition;
    int MAP_WIDTH, MAP_HEIGHT;

    void TrackObject(IplImage* imgThresh);
    QImage IplImagetoQImage(const IplImage *iplImage);

signals:
    void repaint(QImage qimgOriginal);

public slots:
    void trackObjectAndUpdateGUI();
};

#endif // TRACKFIGURE_H
