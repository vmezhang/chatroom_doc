/****************************************************************************
** Meta object code from reading C++ file 'ChatWidget.h'
**
** Created: Thu May 29 10:41:18 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "include/ChatWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ChatWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ChatWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x0a,
      23,   11,   11,   11, 0x0a,
      34,   11,   11,   11, 0x0a,
      47,   11,   11,   11, 0x0a,
      63,   11,   11,   11, 0x0a,
      75,   11,   11,   11, 0x0a,
      87,   11,   11,   11, 0x0a,
     101,   11,   11,   11, 0x0a,
     116,   11,   11,   11, 0x0a,
     132,   11,   11,   11, 0x0a,
     155,  143,   11,   11, 0x0a,
     193,  188,   11,   11, 0x2a,
     218,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ChatWidget[] = {
    "ChatWidget\0\0fontSize()\0fontBold()\0"
    "fontItalic()\0fontUnderline()\0fontColor()\0"
    "openVideo()\0insertImage()\0saveChatInfo()\0"
    "clearChatInfo()\0sendSlot()\0type,ipAddr\0"
    "sendMessage(MessageType,QString)\0type\0"
    "sendMessage(MessageType)\0recvMessage()\0"
};

void ChatWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ChatWidget *_t = static_cast<ChatWidget *>(_o);
        switch (_id) {
        case 0: _t->fontSize(); break;
        case 1: _t->fontBold(); break;
        case 2: _t->fontItalic(); break;
        case 3: _t->fontUnderline(); break;
        case 4: _t->fontColor(); break;
        case 5: _t->openVideo(); break;
        case 6: _t->insertImage(); break;
        case 7: _t->saveChatInfo(); break;
        case 8: _t->clearChatInfo(); break;
        case 9: _t->sendSlot(); break;
        case 10: _t->sendMessage((*reinterpret_cast< MessageType(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 11: _t->sendMessage((*reinterpret_cast< MessageType(*)>(_a[1]))); break;
        case 12: _t->recvMessage(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ChatWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ChatWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ChatWidget,
      qt_meta_data_ChatWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ChatWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ChatWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ChatWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ChatWidget))
        return static_cast<void*>(const_cast< ChatWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int ChatWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
