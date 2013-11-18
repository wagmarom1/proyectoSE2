/****************************************************************************
** Meta object code from reading C++ file 'packet.h'
**
** Created: Mon Nov 18 12:17:03 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "packet.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'packet.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_packet[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x05,
      24,    7,    7,    7, 0x05,
      35,    7,    7,    7, 0x05,
      60,   49,    7,    7, 0x05,

 // slots: signature, parameters, type, tag, flags
      82,    7,    7,    7, 0x0a,
      96,    7,   89,    7, 0x0a,
     114,    7,  110,    7, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_packet[] = {
    "packet\0\0moveRequested()\0finished()\0"
    "loosePacket()\0lostPacket\0deletePacket(packet*)\0"
    "move()\0QPoint\0getPosition()\0int\0"
    "getPoints()\0"
};

void packet::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        packet *_t = static_cast<packet *>(_o);
        switch (_id) {
        case 0: _t->moveRequested(); break;
        case 1: _t->finished(); break;
        case 2: _t->loosePacket(); break;
        case 3: _t->deletePacket((*reinterpret_cast< packet*(*)>(_a[1]))); break;
        case 4: _t->move(); break;
        case 5: { QPoint _r = _t->getPosition();
            if (_a[0]) *reinterpret_cast< QPoint*>(_a[0]) = _r; }  break;
        case 6: { int _r = _t->getPoints();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData packet::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject packet::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_packet,
      qt_meta_data_packet, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &packet::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *packet::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *packet::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_packet))
        return static_cast<void*>(const_cast< packet*>(this));
    return QObject::qt_metacast(_clname);
}

int packet::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void packet::moveRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void packet::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void packet::loosePacket()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void packet::deletePacket(packet * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
