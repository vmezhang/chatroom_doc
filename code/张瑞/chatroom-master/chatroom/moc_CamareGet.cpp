/****************************************************************************
** Meta object code from reading C++ file 'CamareGet.h'
**
** Created: Thu May 29 10:41:20 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "include/CamareGet.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CamareGet.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CamaraGet[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x0a,
      24,   10,   10,   10, 0x0a,
      36,   10,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CamaraGet[] = {
    "CamaraGet\0\0openCamara()\0readFarme()\0"
    "closeCamara()\0"
};

void CamaraGet::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CamaraGet *_t = static_cast<CamaraGet *>(_o);
        switch (_id) {
        case 0: _t->openCamara(); break;
        case 1: _t->readFarme(); break;
        case 2: _t->closeCamara(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData CamaraGet::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CamaraGet::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata_CamaraGet,
      qt_meta_data_CamaraGet, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CamaraGet::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CamaraGet::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CamaraGet::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CamaraGet))
        return static_cast<void*>(const_cast< CamaraGet*>(this));
    return QLabel::qt_metacast(_clname);
}

int CamaraGet::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
