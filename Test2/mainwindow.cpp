#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore>
#include <QPainter>
using namespace std;

float MAP_WIDTH, MAP_HEIGHT;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);                      //set up the gui

    MAP_WIDTH = ui->lbMap->width();         //save the label width
    MAP_HEIGHT =  ui->lbMap->height();      //save the label height
    pointPosition = new QPoint(0,0);

    std::cout << MAP_HEIGHT << std::endl;
    capwebcam = cvCaptureFromCAM(0);

    if(!capwebcam)
    {
        return;
    }

    tmrTimer = new QTimer(this);
    connect(tmrTimer, SIGNAL(timeout()), this, SLOT(processFrameAndUpdateGUI()));
    tmrTimer->start(20);
}

MainWindow::~MainWindow()
{
    delete ui;
    cvReleaseImage(&matOriginal);
    cvReleaseCapture(&capwebcam);
}


void MainWindow::processFrameAndUpdateGUI()
{
    matOriginal = cvQueryFrame(capwebcam);

    if(!matOriginal) return;

    matOriginal=cvCloneImage(matOriginal);

    cvSmooth(matOriginal, matOriginal, CV_GAUSSIAN,3,3);                    //smooth the original image using Gaussian kernel


    IplImage* imgGrayScale = cvCreateImage(cvGetSize(matOriginal), 8, 1);   //create a space for img of grayscale
    cvCvtColor(matOriginal,imgGrayScale,CV_BGR2GRAY);                       //converting the original image into grayscale

    cvThreshold(imgGrayScale,imgGrayScale,100,255,CV_THRESH_BINARY_INV);    //thresholding the grayscale image to get better results

    //track the possition of the ball
    TrackObject(imgGrayScale);

    QImage qimgOriginal = IplImagetoQImage(matOriginal);                    //convert image read from video to QImage

    ui->lbOriginal->setPixmap(QPixmap::fromImage(qimgOriginal).scaled(this->ui->lbOriginal->width(),this->ui->lbOriginal->height(),Qt::KeepAspectRatio));
    cvReleaseImage(&imgGrayScale);
}

void MainWindow::on_pushButton_clicked()
{
    if(pointPosition->x()==50)
    {
        pointPosition->setX(0);
    }else {
        pointPosition->setX(50);
    }
}

extern "C"
void MainWindow::TrackObject(IplImage* imgThresh){
        CvSeq* contour;                                         //hold the pointer to a contour
        CvSeq* result;                                          //hold sequence of points of a contour
        CvMemStorage *storage = cvCreateMemStorage(0);          //storage area for all contours

        //finding all contours in the image
        cvFindContours(imgThresh, storage, &contour, sizeof(CvContour), CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cvPoint(0,0));

        int pointsToDetec = (ui->rbTriangle->isChecked())? 3 : 4;
        CvPoint *pt[pointsToDetec];
       //iterating through each contour
       while(contour)
       {
            //obtain a sequence of points of the countour, pointed by the variable 'countour'
           result = cvApproxPoly(contour, sizeof(CvContour), storage, CV_POLY_APPROX_DP, cvContourPerimeter(contour)*0.02, 0);

           //if there are 3 vertices  in the contour and the area of the triangle is more than 100 pixels


           if(result->total==pointsToDetec && fabs(cvContourArea(result, CV_WHOLE_SEQ))>100 )
           {
                //iterating through each point
                for(int i=0;i<pointsToDetec;i++){
                   pt[i] = (CvPoint*)cvGetSeqElem(result, i);
                   cvCircle(matOriginal, *pt[i],5,cvScalar(0,255,0),2,8,0);
                }

                //Draw the uper point of triangle
                int x = pt[0]->x, y = pt[0]->y;
                stringstream strs;
                strs << "Point: " << x << "," << y;
                string temp_str = strs.str();
                char* strs_char_type = (char*) temp_str.c_str();
                CvFont font;
                cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX, 0.4, 0.4, 0, 1, 8);
                cvPutText(matOriginal, strs_char_type , *pt[0], &font, cvScalar(0,255,0));
                ui->lbpoint->setText(QString(strs_char_type));

                if(x < MAP_WIDTH && 0 < x){
                  pointPosition->setX(x);
                }
                if(y < MAP_HEIGHT && 0 < y){
                  pointPosition->setY(y);
                }
           }

            //obtain the next contour
            contour = contour->h_next;
       }


       cvReleaseMemStorage(&storage);
}

QImage MainWindow::IplImagetoQImage(const IplImage *iplImage)
{
    int height = iplImage->height;
    int width = iplImage->width;

    const uchar *qImageBuffer =(const uchar*)iplImage->imageData;
    QImage img(qImageBuffer, width, height, QImage::Format_RGB888);

    return img.rgbSwapped();;
}

void MainWindow::paintEvent(QPaintEvent * e){

    QPixmap pixmap(ui->lbMap->width(),ui->lbMap->height());
    pixmap.fill(QColor("transparent"));

    QPainter painter(&pixmap);
    painter.setPen(QPen(Qt::darkMagenta, 5, Qt::DashLine, Qt::RoundCap));
    painter.setBrush(QBrush(Qt::green, Qt::SolidPattern));
    painter.drawEllipse(pointPosition->x(), MAP_HEIGHT-50, 50, 50);

    ui->lbMap->setPixmap(pixmap);
}
