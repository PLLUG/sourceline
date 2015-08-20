/****************************************************************************
** Meta object code from reading C++ file 'consoleview.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/app/ui/consoleview.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'consoleview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ConsoleView_t {
    QByteArrayData data[9];
    char stringdata0[97];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ConsoleView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ConsoleView_t qt_meta_stringdata_ConsoleView = {
    {
QT_MOC_LITERAL(0, 0, 11), // "ConsoleView"
QT_MOC_LITERAL(1, 12, 18), // "slotSetConsolePath"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 5), // "pPath"
QT_MOC_LITERAL(4, 38, 21), // "slotReadConsoleOutput"
QT_MOC_LITERAL(5, 60, 8), // "slotExec"
QT_MOC_LITERAL(6, 69, 3), // "cmd"
QT_MOC_LITERAL(7, 73, 19), // "slotPrintWorkingDir"
QT_MOC_LITERAL(8, 93, 3) // "dir"

    },
    "ConsoleView\0slotSetConsolePath\0\0pPath\0"
    "slotReadConsoleOutput\0slotExec\0cmd\0"
    "slotPrintWorkingDir\0dir"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ConsoleView[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x0a /* Public */,
       4,    0,   42,    2, 0x0a /* Public */,
       5,    1,   43,    2, 0x0a /* Public */,
       7,    1,   46,    2, 0x08 /* Private */,
       7,    0,   49,    2, 0x28 /* Private | MethodCloned */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void,

       0        // eod
};

void ConsoleView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ConsoleView *_t = static_cast<ConsoleView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slotSetConsolePath((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->slotReadConsoleOutput(); break;
        case 2: _t->slotExec((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->slotPrintWorkingDir((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->slotPrintWorkingDir(); break;
        default: ;
        }
    }
}

const QMetaObject ConsoleView::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ConsoleView.data,
      qt_meta_data_ConsoleView,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ConsoleView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ConsoleView::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ConsoleView.stringdata0))
        return static_cast<void*>(const_cast< ConsoleView*>(this));
    return QWidget::qt_metacast(_clname);
}

int ConsoleView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
