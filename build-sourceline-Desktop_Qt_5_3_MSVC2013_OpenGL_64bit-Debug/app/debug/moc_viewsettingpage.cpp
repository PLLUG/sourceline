/****************************************************************************
** Meta object code from reading C++ file 'viewsettingpage.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/app/ui/viewsettingpage.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'viewsettingpage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ViewSettingPage_t {
    QByteArrayData data[10];
    char stringdata[144];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ViewSettingPage_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ViewSettingPage_t qt_meta_stringdata_ViewSettingPage = {
    {
QT_MOC_LITERAL(0, 0, 15),
QT_MOC_LITERAL(1, 16, 17),
QT_MOC_LITERAL(2, 34, 0),
QT_MOC_LITERAL(3, 35, 5),
QT_MOC_LITERAL(4, 41, 19),
QT_MOC_LITERAL(5, 61, 6),
QT_MOC_LITERAL(6, 68, 21),
QT_MOC_LITERAL(7, 90, 18),
QT_MOC_LITERAL(8, 109, 18),
QT_MOC_LITERAL(9, 128, 15)
    },
    "ViewSettingPage\0signalGetSettings\0\0"
    "pPath\0slotFileViewChanged\0pValue\0"
    "slotEditorViewChanged\0slotRevTreeChanged\0"
    "slotConsoleChanged\0slotTreeChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ViewSettingPage[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   47,    2, 0x0a /* Public */,
       6,    1,   50,    2, 0x0a /* Public */,
       7,    1,   53,    2, 0x0a /* Public */,
       8,    1,   56,    2, 0x0a /* Public */,
       9,    1,   59,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::QVariant,    5,
    QMetaType::Void, QMetaType::QVariant,    5,
    QMetaType::Void, QMetaType::QVariant,    5,
    QMetaType::Void, QMetaType::QVariant,    5,
    QMetaType::Void, QMetaType::QVariant,    5,

       0        // eod
};

void ViewSettingPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ViewSettingPage *_t = static_cast<ViewSettingPage *>(_o);
        switch (_id) {
        case 0: _t->signalGetSettings((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->slotFileViewChanged((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        case 2: _t->slotEditorViewChanged((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        case 3: _t->slotRevTreeChanged((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        case 4: _t->slotConsoleChanged((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        case 5: _t->slotTreeChanged((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ViewSettingPage::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ViewSettingPage::signalGetSettings)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject ViewSettingPage::staticMetaObject = {
    { &SettingsPage::staticMetaObject, qt_meta_stringdata_ViewSettingPage.data,
      qt_meta_data_ViewSettingPage,  qt_static_metacall, 0, 0}
};


const QMetaObject *ViewSettingPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ViewSettingPage::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ViewSettingPage.stringdata))
        return static_cast<void*>(const_cast< ViewSettingPage*>(this));
    return SettingsPage::qt_metacast(_clname);
}

int ViewSettingPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = SettingsPage::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void ViewSettingPage::signalGetSettings(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
