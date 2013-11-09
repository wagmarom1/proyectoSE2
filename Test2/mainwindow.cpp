#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    capwebcam = cvCaptureFromCAM(1);

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
    //cv::inRange(matOriginal, cv::Scalar(0,0,175), cv::Scalar(100,100,256), matProcessed);
    //cv::GaussianBlur(matProcessed, matProcessed, cv::Size(9,9), 1.5);

    //smooth the original image using Gaussian kernel
    cvSmooth(matOriginal, matOriginal, CV_GAUSSIAN,3,3);

    //converting the original image into grayscale
    IplImage* imgGrayScale = cvCreateImage(cvGetSize(matOriginal), 8, 1);
    cvCvtColor(matOriginal,imgGrayScale,CV_BGR2GRAY);

    //thresholding the grayscale image to get better results
    cvThreshold(imgGrayScale,imgGrayScale,100,255,CV_THRESH_BINARY_INV);

    //track the possition of the ball

    //Convert Mat to IplImage
//    IplImage *matOriginalIplImage;
//    matOriginalIplImage = cvCreateImage(cvSize(ui->lbOriginal->width(),ui->lbOriginal->height()), IPL_DEPTH_8U, 1); //create IplImage for matOriginal
//    matOriginalIplImage->imageData = (char *) matOriginal.data; // get data of matOriginal for IplImage
    // Track triangle
    TrackObject(imgGrayScale);

    //cv::Mat temp(matOriginalIplImage);
    //matOriginal = temp;
    //cv::cvtColor(matOriginal, matOriginal, CV_BGR2RGB);

    QImage qimgOriginal = IplImagetoQImage(matOriginal);
    //QImage qimgOriginal((uchar*)matOriginal->imageData, matOriginal->width, matOriginal->height, QImage::Format_RGB888);
    //QImage qimgProcessed((uchar*)matProcessed.data, matProcessed.cols, matProcessed.rows, matProcessed.step, QImage::Format_Indexed8);

    ui->lbOriginal->setPixmap(QPixmap::fromImage(qimgOriginal).scaled(this->ui->lbOriginal->width(),this->ui->lbOriginal->height(),Qt::KeepAspectRatio));
    //ui->lbProcessed->setPixmap(QPixmap::fromImage(qimgProcessed));
    cvReleaseImage(&imgGrayScale);
}

void MainWindow::on_pushButton_clicked()
{
    if(tmrTimer->isActive() == true)
    {
        tmrTimer->stop();
        ui->pushButton->setText("resume");
    }else {
        tmrTimer->start(20);
        ui->pushButton->setText("pause");
    }
}

extern "C"
void MainWindow::TrackObject(IplImage* imgThresh){
        CvSeq* contour;  //hold the pointer to a contour
        CvSeq* result;     //hold sequence of points of a contour
        CvMemStorage *storage = cvCreateMemStorage(0); //storage area for all contours

        //finding all contours in the image
        cvFindContours(imgThresh, storage, &contour, sizeof(CvContour), CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cvPoint(0,0));

        int valueToDetec = (ui->rbTriangle->isChecked())? 3 : 4;

       //iterating through each contour
       while(contour)
       {
            //obtain a sequence of points of the countour, pointed by the variable 'countour'
           result = cvApproxPoly(contour, sizeof(CvContour), storage, CV_POLY_APPROX_DP, cvContourPerimeter(contour)*0.02, 0);

           //if there are 3 vertices  in the contour and the area of the triangle is more than 100 pixels


           if(result->total==valueToDetec && fabs(cvContourArea(result, CV_WHOLE_SEQ))>100 )
           {
                  //iterating through each point
                  CvPoint *pt[4];
                  for(int i=0;i<4;i++){
                       pt[i] = (CvPoint*)cvGetSeqElem(result, i);
                       cvCircle(matOriginal, *pt[i],5,cvScalar(0,255,0),2,8,0);
                  }

//                  cvLine(matOriginal, *pt[0], *pt[1], cvScalar(0,0,255), 2);
//                  cvLine(matOriginal, *pt[0], *pt[2], cvScalar(0,0,255), 2);
//                  cvLine(matOriginal, *pt[2], *pt[1], cvScalar(0,0,255), 2);

                  //Draw the uper point of triangle
                  int x = pt[0]->x, y = pt[0]->y;
                  stringstream strs;
                  strs << "Point: " << x << "," << y;
                  string temp_str = strs.str();
                  char* strs_char_type = (char*) temp_str.c_str();
                  CvFont font;
                  cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX, 0.4, 0.4, 0, 1, 8);
                  cvPutText(matOriginal, strs_char_type , *pt[0], &font, cvScalar(0,255,0));
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
