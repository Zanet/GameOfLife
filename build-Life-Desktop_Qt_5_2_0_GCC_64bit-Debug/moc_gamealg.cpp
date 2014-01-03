/****************************************************************************
** Meta object code from reading C++ file 'gamealg.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Life/gamealg.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gamealg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_GameAlg_t {
    QByteArrayData data[17];
    char stringdata[142];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_GameAlg_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_GameAlg_t qt_meta_stringdata_GameAlg = {
    {
QT_MOC_LITERAL(0, 0, 7),
QT_MOC_LITERAL(1, 8, 12),
QT_MOC_LITERAL(2, 21, 0),
QT_MOC_LITERAL(3, 22, 5),
QT_MOC_LITERAL(4, 28, 9),
QT_MOC_LITERAL(5, 38, 11),
QT_MOC_LITERAL(6, 50, 3),
QT_MOC_LITERAL(7, 54, 6),
QT_MOC_LITERAL(8, 61, 4),
QT_MOC_LITERAL(9, 66, 12),
QT_MOC_LITERAL(10, 79, 12),
QT_MOC_LITERAL(11, 92, 8),
QT_MOC_LITERAL(12, 101, 9),
QT_MOC_LITERAL(13, 111, 4),
QT_MOC_LITERAL(14, 116, 10),
QT_MOC_LITERAL(15, 127, 11),
QT_MOC_LITERAL(16, 139, 1)
    },
    "GameAlg\0ChangeStatus\0\0feeds\0iteration\0"
    "CellChanged\0row\0column\0life\0NewDimension\0"
    "CellModified\0SetTimer\0StopTimer\0Step\0"
    "SingleStep\0FeedsStatus\0f\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GameAlg[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   59,    2, 0x06,
       5,    3,   64,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
       9,    2,   71,    2, 0x08,
      10,    3,   76,    2, 0x08,
      11,    0,   83,    2, 0x08,
      12,    0,   84,    2, 0x08,
      13,    0,   85,    2, 0x08,
      14,    0,   86,    2, 0x08,
      15,    1,   87,    2, 0x08,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Bool,    6,    7,    8,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    6,    7,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Bool,    6,    7,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   16,

       0        // eod
};

void GameAlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GameAlg *_t = static_cast<GameAlg *>(_o);
        switch (_id) {
        case 0: _t->ChangeStatus((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->CellChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 2: _t->NewDimension((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->CellModified((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 4: _t->SetTimer(); break;
        case 5: _t->StopTimer(); break;
        case 6: _t->Step(); break;
        case 7: _t->SingleStep(); break;
        case 8: _t->FeedsStatus((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (GameAlg::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GameAlg::ChangeStatus)) {
                *result = 0;
            }
        }
        {
            typedef void (GameAlg::*_t)(int , int , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GameAlg::CellChanged)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject GameAlg::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_GameAlg.data,
      qt_meta_data_GameAlg,  qt_static_metacall, 0, 0}
};


const QMetaObject *GameAlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GameAlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GameAlg.stringdata))
        return static_cast<void*>(const_cast< GameAlg*>(this));
    return QObject::qt_metacast(_clname);
}

int GameAlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void GameAlg::ChangeStatus(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GameAlg::CellChanged(int _t1, int _t2, bool _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
