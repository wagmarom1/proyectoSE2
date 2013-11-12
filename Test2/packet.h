#ifndef PACKET_H
#define PACKET_H

#include <QPoint>
#include <QMutex>
#include <QTimer>
#include <QEventLoop>

class packet :public QObject
{
    Q_OBJECT
public:
    explicit packet(QObject *parent = 0);
    void requestMoving();
    void abort();


private:
    QPoint _pos;                            //actual position of packet
    float _speed;                           //speed of packet

    bool _moving;                           //to indicate if moving
    bool _abort;                            //to abort threads when exiting
    QMutex mutex;                           //to lock critic regions

signals:
    void moveRequested();                   //when packed admin request its start
    void finished();                        //tell the thread that it finish
    void loosePacket();                     //when player loose a packet, we need to infor to packedAdmin

public slots:
    void move();
    QPoint getPosition();
};

#endif // PACKET_H
