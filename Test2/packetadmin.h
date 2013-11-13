#ifndef PACKETADMIN_H
#define PACKETADMIN_H

#include "packet.h"
#include <QList>
#include <QThread>


class packetAdmin : public QObject
{
    Q_OBJECT
public:
    explicit packetAdmin(QObject *parent = 0);
    QList<packet*> getPackets();
    QList<QThread*> getThreads();
    void resetLostPackets();

private:
    int _lostPackets;
    QList<packet*> _packets;
    QList<QThread*> _threads;

signals:
    void crossTheEnd(const QString &value); //when some packet reach the end a counter on mainwindow gui change _lostPackets is sended

public slots:
    void createPacket();
    void increaseLostPackets();
    void deletePacketFromList(packet* lostPacket);
};

#endif // PACKETADMIN_H
