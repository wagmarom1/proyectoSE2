#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QPicture>
using namespace std;

const int CAMID = 0,                       //cam selected
          LEVEL_DELAY = 8000,              //delay to drop a packet
          GUI_REFRESH_DELAY = 20;          //delay to refresh gui
int MAP_WIDTH, MAP_HEIGHT, packetsCatched;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);                      //set up the gui
    MAP_WIDTH = ui->lbMap->width();         //save the label width
    MAP_HEIGHT =  ui->lbMap->height();      //save the label height
    packetsCatched = 0;
    playerPosition = new QPoint(0,0);

    capwebcam = cvCaptureFromCAM(CAMID);

    if(!capwebcam)
    {
        return;
    }
    //packet admin
    packetAdm = new packetAdmin();
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), packetAdm, SLOT(createPacket())); //each 5s will throw a packet
    connect(packetAdm, SIGNAL(crossTheEnd(QString)), ui->lbLost, SLOT(setText(QString))); //refresh lost counter
    timer->start(LEVEL_DELAY);

    guiTimer = new QTimer(this);
    connect(guiTimer, SIGNAL(timeout()), this, SLOT(processFrameAndUpdateGUI()));
    guiTimer->start(20);

    pixmap = new QImage(ui->lbMap->width(),ui->lbMap->height(), QImage::Format_ARGB32_Premultiplied);         //create pixmap qith lbMap dimensions
    pixmap->fill(QColor("transparent"));                                                                 //set the filled surface

    cleanerTimer = new QTimer(this);
    cleaner = new QObjectCleanupHandler();
    connect(cleanerTimer, SIGNAL(timeout()), this, SLOT(callGarbageCollector()));
    cleanerTimer->start(10000);
}

MainWindow::~MainWindow()
{
    delete ui;
    cvReleaseImage(&matOriginal);
    cvReleaseCapture(&capwebcam);

    //delete instances, threads and abort packets
    for(int i = 0; i < packetAdm->getPackets().size(); i++)
    {
        packet* packet_ = packetAdm->getPackets().at(i);
        QThread* thread_ = packetAdm->getThreads().at(i);
        packet_->abort();
        thread_->wait();
        delete packet_;
        delete thread_;
    }
    delete packetAdm;
    delete timer;
}

void MainWindow::callGarbageCollector()
{
    cleaner->clear();
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
    cvReleaseImage(&matOriginal);
    paintEvent();
}

void MainWindow::on_pushButton_clicked()
{
    packetsCatched = 0;
    ui->lbCached->setText(QString::number(0));
    packetAdm->resetLostPackets();
    ui->lbLost->setText(QString::number(0));
    ui->lbLevel->setText(QString::number(1));
    ui->horizontalScrollBar->setValue(10);
    timer->setInterval(LEVEL_DELAY);
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

                //Change the player position
                if(x < MAP_WIDTH && 0 < x){
                  playerPosition->setX(x);
                }
                if(y < MAP_HEIGHT && 0 < y){
                  playerPosition->setY(y);
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

    return img.rgbSwapped();
}


void MainWindow::paintEvent(/*QPaintEvent * e*/){

    QPainter painter(pixmap);
    painter.setPen(QPen(Qt::darkMagenta, 3, Qt::DotLine, Qt::RoundCap));                                //set a pen to draw with dot line and magenta
    painter.setBrush(QBrush(Qt::green, Qt::CrossPattern));                                              //set a brush cross patern and green
    QRectF rectangle(playerPosition->x(), MAP_HEIGHT-50, 70.0, 20.0);                                   //get a rectangle to draw a elipse
    painter.drawEllipse(rectangle);                                                                     //draw a elipse
    painter.setBrush(QBrush(Qt::darkBlue, Qt::Dense3Pattern));
    QPainterPath path;                                                                                  //with path u can draw wherever u want
    path.moveTo(playerPosition->x(), MAP_HEIGHT-35);                                                    //point to a first position
    path.lineTo(playerPosition->x(), MAP_HEIGHT);                                                       //draw a line
    path.cubicTo(playerPosition->x()+35, MAP_HEIGHT-5, playerPosition->x()+35, MAP_HEIGHT-20, playerPosition->x()+70, MAP_HEIGHT);   //draw a cubic the first 2 points make a deformation on the line till the last point
    path.lineTo(playerPosition->x()+70, MAP_HEIGHT-35);                                                 //another line
    painter.drawPath(path);                                                                             //finaly draw the configured path


    painter.setPen(QPen(Qt::darkRed, 2, Qt::SolidLine, Qt::SquareCap));
    painter.setBrush(QBrush(Qt::green, Qt::Dense5Pattern));
    // Paint each packet and check if player catch it
    for(int i = 0; i < packetAdm->getPackets().size(); i++)
    {
        packet* actualPacket = packetAdm->getPackets().at(i);
        painter.drawEllipse(actualPacket->getPosition(), 10, 10);
        painter.drawText(actualPacket->getPosition(), QString::number(actualPacket->getPoints()));
        if(playerPosition->x() < actualPacket->getPosition().x() &&
                actualPacket->getPosition().x() < (playerPosition->x()+70) &&
                (MAP_HEIGHT-50) < actualPacket->getPosition().y() && actualPacket->getPosition().y() < (MAP_HEIGHT-40))
        {
            actualPacket->abort();
            packetsCatched += actualPacket->getPoints();
            QEventLoop loop;
            QTimer::singleShot(100, &loop, SLOT(quit()));
            loop.exec();
            ui->lbCached->setText(QString::number(packetsCatched));
        }
    }

    ui->lbMap->setPixmap(QPixmap::fromImage(*pixmap));

    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.eraseRect(rect());
    painter.end();
}


void MainWindow::on_horizontalScrollBar_valueChanged(int value)
{
    ui->lbLevel->setText(QString::number(value/10));
    timer->setInterval(LEVEL_DELAY/(value/10));                                                         //set the timer interval so it make the packets drop faster
}
