#include "packet.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

packet::packet(QObject *parent) :
    QObject(parent)
{
    _moving = false;                    //initialization of values
    _abort = false;
    srand (time(NULL));                 // PRNG Pseudo Random Number Generator
    _speed = rand() % 6 + 1;            // get a random number between 0-6 and add 1
    _pos.setX(rand() % 521 /*lbMap Width*/);  // set a inicial X position in a random value interval between 0 and lbMap Width
    _pos.setY(0);                       // packets start at y = 0
    _points = rand() % 100;
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

int packet::getPoints(){
    return _points;
}
