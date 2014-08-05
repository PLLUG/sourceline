/****************************************************************************
** Meta object code from reading C++ file 'appsettingsdialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/app/ui/appsettingsdialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'appsettingsdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_AppSettingsDialog_t {
    QByteArrayData data[12];
    char stringdata[176];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AppSettingsDialog_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AppSettingsDialog_t qt_meta_stringdata_AppSettingsDialog = {
    {
QT_MOC_LITERAL(0, 0, 17),
QT_MOC_LITERAL(1, 18, 24),
QT_MOC_LITERAL(2, 43, 0),
QT_MOC_LITERAL(3, 44, 9),
QT_MOC_LITERAL(4, 54, 17),
QT_MOC_LITERAL(5, 72, 18),
QT_MOC_LITERAL(6, 91, 19),
QT_MOC_LITERAL(7, 111, 9),
QT_MOC_LITERAL(8, 121, 13),
QT_MOC_LITERAL(9, 135, 12),
QT_MOC_LITERAL(10, 148, 21),
QT_MOC_LITERAL(11, 170, 5)
    },
    "AppSettingsDialog\0signalSettingPageChanged\0"
    "\0pPageName\0signalReadSetting\0"
    "signalWriteSetting\0slotSettingsChanged\0"
    "slotBtnOk\0slotBtnCancel\0slotBtnApply\0"
    "slotOnListItemClicked\0index"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AppSettingsDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       4,    0,   57,    2, 0x06 /* Public */,
       5,    0,   58,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   59,    2, 0x0a /* Public */,
       7,    0,   60,    2, 0x08 /* Private */,
       8,    0,   61,    2, 0x08 /* Private */,
       9,    0,   62,    2, 0x08 /* Private */,
      10,    1,   63,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   11,

       0        // eod
};

void AppSettingsDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AppSettingsDialog *_t = static_cast<AppSettingsDialog *>(_o);
        switch (_id) {
        case 0: _t->signalSettingPageChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->signalReadSetting(); break;
        case 2: _t->signalWriteSetting(); break;
        case 3: _t->slotSettingsChanged(); break;
        case 4: _t->slotBtnOk(); break;
        case 5: _t->slotBtnCancel(); break;
        case 6: _t->slotBtnApply(); break;
        case 7: _t->slotOnListItemClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (AppSettingsDialog::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AppSettingsDialog::signalSettingPageChanged)) {
                *result = 0;
            }
        }
        {
            typedef void (AppSettingsDialog::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AppSettingsDialog::signalReadSetting)) {
                *result = 1;
            }
        }
        {
            typedef void (AppSettingsDialog::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AppSettingsDialog::signalWriteSetting)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject AppSettingsDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_AppSettingsDialog.data,
      qt_meta_data_AppSettingsDialog,  qt_static_metacall, 0, 0}
};


const QMetaObject *AppSettingsDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AppSettingsDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AppSettingsDialog.stringdata))
        return static_cast<void*>(const_cast< AppSettingsDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int AppSettingsDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void AppSettingsDialog::signalSettingPageChanged(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void AppSettingsDialog::signalReadSetting()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void AppSettingsDialog::signalWriteSetting()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE
