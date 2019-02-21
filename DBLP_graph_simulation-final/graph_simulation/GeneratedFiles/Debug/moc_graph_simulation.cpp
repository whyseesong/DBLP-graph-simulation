/****************************************************************************
** Meta object code from reading C++ file 'graph_simulation.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../graph_simulation.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'graph_simulation.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_streamObject_t {
    QByteArrayData data[3];
    char stringdata0[32];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_streamObject_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_streamObject_t qt_meta_stringdata_streamObject = {
    {
QT_MOC_LITERAL(0, 0, 12), // "streamObject"
QT_MOC_LITERAL(1, 13, 17), // "loadByThread_Slot"
QT_MOC_LITERAL(2, 31, 0) // ""

    },
    "streamObject\0loadByThread_Slot\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_streamObject[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void streamObject::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        streamObject *_t = static_cast<streamObject *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->loadByThread_Slot(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject streamObject::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_streamObject.data,
      qt_meta_data_streamObject,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *streamObject::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *streamObject::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_streamObject.stringdata0))
        return static_cast<void*>(const_cast< streamObject*>(this));
    return QObject::qt_metacast(_clname);
}

int streamObject::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
struct qt_meta_stringdata_graph_simulation_t {
    QByteArrayData data[14];
    char stringdata0[240];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_graph_simulation_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_graph_simulation_t qt_meta_stringdata_graph_simulation = {
    {
QT_MOC_LITERAL(0, 0, 16), // "graph_simulation"
QT_MOC_LITERAL(1, 17, 18), // "main_loadFile_Slot"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 21), // "main_topk_author_Slot"
QT_MOC_LITERAL(4, 59, 27), // "main_search_one_author_Slot"
QT_MOC_LITERAL(5, 87, 27), // "main_search_two_author_Slot"
QT_MOC_LITERAL(6, 115, 19), // "main_animation_Slot"
QT_MOC_LITERAL(7, 135, 19), // "main_recommend_Slot"
QT_MOC_LITERAL(8, 155, 19), // "read_coauthor_graph"
QT_MOC_LITERAL(9, 175, 5), // "Graph"
QT_MOC_LITERAL(10, 181, 14), // "std::ifstream&"
QT_MOC_LITERAL(11, 196, 2), // "in"
QT_MOC_LITERAL(12, 199, 28), // "dataStreamConfirmBtn_clicked"
QT_MOC_LITERAL(13, 228, 11) // "tictoc_Slot"

    },
    "graph_simulation\0main_loadFile_Slot\0"
    "\0main_topk_author_Slot\0"
    "main_search_one_author_Slot\0"
    "main_search_two_author_Slot\0"
    "main_animation_Slot\0main_recommend_Slot\0"
    "read_coauthor_graph\0Graph\0std::ifstream&\0"
    "in\0dataStreamConfirmBtn_clicked\0"
    "tictoc_Slot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_graph_simulation[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x0a /* Public */,
       3,    0,   60,    2, 0x0a /* Public */,
       4,    0,   61,    2, 0x0a /* Public */,
       5,    0,   62,    2, 0x0a /* Public */,
       6,    0,   63,    2, 0x0a /* Public */,
       7,    0,   64,    2, 0x0a /* Public */,
       8,    1,   65,    2, 0x0a /* Public */,
      12,    0,   68,    2, 0x0a /* Public */,
      13,    0,   69,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    0x80000000 | 9, 0x80000000 | 10,   11,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void graph_simulation::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        graph_simulation *_t = static_cast<graph_simulation *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->main_loadFile_Slot(); break;
        case 1: _t->main_topk_author_Slot(); break;
        case 2: _t->main_search_one_author_Slot(); break;
        case 3: _t->main_search_two_author_Slot(); break;
        case 4: _t->main_animation_Slot(); break;
        case 5: _t->main_recommend_Slot(); break;
        case 6: { Graph _r = _t->read_coauthor_graph((*reinterpret_cast< std::ifstream(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< Graph*>(_a[0]) = _r; }  break;
        case 7: _t->dataStreamConfirmBtn_clicked(); break;
        case 8: _t->tictoc_Slot(); break;
        default: ;
        }
    }
}

const QMetaObject graph_simulation::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_graph_simulation.data,
      qt_meta_data_graph_simulation,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *graph_simulation::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *graph_simulation::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_graph_simulation.stringdata0))
        return static_cast<void*>(const_cast< graph_simulation*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int graph_simulation::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
