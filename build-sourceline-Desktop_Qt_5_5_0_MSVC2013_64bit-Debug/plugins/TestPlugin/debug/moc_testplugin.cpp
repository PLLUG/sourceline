/****************************************************************************
** Meta object code from reading C++ file 'testplugin.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../src/plugins/TestPlugin/testplugin.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/qplugin.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'testplugin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TestPlugin_t {
    QByteArrayData data[1];
    char stringdata0[11];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TestPlugin_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TestPlugin_t qt_meta_stringdata_TestPlugin = {
    {
QT_MOC_LITERAL(0, 0, 10) // "TestPlugin"

    },
    "TestPlugin"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TestPlugin[] = {

 // content:
       7,       // revision
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

void TestPlugin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject TestPlugin::staticMetaObject = {
    { &Plugin::staticMetaObject, qt_meta_stringdata_TestPlugin.data,
      qt_meta_data_TestPlugin,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TestPlugin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TestPlugin::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TestPlugin.stringdata0))
        return static_cast<void*>(const_cast< TestPlugin*>(this));
    if (!strcmp(_clname, "org.PLUG.Qt.Sf.Houd1ny"))
        return static_cast< PluginInterface*>(const_cast< TestPlugin*>(this));
    return Plugin::qt_metacast(_clname);
}

int TestPlugin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Plugin::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}

QT_PLUGIN_METADATA_SECTION const uint qt_section_alignment_dummy = 42;

#ifdef QT_NO_DEBUG

QT_PLUGIN_METADATA_SECTION
static const unsigned char qt_pluginMetaData[] = {
    'Q', 'T', 'M', 'E', 'T', 'A', 'D', 'A', 'T', 'A', ' ', ' ',
    'q',  'b',  'j',  's',  0x01, 0x00, 0x00, 0x00,
    0xbc, 0x01, 0x00, 0x00, 0x0b, 0x00, 0x00, 0x00,
    0xa8, 0x01, 0x00, 0x00, 0x1b, 0x03, 0x00, 0x00,
    0x03, 0x00, 'I',  'I',  'D',  0x00, 0x00, 0x00,
    0x1e, 0x00, 'o',  'r',  'g',  '.',  'q',  't', 
    '-',  'p',  'r',  'o',  'j',  'e',  'c',  't', 
    '.',  'Q',  't',  '.',  'Q',  'D',  'u',  'm', 
    'm',  'y',  'P',  'l',  'u',  'g',  'i',  'n', 
    0x1b, 0x09, 0x00, 0x00, 0x09, 0x00, 'c',  'l', 
    'a',  's',  's',  'N',  'a',  'm',  'e',  0x00,
    0x0a, 0x00, 'T',  'e',  's',  't',  'P',  'l', 
    'u',  'g',  'i',  'n',  0x1a, 0xa0, 0xa0, 0x00,
    0x07, 0x00, 'v',  'e',  'r',  's',  'i',  'o', 
    'n',  0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00,
    0x05, 0x00, 'd',  'e',  'b',  'u',  'g',  0x00,
    0x15, 0x10, 0x00, 0x00, 0x08, 0x00, 'M',  'e', 
    't',  'a',  'D',  'a',  't',  'a',  0x00, 0x00,
    '(',  0x01, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00,
    0x08, 0x01, 0x00, 0x00, 0x9b, 0x03, 0x00, 0x00,
    0x08, 0x00, 'c',  'a',  't',  'e',  'g',  'o', 
    'r',  'y',  0x00, 0x00, 0x0b, 0x00, 'T',  'e', 
    's',  't',  ' ',  'P',  'l',  'u',  'g',  'i', 
    'n',  0x00, 0x00, 0x00, 0x9b, 0x07, 0x00, 0x00,
    0x07, 0x00, 'v',  'e',  'r',  's',  'i',  'o', 
    'n',  0x00, 0x00, 0x00, 0x05, 0x00, '0',  '.', 
    '0',  '.',  '1',  0x00, 0x1b, 0x0b, 0x00, 0x00,
    0x0b, 0x00, 'd',  'e',  's',  'c',  'r',  'i', 
    'p',  't',  'i',  'o',  'n',  0x00, 0x00, 0x00,
    0x0b, 0x00, 't',  'e',  's',  't',  ' ',  'p', 
    'l',  'u',  'g',  'i',  'n',  0x00, 0x00, 0x00,
    0x9b, 0x0f, 0x00, 0x00, 0x0b, 0x00, 'a',  's', 
    'd',  'a',  's',  'a',  's',  'd',  'a',  's', 
    'd',  0x00, 0x00, 0x00, 0x0a, 0x00, 'l',  'a', 
    'l',  'a',  'l',  'a',  'l',  'a',  'l',  'a', 
    0x9b, 0x13, 0x00, 0x00, 0x0b, 0x00, 'd',  'c', 
    'd',  'e',  'm',  'c',  'm',  'l',  'l',  'k', 
    'l',  0x00, 0x00, 0x00, 0x0a, 0x00, 'b',  'e', 
    'b',  'e',  'b',  'e',  'b',  'e',  'b',  'e', 
    0x9b, 0x17, 0x00, 0x00, 0x0b, 0x00, 'd',  'l', 
    'c',  'k',  'k',  'c',  'n',  'l',  'r',  'l', 
    'm',  0x00, 0x00, 0x00, 0x0a, 0x00, 'f',  'u', 
    'f',  'u',  'f',  'u',  'f',  'u',  'f',  'u', 
    0x9b, 0x1b, 0x00, 0x00, 0x0b, 0x00, 'n',  'j', 
    'n',  'k',  'n',  'k',  'k',  'm',  'k',  'l', 
    'm',  0x00, 0x00, 0x00, 0x0a, 0x00, 'h',  'o', 
    'h',  'o',  'h',  'o',  'h',  'o',  'h',  'o', 
    0x9b, 0x1f, 0x00, 0x00, 0x0b, 0x00, 'd',  'n', 
    'n',  'u',  'n',  'i',  'o',  'n',  'o',  'm', 
    'e',  0x00, 0x00, 0x00, 0x0a, 0x00, 'q',  'a', 
    'q',  'a',  'q',  'a',  'q',  'a',  'q',  'a', 
    'h',  0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00,
    0x88, 0x00, 0x00, 0x00, 'D',  0x00, 0x00, 0x00,
    0xa8, 0x00, 0x00, 0x00, 0xe8, 0x00, 0x00, 0x00,
    0xc8, 0x00, 0x00, 0x00, ',',  0x00, 0x00, 0x00,
    0x0c, 0x00, 0x00, 0x00, 'p',  0x00, 0x00, 0x00,
    '8',  0x00, 0x00, 0x00, 'd',  0x00, 0x00, 0x00,
    'T',  0x00, 0x00, 0x00
};

#else // QT_NO_DEBUG

QT_PLUGIN_METADATA_SECTION
static const unsigned char qt_pluginMetaData[] = {
    'Q', 'T', 'M', 'E', 'T', 'A', 'D', 'A', 'T', 'A', ' ', ' ',
    'q',  'b',  'j',  's',  0x01, 0x00, 0x00, 0x00,
    0xbc, 0x01, 0x00, 0x00, 0x0b, 0x00, 0x00, 0x00,
    0xa8, 0x01, 0x00, 0x00, 0x1b, 0x03, 0x00, 0x00,
    0x03, 0x00, 'I',  'I',  'D',  0x00, 0x00, 0x00,
    0x1e, 0x00, 'o',  'r',  'g',  '.',  'q',  't', 
    '-',  'p',  'r',  'o',  'j',  'e',  'c',  't', 
    '.',  'Q',  't',  '.',  'Q',  'D',  'u',  'm', 
    'm',  'y',  'P',  'l',  'u',  'g',  'i',  'n', 
    0x15, 0x09, 0x00, 0x00, 0x08, 0x00, 'M',  'e', 
    't',  'a',  'D',  'a',  't',  'a',  0x00, 0x00,
    '(',  0x01, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00,
    0x08, 0x01, 0x00, 0x00, 0x9b, 0x03, 0x00, 0x00,
    0x08, 0x00, 'c',  'a',  't',  'e',  'g',  'o', 
    'r',  'y',  0x00, 0x00, 0x0b, 0x00, 'T',  'e', 
    's',  't',  ' ',  'P',  'l',  'u',  'g',  'i', 
    'n',  0x00, 0x00, 0x00, 0x9b, 0x07, 0x00, 0x00,
    0x07, 0x00, 'v',  'e',  'r',  's',  'i',  'o', 
    'n',  0x00, 0x00, 0x00, 0x05, 0x00, '0',  '.', 
    '0',  '.',  '1',  0x00, 0x1b, 0x0b, 0x00, 0x00,
    0x0b, 0x00, 'd',  'e',  's',  'c',  'r',  'i', 
    'p',  't',  'i',  'o',  'n',  0x00, 0x00, 0x00,
    0x0b, 0x00, 't',  'e',  's',  't',  ' ',  'p', 
    'l',  'u',  'g',  'i',  'n',  0x00, 0x00, 0x00,
    0x9b, 0x0f, 0x00, 0x00, 0x0b, 0x00, 'a',  's', 
    'd',  'a',  's',  'a',  's',  'd',  'a',  's', 
    'd',  0x00, 0x00, 0x00, 0x0a, 0x00, 'l',  'a', 
    'l',  'a',  'l',  'a',  'l',  'a',  'l',  'a', 
    0x9b, 0x13, 0x00, 0x00, 0x0b, 0x00, 'd',  'c', 
    'd',  'e',  'm',  'c',  'm',  'l',  'l',  'k', 
    'l',  0x00, 0x00, 0x00, 0x0a, 0x00, 'b',  'e', 
    'b',  'e',  'b',  'e',  'b',  'e',  'b',  'e', 
    0x9b, 0x17, 0x00, 0x00, 0x0b, 0x00, 'd',  'l', 
    'c',  'k',  'k',  'c',  'n',  'l',  'r',  'l', 
    'm',  0x00, 0x00, 0x00, 0x0a, 0x00, 'f',  'u', 
    'f',  'u',  'f',  'u',  'f',  'u',  'f',  'u', 
    0x9b, 0x1b, 0x00, 0x00, 0x0b, 0x00, 'n',  'j', 
    'n',  'k',  'n',  'k',  'k',  'm',  'k',  'l', 
    'm',  0x00, 0x00, 0x00, 0x0a, 0x00, 'h',  'o', 
    'h',  'o',  'h',  'o',  'h',  'o',  'h',  'o', 
    0x9b, 0x1f, 0x00, 0x00, 0x0b, 0x00, 'd',  'n', 
    'n',  'u',  'n',  'i',  'o',  'n',  'o',  'm', 
    'e',  0x00, 0x00, 0x00, 0x0a, 0x00, 'q',  'a', 
    'q',  'a',  'q',  'a',  'q',  'a',  'q',  'a', 
    'h',  0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00,
    0x88, 0x00, 0x00, 0x00, 'D',  0x00, 0x00, 0x00,
    0xa8, 0x00, 0x00, 0x00, 0xe8, 0x00, 0x00, 0x00,
    0xc8, 0x00, 0x00, 0x00, ',',  0x00, 0x00, 0x00,
    0x1b, '0',  0x00, 0x00, 0x09, 0x00, 'c',  'l', 
    'a',  's',  's',  'N',  'a',  'm',  'e',  0x00,
    0x0a, 0x00, 'T',  'e',  's',  't',  'P',  'l', 
    'u',  'g',  'i',  'n',  '1',  0x00, 0x00, 0x00,
    0x05, 0x00, 'd',  'e',  'b',  'u',  'g',  0x00,
    0x1a, 0xa0, 0xa0, 0x00, 0x07, 0x00, 'v',  'e', 
    'r',  's',  'i',  'o',  'n',  0x00, 0x00, 0x00,
    0x0c, 0x00, 0x00, 0x00, '8',  0x00, 0x00, 0x00,
    'p',  0x01, 0x00, 0x00, 0x8c, 0x01, 0x00, 0x00,
    0x98, 0x01, 0x00, 0x00
};
#endif // QT_NO_DEBUG

QT_MOC_EXPORT_PLUGIN(TestPlugin, TestPlugin)

QT_END_MOC_NAMESPACE
