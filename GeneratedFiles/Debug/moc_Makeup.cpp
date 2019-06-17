/****************************************************************************
** Meta object code from reading C++ file 'Makeup.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Makeup.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Makeup.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Makeup_t {
    QByteArrayData data[18];
    char stringdata0[160];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Makeup_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Makeup_t qt_meta_stringdata_Makeup = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Makeup"
QT_MOC_LITERAL(1, 7, 10), // "backToMain"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 4), // "quit"
QT_MOC_LITERAL(4, 24, 16), // "updateKinectData"
QT_MOC_LITERAL(5, 41, 7), // "hatList"
QT_MOC_LITERAL(6, 49, 11), // "eardropList"
QT_MOC_LITERAL(7, 61, 12), // "necklaceList"
QT_MOC_LITERAL(8, 74, 12), // "braceletList"
QT_MOC_LITERAL(9, 87, 4), // "back"
QT_MOC_LITERAL(10, 92, 5), // "exitM"
QT_MOC_LITERAL(11, 98, 10), // "widgetList"
QT_MOC_LITERAL(12, 109, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(13, 126, 4), // "item"
QT_MOC_LITERAL(14, 131, 11), // "recieveMode"
QT_MOC_LITERAL(15, 143, 4), // "mode"
QT_MOC_LITERAL(16, 148, 6), // "number"
QT_MOC_LITERAL(17, 155, 4) // "exit"

    },
    "Makeup\0backToMain\0\0quit\0updateKinectData\0"
    "hatList\0eardropList\0necklaceList\0"
    "braceletList\0back\0exitM\0widgetList\0"
    "QListWidgetItem*\0item\0recieveMode\0"
    "mode\0number\0exit"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Makeup[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x06 /* Public */,
       3,    0,   75,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   76,    2, 0x08 /* Private */,
       5,    0,   77,    2, 0x08 /* Private */,
       6,    0,   78,    2, 0x08 /* Private */,
       7,    0,   79,    2, 0x08 /* Private */,
       8,    0,   80,    2, 0x08 /* Private */,
       9,    0,   81,    2, 0x08 /* Private */,
      10,    0,   82,    2, 0x0a /* Public */,
      11,    1,   83,    2, 0x0a /* Public */,
      14,    2,   86,    2, 0x0a /* Public */,
      17,    0,   91,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   15,   16,
    QMetaType::Void,

       0        // eod
};

void Makeup::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Makeup *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->backToMain(); break;
        case 1: _t->quit(); break;
        case 2: _t->updateKinectData(); break;
        case 3: _t->hatList(); break;
        case 4: _t->eardropList(); break;
        case 5: _t->necklaceList(); break;
        case 6: _t->braceletList(); break;
        case 7: _t->back(); break;
        case 8: _t->exitM(); break;
        case 9: _t->widgetList((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 10: _t->recieveMode((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 11: _t->exit(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Makeup::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Makeup::backToMain)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Makeup::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Makeup::quit)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Makeup::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_Makeup.data,
    qt_meta_data_Makeup,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Makeup::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Makeup::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Makeup.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Makeup::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void Makeup::backToMain()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Makeup::quit()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
