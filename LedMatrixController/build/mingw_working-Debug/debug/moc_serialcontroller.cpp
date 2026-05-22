/****************************************************************************
** Meta object code from reading C++ file 'serialcontroller.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../serialcontroller.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'serialcontroller.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSSerialControllerENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSSerialControllerENDCLASS = QtMocHelpers::stringData(
    "SerialController",
    "connectedChanged",
    "",
    "statusMessageChanged",
    "availablePortsChanged",
    "serialDataReceived",
    "data",
    "connectToPort",
    "portName",
    "disconnectPort",
    "sendMatrix",
    "matrix",
    "refreshPorts",
    "onReadyRead",
    "onErrorOccurred",
    "QSerialPort::SerialPortError",
    "error",
    "connected",
    "statusMessage",
    "availablePorts"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSSerialControllerENDCLASS_t {
    uint offsetsAndSizes[40];
    char stringdata0[17];
    char stringdata1[17];
    char stringdata2[1];
    char stringdata3[21];
    char stringdata4[22];
    char stringdata5[19];
    char stringdata6[5];
    char stringdata7[14];
    char stringdata8[9];
    char stringdata9[15];
    char stringdata10[11];
    char stringdata11[7];
    char stringdata12[13];
    char stringdata13[12];
    char stringdata14[16];
    char stringdata15[29];
    char stringdata16[6];
    char stringdata17[10];
    char stringdata18[14];
    char stringdata19[15];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSSerialControllerENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSSerialControllerENDCLASS_t qt_meta_stringdata_CLASSSerialControllerENDCLASS = {
    {
        QT_MOC_LITERAL(0, 16),  // "SerialController"
        QT_MOC_LITERAL(17, 16),  // "connectedChanged"
        QT_MOC_LITERAL(34, 0),  // ""
        QT_MOC_LITERAL(35, 20),  // "statusMessageChanged"
        QT_MOC_LITERAL(56, 21),  // "availablePortsChanged"
        QT_MOC_LITERAL(78, 18),  // "serialDataReceived"
        QT_MOC_LITERAL(97, 4),  // "data"
        QT_MOC_LITERAL(102, 13),  // "connectToPort"
        QT_MOC_LITERAL(116, 8),  // "portName"
        QT_MOC_LITERAL(125, 14),  // "disconnectPort"
        QT_MOC_LITERAL(140, 10),  // "sendMatrix"
        QT_MOC_LITERAL(151, 6),  // "matrix"
        QT_MOC_LITERAL(158, 12),  // "refreshPorts"
        QT_MOC_LITERAL(171, 11),  // "onReadyRead"
        QT_MOC_LITERAL(183, 15),  // "onErrorOccurred"
        QT_MOC_LITERAL(199, 28),  // "QSerialPort::SerialPortError"
        QT_MOC_LITERAL(228, 5),  // "error"
        QT_MOC_LITERAL(234, 9),  // "connected"
        QT_MOC_LITERAL(244, 13),  // "statusMessage"
        QT_MOC_LITERAL(258, 14)   // "availablePorts"
    },
    "SerialController",
    "connectedChanged",
    "",
    "statusMessageChanged",
    "availablePortsChanged",
    "serialDataReceived",
    "data",
    "connectToPort",
    "portName",
    "disconnectPort",
    "sendMatrix",
    "matrix",
    "refreshPorts",
    "onReadyRead",
    "onErrorOccurred",
    "QSerialPort::SerialPortError",
    "error",
    "connected",
    "statusMessage",
    "availablePorts"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSSerialControllerENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       3,   92, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   74,    2, 0x06,    4 /* Public */,
       3,    0,   75,    2, 0x06,    5 /* Public */,
       4,    0,   76,    2, 0x06,    6 /* Public */,
       5,    1,   77,    2, 0x06,    7 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       7,    1,   80,    2, 0x0a,    9 /* Public */,
       9,    0,   83,    2, 0x0a,   11 /* Public */,
      10,    1,   84,    2, 0x0a,   12 /* Public */,
      12,    0,   87,    2, 0x0a,   14 /* Public */,
      13,    0,   88,    2, 0x08,   15 /* Private */,
      14,    1,   89,    2, 0x08,   16 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    6,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QStringList,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 15,   16,

 // properties: name, type, flags
      17, QMetaType::Bool, 0x00015001, uint(0), 0,
      18, QMetaType::QString, 0x00015001, uint(1), 0,
      19, QMetaType::QStringList, 0x00015001, uint(2), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject SerialController::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSSerialControllerENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSSerialControllerENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSSerialControllerENDCLASS_t,
        // property 'connected'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'statusMessage'
        QtPrivate::TypeAndForceComplete<QString, std::true_type>,
        // property 'availablePorts'
        QtPrivate::TypeAndForceComplete<QStringList, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<SerialController, std::true_type>,
        // method 'connectedChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'statusMessageChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'availablePortsChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'serialDataReceived'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'connectToPort'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'disconnectPort'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'sendMatrix'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QStringList &, std::false_type>,
        // method 'refreshPorts'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onReadyRead'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onErrorOccurred'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QSerialPort::SerialPortError, std::false_type>
    >,
    nullptr
} };

void SerialController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SerialController *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->connectedChanged(); break;
        case 1: _t->statusMessageChanged(); break;
        case 2: _t->availablePortsChanged(); break;
        case 3: _t->serialDataReceived((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 4: _t->connectToPort((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 5: _t->disconnectPort(); break;
        case 6: _t->sendMatrix((*reinterpret_cast< std::add_pointer_t<QStringList>>(_a[1]))); break;
        case 7: _t->refreshPorts(); break;
        case 8: _t->onReadyRead(); break;
        case 9: _t->onErrorOccurred((*reinterpret_cast< std::add_pointer_t<QSerialPort::SerialPortError>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SerialController::*)();
            if (_t _q_method = &SerialController::connectedChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SerialController::*)();
            if (_t _q_method = &SerialController::statusMessageChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SerialController::*)();
            if (_t _q_method = &SerialController::availablePortsChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (SerialController::*)(const QString & );
            if (_t _q_method = &SerialController::serialDataReceived; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
    }else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<SerialController *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = _t->isConnected(); break;
        case 1: *reinterpret_cast< QString*>(_v) = _t->statusMessage(); break;
        case 2: *reinterpret_cast< QStringList*>(_v) = _t->availablePorts(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
}

const QMetaObject *SerialController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SerialController::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSSerialControllerENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int SerialController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 10;
    }else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void SerialController::connectedChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void SerialController::statusMessageChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void SerialController::availablePortsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void SerialController::serialDataReceived(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
