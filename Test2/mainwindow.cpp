#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QPicture>
#include <QtGui>


const int LEVEL_DELAY = 8000,              //delay to drop a packet
          GUI_REFRESH_DELAY = 20,          //delay to refresh gui
          GARBAGE_COLLECT_DELAY = 10000;   //delay to collet memory garbage
int MAP_WIDTH, MAP_HEIGHT, packetsCatched;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);                      //set up the gui
    this->move(0,0);                        //move window to 0,0 point
    MAP_WIDTH = ui->lbMap->width();         //save the label width
    MAP_HEIGHT =  ui->lbMap->height();      //save the label height
    packetsCatched = 0;                     //set packets cached

    tracker = new trackFigure();          //this track the object in the cam
    tracker->playerPosition = new QPoint(0,0);       //set player position to the beginin
    tracker->MAP_HEIGHT = MAP_HEIGHT;
    tracker->MAP_WIDTH = MAP_WIDTH;

    if(!tracker->capwebcam)                 //if no cam detected do nothing
    {
        return;
    }
    //SIGNALS AND SLOTS connections.....................................................................................................
    packetAdm = new packetAdmin();          //manage the packets drop
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), packetAdm, SLOT(createPacket())); //each 5s will throw a packet
    connect(packetAdm, SIGNAL(crossTheEnd(QString)), ui->lbLost, SLOT(setText(QString))); //refresh lost counter if packet cross the end
    timer->start(LEVEL_DELAY);

    guiTimer = new QTimer(this);            //controls the interval of time to paint the gui and track the object
    connect(guiTimer, SIGNAL(timeout()), tracker, SLOT(trackObjectAndUpdateGUI()));
    connect(tracker, SIGNAL(repaint(QImage)), this, SLOT(repaint(QImage)));
    guiTimer->start(GUI_REFRESH_DELAY);

    pixmap = new QImage(ui->lbMap->width(),ui->lbMap->height(), QImage::Format_ARGB32_Premultiplied);         //create pixmap qith lbMap dimensions
    pixmap->fill(QColor("transparent"));                                                                 //set the filled surface

    cleanerTimer = new QTimer(this);
    cleaner = new QObjectCleanupHandler();
    connect(cleanerTimer, SIGNAL(timeout()), this, SLOT(callGarbageCollector()));
    cleanerTimer->start(GARBAGE_COLLECT_DELAY);
}

MainWindow::~MainWindow()
{
    delete ui;
    cvReleaseImage(&tracker->matOriginal);
    cvReleaseCapture(&tracker->capwebcam);

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
    delete tracker;
    delete timer;
    delete guiTimer;
    delete cleanerTimer;
}

void MainWindow::callGarbageCollector()
{
    cleaner->clear();
}

void::MainWindow::repaint(QImage qimgOriginal)
{
    //after the track object we need to repaint the label
    ui->lbOriginal->setPixmap(QPixmap::fromImage(qimgOriginal).scaled(this->ui->lbOriginal->width(),this->ui->lbOriginal->height(),Qt::KeepAspectRatio));
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

void MainWindow::paintEvent(/*QPaintEvent * e*/){

    QPainter painter(pixmap);
    painter.setPen(QPen(Qt::darkMagenta, 3, Qt::DotLine, Qt::RoundCap));                                //set a pen to draw with dot line and magenta
    painter.setBrush(QBrush(Qt::green, Qt::CrossPattern));                                              //set a brush cross patern and green
    QRectF rectangle(tracker->playerPosition->x(), MAP_HEIGHT-50, 70.0, 20.0);                                   //get a rectangle to draw a elipse
    painter.drawEllipse(rectangle);                                                                     //draw a elipse
    painter.setBrush(QBrush(Qt::darkBlue, Qt::Dense3Pattern));
    QPainterPath path;                                                                                  //with path u can draw wherever u want
    path.moveTo(tracker->playerPosition->x(), MAP_HEIGHT-35);                                                    //point to a first position
    path.lineTo(tracker->playerPosition->x(), MAP_HEIGHT);                                                       //draw a line
    path.cubicTo(tracker->playerPosition->x()+35, MAP_HEIGHT-5, tracker->playerPosition->x()+35, MAP_HEIGHT-20, tracker->playerPosition->x()+70, MAP_HEIGHT);   //draw a cubic the first 2 points make a deformation on the line till the last point
    path.lineTo(tracker->playerPosition->x()+70, MAP_HEIGHT-35);                                                 //another line
    painter.drawPath(path);                                                                             //finaly draw the configured path


    painter.setPen(QPen(Qt::darkRed, 2, Qt::SolidLine, Qt::SquareCap));
    painter.setBrush(QBrush(Qt::green, Qt::Dense5Pattern));
    // Paint each packet and check if player catch it
    for(int i = 0; i < packetAdm->getPackets().size(); i++)
    {
        packet* actualPacket = packetAdm->getPackets().at(i);
        painter.drawEllipse(actualPacket->getPosition(), 10, 10);
        painter.drawText(actualPacket->getPosition(), QString::number(actualPacket->getPoints()));
        if(tracker->playerPosition->x() < actualPacket->getPosition().x() &&
                actualPacket->getPosition().x() < (tracker->playerPosition->x()+70) &&
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

void MainWindow::on_rbTriangle_toggled(bool checked)
{
    tracker->triangleIsChecked = checked;
}
