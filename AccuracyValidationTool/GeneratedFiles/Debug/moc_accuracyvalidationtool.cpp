/****************************************************************************
** Meta object code from reading C++ file 'accuracyvalidationtool.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../accuracyvalidationtool.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'accuracyvalidationtool.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AccuracyValidationTool_t {
    QByteArrayData data[15];
    char stringdata0[235];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AccuracyValidationTool_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AccuracyValidationTool_t qt_meta_stringdata_AccuracyValidationTool = {
    {
QT_MOC_LITERAL(0, 0, 22), // "AccuracyValidationTool"
QT_MOC_LITERAL(1, 23, 15), // "slot_openAVideo"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 17), // "slot_setFrameRate"
QT_MOC_LITERAL(4, 58, 22), // "slot_setReportInterval"
QT_MOC_LITERAL(5, 81, 17), // "slot_setStartTime"
QT_MOC_LITERAL(6, 99, 17), // "slot_HSliderMoved"
QT_MOC_LITERAL(7, 117, 5), // "value"
QT_MOC_LITERAL(8, 123, 20), // "slot_HSliderReleased"
QT_MOC_LITERAL(9, 144, 15), // "slot_videoSpeed"
QT_MOC_LITERAL(10, 160, 5), // "index"
QT_MOC_LITERAL(11, 166, 17), // "slot_countInMinus"
QT_MOC_LITERAL(12, 184, 18), // "slot_countOutMinus"
QT_MOC_LITERAL(13, 203, 15), // "slot_outputData"
QT_MOC_LITERAL(14, 219, 15) // "slot_closeVideo"

    },
    "AccuracyValidationTool\0slot_openAVideo\0"
    "\0slot_setFrameRate\0slot_setReportInterval\0"
    "slot_setStartTime\0slot_HSliderMoved\0"
    "value\0slot_HSliderReleased\0slot_videoSpeed\0"
    "index\0slot_countInMinus\0slot_countOutMinus\0"
    "slot_outputData\0slot_closeVideo"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AccuracyValidationTool[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x08 /* Private */,
       3,    0,   70,    2, 0x08 /* Private */,
       4,    0,   71,    2, 0x08 /* Private */,
       5,    0,   72,    2, 0x08 /* Private */,
       6,    1,   73,    2, 0x08 /* Private */,
       8,    0,   76,    2, 0x08 /* Private */,
       9,    1,   77,    2, 0x08 /* Private */,
      11,    0,   80,    2, 0x08 /* Private */,
      12,    0,   81,    2, 0x08 /* Private */,
      13,    0,   82,    2, 0x08 /* Private */,
      14,    0,   83,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void AccuracyValidationTool::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AccuracyValidationTool *_t = static_cast<AccuracyValidationTool *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slot_openAVideo(); break;
        case 1: _t->slot_setFrameRate(); break;
        case 2: _t->slot_setReportInterval(); break;
        case 3: _t->slot_setStartTime(); break;
        case 4: _t->slot_HSliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->slot_HSliderReleased(); break;
        case 6: _t->slot_videoSpeed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->slot_countInMinus(); break;
        case 8: _t->slot_countOutMinus(); break;
        case 9: _t->slot_outputData(); break;
        case 10: _t->slot_closeVideo(); break;
        default: ;
        }
    }
}

const QMetaObject AccuracyValidationTool::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_AccuracyValidationTool.data,
      qt_meta_data_AccuracyValidationTool,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *AccuracyValidationTool::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AccuracyValidationTool::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_AccuracyValidationTool.stringdata0))
        return static_cast<void*>(const_cast< AccuracyValidationTool*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int AccuracyValidationTool::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
