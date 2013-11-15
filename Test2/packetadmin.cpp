#include "packetadmin.h"
#include <iostream>

packetAdmin::packetAdmin(QObject *parent) :
    QObject(parent)
{
    _lostPackets = 0;
}

void packetAdmin::createPacket()
{
    QThread* newThread = new QThread();
    packet *newPacket = new packet();

    newPacket->moveToThread(newThread);
    connect(newPacket, SIGNAL(moveRequested()), newThread, SLOT(start()));
    connect(newThread, SIGNAL(started()), newPacket, SLOT(move()));
    connect(newPacket, SIGNAL(finished()), newThread, SLOT(quit()), Qt::DirectConnection);              // (1)
    connect(newPacket, SIGNAL(deletePacket(packet*)), this, SLOT(deletePacketFromList(packet*)));
    connect(newPacket, SIGNAL(loosePacket()), this, SLOT(increaseLostPackets()));

    newPacket->requestMoving();
    _packets.append(newPacket);
    _threads.append(newThread);
}

void packetAdmin::deletePacketFromList(packet *lostPacket)
{
    //At this point the signal finished of packet class was emited and the thread asociated with it is quit see(1) above,
    //but still in _threads list and in memory so what we do here is get this thread and remove it from _thread list and memory with delete
    //the same with the packet
    std::cout << QString::number(_packets.size()).toStdString() <<std::endl;
    int ind= _packets.indexOf(lostPacket);
    QThread* thread = _threads.at(ind);
    _packets.removeAt(ind);
    _threads.removeAt(ind);
    delete lostPacket;
    delete thread;
}

void packetAdmin::increaseLostPackets()
{
    _lostPackets ++;
    emit crossTheEnd(QString::number(_lostPackets));
}

 QList<packet *> packetAdmin::getPackets()
 {
     return _packets;
 }

 QList<QThread*> packetAdmin::getThreads()
 {
     return _threads;
 }

 void packetAdmin::resetLostPackets()
 {
     _lostPackets = 0;
 }
