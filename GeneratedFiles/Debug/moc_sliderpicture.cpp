/****************************************************************************
** Meta object code from reading C++ file 'sliderpicture.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../sliderpicture.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sliderpicture.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SliderPicture_t {
    QByteArrayData data[14];
    char stringdata0[126];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SliderPicture_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SliderPicture_t qt_meta_stringdata_SliderPicture = {
    {
QT_MOC_LITERAL(0, 0, 13), // "SliderPicture"
QT_MOC_LITERAL(1, 14, 12), // "kinectWindow"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 4), // "mode"
QT_MOC_LITERAL(4, 33, 6), // "number"
QT_MOC_LITERAL(5, 40, 4), // "quit"
QT_MOC_LITERAL(6, 45, 17), // "changeCurrentPage"
QT_MOC_LITERAL(7, 63, 9), // "PixLabel*"
QT_MOC_LITERAL(8, 73, 5), // "label"
QT_MOC_LITERAL(9, 79, 14), // "changeCategory"
QT_MOC_LITERAL(10, 94, 5), // "exitM"
QT_MOC_LITERAL(11, 100, 4), // "exit"
QT_MOC_LITERAL(12, 105, 9), // "nowWindow"
QT_MOC_LITERAL(13, 115, 10) // "nextWindow"

    },
    "SliderPicture\0kinectWindow\0\0mode\0"
    "number\0quit\0changeCurrentPage\0PixLabel*\0"
    "label\0changeCategory\0exitM\0exit\0"
    "nowWindow\0nextWindow"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SliderPicture[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   54,    2, 0x06 /* Public */,
       5,    0,   59,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   60,    2, 0x08 /* Private */,
       9,    1,   63,    2, 0x08 /* Private */,
      10,    0,   66,    2, 0x0a /* Public */,
      11,    0,   67,    2, 0x0a /* Public */,
      12,    0,   68,    2, 0x0a /* Public */,
      13,    0,   69,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SliderPicture::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SliderPicture *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->kinectWindow((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->quit(); break;
        case 2: _t->changeCurrentPage((*reinterpret_cast< PixLabel*(*)>(_a[1]))); break;
        case 3: _t->changeCategory((*reinterpret_cast< PixLabel*(*)>(_a[1]))); break;
        case 4: _t->exitM(); break;
        case 5: _t->exit(); break;
        case 6: _t->nowWindow(); break;
        case 7: _t->nextWindow(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< PixLabel* >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< PixLabel* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SliderPicture::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SliderPicture::kinectWindow)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SliderPicture::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SliderPicture::quit)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SliderPicture::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_SliderPicture.data,
    qt_meta_data_SliderPicture,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SliderPicture::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SliderPicture::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SliderPicture.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int SliderPicture::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void SliderPicture::kinectWindow(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SliderPicture::quit()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
struct qt_meta_stringdata_PushButton_t {
    QByteArrayData data[1];
    char stringdata0[11];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PushButton_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PushButton_t qt_meta_stringdata_PushButton = {
    {
QT_MOC_LITERAL(0, 0, 10) // "PushButton"

    },
    "PushButton"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PushButton[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void PushButton::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject PushButton::staticMetaObject = { {
    &QPushButton::staticMetaObject,
    qt_meta_stringdata_PushButton.data,
    qt_meta_data_PushButton,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PushButton::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PushButton::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PushButton.stringdata0))
        return static_cast<void*>(this);
    return QPushButton::qt_metacast(_clname);
}

int PushButton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPushButton::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_PixLabel_t {
    QByteArrayData data[4];
    char stringdata0[37];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PixLabel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PixLabel_t qt_meta_stringdata_PixLabel = {
    {
QT_MOC_LITERAL(0, 0, 8), // "PixLabel"
QT_MOC_LITERAL(1, 9, 16), // "signalLabelPress"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 9) // "PixLabel*"

    },
    "PixLabel\0signalLabelPress\0\0PixLabel*"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PixLabel[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,

       0        // eod
};

void PixLabel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PixLabel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalLabelPress((*reinterpret_cast< PixLabel*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< PixLabel* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PixLabel::*)(PixLabel * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PixLabel::signalLabelPress)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject PixLabel::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_PixLabel.data,
    qt_meta_data_PixLabel,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PixLabel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PixLabel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PixLabel.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int PixLabel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void PixLabel::signalLabelPress(PixLabel * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
