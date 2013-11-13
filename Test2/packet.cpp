#include "packet.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

packet::packet(QObject *parent) :
    QObject(parent)
{
    _moving = false;
    _abort = false;
    srand (time(NULL));
    int x = rand() % 521;
    int speed = rand() % 6 + 1;
    _pos.setX(x); _pos.setY(0);
    _speed = speed;
}


void packet::requestMoving()
{
    mutex.lock();
    _moving = true;
    _abort = false;
    mutex.unlock();

    emit moveRequested();
}

void packet::abort()
{
    if (_moving) {
        _abort = true;
    }
}

void packet::move()
{
    mutex.lock();
    bool abort = _abort;
    mutex.unlock();

    while(!abort)
    {

        mutex.lock();
        abort = _abort;
        mutex.unlock();

        // abort is when program is exited or if player pick up a packet, and limit is when
        // packet cross the limit and player loose it
        if(abort || _pos.y() > 451)
        {
            if(_pos.y() > 451) emit loosePacket();
            break;
        }

        // This will stupidly wait 1 sec doing nothing...
        QEventLoop loop;
        QTimer::singleShot(100, &loop, SLOT(quit()));
        loop.exec();

        mutex.lock();
        _pos.setY(_pos.y()+_speed);
        mutex.unlock();


    }

    mutex.lock();
    _moving = false;
    mutex.unlock();
    emit deletePacket(this);
    emit finished();
}

QPoint packet::getPosition(){
    return _pos;
}
