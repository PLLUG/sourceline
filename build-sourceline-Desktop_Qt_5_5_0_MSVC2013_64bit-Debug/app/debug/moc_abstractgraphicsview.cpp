/****************************************************************************
** Meta object code from reading C++ file 'abstractgraphicsview.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/app/ui/revisionView/view/abstractgraphicsview.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'abstractgraphicsview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_AbstractGraphicsView_t {
    QByteArrayData data[10];
    char stringdata0[128];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AbstractGraphicsView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AbstractGraphicsView_t qt_meta_stringdata_AbstractGraphicsView = {
    {
QT_MOC_LITERAL(0, 0, 20), // "AbstractGraphicsView"
QT_MOC_LITERAL(1, 21, 8), // "updateUI"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 18), // "slotRequestForItem"
QT_MOC_LITERAL(4, 50, 25), // "AbstractRevisionDelegate*"
QT_MOC_LITERAL(5, 76, 4), // "item"
QT_MOC_LITERAL(6, 81, 16), // "slotModelChanged"
QT_MOC_LITERAL(7, 98, 13), // "branchClicked"
QT_MOC_LITERAL(8, 112, 1), // "d"
QT_MOC_LITERAL(9, 114, 13) // "commitClicked"

    },
    "AbstractGraphicsView\0updateUI\0\0"
    "slotRequestForItem\0AbstractRevisionDelegate*\0"
    "item\0slotModelChanged\0branchClicked\0"
    "d\0commitClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AbstractGraphicsView[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   40,    2, 0x08 /* Private */,
       6,    0,   43,    2, 0x08 /* Private */,
       7,    1,   44,    2, 0x08 /* Private */,
       9,    1,   47,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    8,
    QMetaType::Void, 0x80000000 | 4,    2,

       0        // eod
};

void AbstractGraphicsView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AbstractGraphicsView *_t = static_cast<AbstractGraphicsView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateUI(); break;
        case 1: _t->slotRequestForItem((*reinterpret_cast< AbstractRevisionDelegate*(*)>(_a[1]))); break;
        case 2: _t->slotModelChanged(); break;
        case 3: _t->branchClicked((*reinterpret_cast< AbstractRevisionDelegate*(*)>(_a[1]))); break;
        case 4: _t->commitClicked((*reinterpret_cast< AbstractRevisionDelegate*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (AbstractGraphicsView::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AbstractGraphicsView::updateUI)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject AbstractGraphicsView::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_AbstractGraphicsView.data,
      qt_meta_data_AbstractGraphicsView,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *AbstractGraphicsView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AbstractGraphicsView::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_AbstractGraphicsView.stringdata0))
        return static_cast<void*>(const_cast< AbstractGraphicsView*>(this));
    if (!strcmp(_clname, "QGraphicsItem"))
        return static_cast< QGraphicsItem*>(const_cast< AbstractGraphicsView*>(this));
    if (!strcmp(_clname, "org.qt-project.Qt.QGraphicsItem"))
        return static_cast< QGraphicsItem*>(const_cast< AbstractGraphicsView*>(this));
    return QObject::qt_metacast(_clname);
}

int AbstractGraphicsView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void AbstractGraphicsView::updateUI()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
