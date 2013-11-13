#include "packetadmin.h"


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
    connect(newPacket, SIGNAL(finished()), newThread, SLOT(quit()), Qt::DirectConnection);
    connect(newPacket, SIGNAL(deletePacket(packet*)), this, SLOT(deletePacketFromList(packet*)));
    connect(newPacket, SIGNAL(loosePacket()), this, SLOT(increaseLostPackets()));

    newPacket->requestMoving();
    _packets.append(newPacket);
    _threads.append(newThread);
}

void packetAdmin::deletePacketFromList(packet *lostPacket)
{
    _packets.removeOne(lostPacket);
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
