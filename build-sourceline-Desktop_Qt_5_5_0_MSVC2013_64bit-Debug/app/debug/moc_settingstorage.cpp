/****************************************************************************
** Meta object code from reading C++ file 'settingstorage.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/app/settings_dialog/settingstorage.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'settingstorage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SettingStorage_t {
    QByteArrayData data[7];
    char stringdata0[91];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SettingStorage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SettingStorage_t qt_meta_stringdata_SettingStorage = {
    {
QT_MOC_LITERAL(0, 0, 14), // "SettingStorage"
QT_MOC_LITERAL(1, 15, 17), // "signalSetSettings"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 9), // "pHashData"
QT_MOC_LITERAL(4, 44, 16), // "slotSaveSettings"
QT_MOC_LITERAL(5, 61, 12), // "pSettingPath"
QT_MOC_LITERAL(6, 74, 16) // "slotLoadSettings"

    },
    "SettingStorage\0signalSetSettings\0\0"
    "pHashData\0slotSaveSettings\0pSettingPath\0"
    "slotLoadSettings"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SettingStorage[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    2,   32,    2, 0x0a /* Public */,
       6,    1,   37,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QVariantMap,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QVariantMap,    5,    3,
    QMetaType::Void, QMetaType::QString,    5,

       0        // eod
};

void SettingStorage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SettingStorage *_t = static_cast<SettingStorage *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalSetSettings((*reinterpret_cast< QMap<QString,QVariant>(*)>(_a[1]))); break;
        case 1: _t->slotSaveSettings((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QMap<QString,QVariant>(*)>(_a[2]))); break;
        case 2: _t->slotLoadSettings((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (SettingStorage::*_t)(QMap<QString,QVariant> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SettingStorage::signalSetSettings)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject SettingStorage::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_SettingStorage.data,
      qt_meta_data_SettingStorage,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *SettingStorage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SettingStorage::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_SettingStorage.stringdata0))
        return static_cast<void*>(const_cast< SettingStorage*>(this));
    return QObject::qt_metacast(_clname);
}

int SettingStorage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void SettingStorage::signalSetSettings(QMap<QString,QVariant> _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
