/****************************************************************************
** Meta object code from reading C++ file 'abstractrevisiondelegate.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/app/ui/revisionView/view/abstractrevisiondelegate.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'abstractrevisiondelegate.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_AbstractRevisionDelegate_t {
    QByteArrayData data[11];
    char stringdata0[160];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AbstractRevisionDelegate_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AbstractRevisionDelegate_t qt_meta_stringdata_AbstractRevisionDelegate = {
    {
QT_MOC_LITERAL(0, 0, 24), // "AbstractRevisionDelegate"
QT_MOC_LITERAL(1, 25, 19), // "needRequestFromView"
QT_MOC_LITERAL(2, 45, 0), // ""
QT_MOC_LITERAL(3, 46, 25), // "AbstractRevisionDelegate*"
QT_MOC_LITERAL(4, 72, 4), // "item"
QT_MOC_LITERAL(5, 77, 6), // "commit"
QT_MOC_LITERAL(6, 84, 6), // "branch"
QT_MOC_LITERAL(7, 91, 20), // "updateBubblePosition"
QT_MOC_LITERAL(8, 112, 21), // "commitActionTriggered"
QT_MOC_LITERAL(9, 134, 21), // "branchActionTriggered"
QT_MOC_LITERAL(10, 156, 3) // "Pos"

    },
    "AbstractRevisionDelegate\0needRequestFromView\0"
    "\0AbstractRevisionDelegate*\0item\0commit\0"
    "branch\0updateBubblePosition\0"
    "commitActionTriggered\0branchActionTriggered\0"
    "Pos"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AbstractRevisionDelegate[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       1,   56, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       5,    1,   47,    2, 0x06 /* Public */,
       6,    1,   50,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   53,    2, 0x08 /* Private */,
       8,    0,   54,    2, 0x08 /* Private */,
       9,    0,   55,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 3,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
      10, QMetaType::QPointF, 0x00095103,

       0        // eod
};

void AbstractRevisionDelegate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AbstractRevisionDelegate *_t = static_cast<AbstractRevisionDelegate *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->needRequestFromView((*reinterpret_cast< AbstractRevisionDelegate*(*)>(_a[1]))); break;
        case 1: _t->commit((*reinterpret_cast< AbstractRevisionDelegate*(*)>(_a[1]))); break;
        case 2: _t->branch((*reinterpret_cast< AbstractRevisionDelegate*(*)>(_a[1]))); break;
        case 3: _t->updateBubblePosition(); break;
        case 4: _t->commitActionTriggered(); break;
        case 5: _t->branchActionTriggered(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< AbstractRevisionDelegate* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< AbstractRevisionDelegate* >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< AbstractRevisionDelegate* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (AbstractRevisionDelegate::*_t)(AbstractRevisionDelegate * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AbstractRevisionDelegate::needRequestFromView)) {
                *result = 0;
            }
        }
        {
            typedef void (AbstractRevisionDelegate::*_t)(AbstractRevisionDelegate * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AbstractRevisionDelegate::commit)) {
                *result = 1;
            }
        }
        {
            typedef void (AbstractRevisionDelegate::*_t)(AbstractRevisionDelegate * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AbstractRevisionDelegate::branch)) {
                *result = 2;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        AbstractRevisionDelegate *_t = static_cast<AbstractRevisionDelegate *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QPointF*>(_v) = _t->pos(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        AbstractRevisionDelegate *_t = static_cast<AbstractRevisionDelegate *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setPos(*reinterpret_cast< QPointF*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject AbstractRevisionDelegate::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_AbstractRevisionDelegate.data,
      qt_meta_data_AbstractRevisionDelegate,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *AbstractRevisionDelegate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AbstractRevisionDelegate::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_AbstractRevisionDelegate.stringdata0))
        return static_cast<void*>(const_cast< AbstractRevisionDelegate*>(this));
    if (!strcmp(_clname, "QGraphicsItem"))
        return static_cast< QGraphicsItem*>(const_cast< AbstractRevisionDelegate*>(this));
    if (!strcmp(_clname, "org.qt-project.Qt.QGraphicsItem"))
        return static_cast< QGraphicsItem*>(const_cast< AbstractRevisionDelegate*>(this));
    return QObject::qt_metacast(_clname);
}

int AbstractRevisionDelegate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 1;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void AbstractRevisionDelegate::needRequestFromView(AbstractRevisionDelegate * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void AbstractRevisionDelegate::commit(AbstractRevisionDelegate * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void AbstractRevisionDelegate::branch(AbstractRevisionDelegate * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
