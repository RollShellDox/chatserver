/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[23];
    char stringdata0[442];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 14), // "friendsUpdated"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 13), // "groupsUpdated"
QT_MOC_LITERAL(4, 41, 24), // "on_connectButton_clicked"
QT_MOC_LITERAL(5, 66, 22), // "on_loginButton_clicked"
QT_MOC_LITERAL(6, 89, 25), // "on_registerButton_clicked"
QT_MOC_LITERAL(7, 115, 21), // "on_sendButton_clicked"
QT_MOC_LITERAL(8, 137, 26), // "on_addFriendButton_clicked"
QT_MOC_LITERAL(9, 164, 28), // "on_createGroupButton_clicked"
QT_MOC_LITERAL(10, 193, 26), // "on_joinGroupButton_clicked"
QT_MOC_LITERAL(11, 220, 26), // "on_groupSendButton_clicked"
QT_MOC_LITERAL(12, 247, 23), // "on_logoutButton_clicked"
QT_MOC_LITERAL(13, 271, 25), // "on_friendList_itemClicked"
QT_MOC_LITERAL(14, 297, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(15, 314, 4), // "item"
QT_MOC_LITERAL(16, 319, 24), // "on_groupList_itemClicked"
QT_MOC_LITERAL(17, 344, 15), // "socketConnected"
QT_MOC_LITERAL(18, 360, 18), // "socketDisconnected"
QT_MOC_LITERAL(19, 379, 15), // "socketReadyRead"
QT_MOC_LITERAL(20, 395, 11), // "socketError"
QT_MOC_LITERAL(21, 407, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(22, 436, 5) // "error"

    },
    "MainWindow\0friendsUpdated\0\0groupsUpdated\0"
    "on_connectButton_clicked\0"
    "on_loginButton_clicked\0on_registerButton_clicked\0"
    "on_sendButton_clicked\0on_addFriendButton_clicked\0"
    "on_createGroupButton_clicked\0"
    "on_joinGroupButton_clicked\0"
    "on_groupSendButton_clicked\0"
    "on_logoutButton_clicked\0"
    "on_friendList_itemClicked\0QListWidgetItem*\0"
    "item\0on_groupList_itemClicked\0"
    "socketConnected\0socketDisconnected\0"
    "socketReadyRead\0socketError\0"
    "QAbstractSocket::SocketError\0error"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   99,    2, 0x06 /* Public */,
       3,    0,  100,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,  101,    2, 0x08 /* Private */,
       5,    0,  102,    2, 0x08 /* Private */,
       6,    0,  103,    2, 0x08 /* Private */,
       7,    0,  104,    2, 0x08 /* Private */,
       8,    0,  105,    2, 0x08 /* Private */,
       9,    0,  106,    2, 0x08 /* Private */,
      10,    0,  107,    2, 0x08 /* Private */,
      11,    0,  108,    2, 0x08 /* Private */,
      12,    0,  109,    2, 0x08 /* Private */,
      13,    1,  110,    2, 0x08 /* Private */,
      16,    1,  113,    2, 0x08 /* Private */,
      17,    0,  116,    2, 0x08 /* Private */,
      18,    0,  117,    2, 0x08 /* Private */,
      19,    0,  118,    2, 0x08 /* Private */,
      20,    1,  119,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 21,   22,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->friendsUpdated(); break;
        case 1: _t->groupsUpdated(); break;
        case 2: _t->on_connectButton_clicked(); break;
        case 3: _t->on_loginButton_clicked(); break;
        case 4: _t->on_registerButton_clicked(); break;
        case 5: _t->on_sendButton_clicked(); break;
        case 6: _t->on_addFriendButton_clicked(); break;
        case 7: _t->on_createGroupButton_clicked(); break;
        case 8: _t->on_joinGroupButton_clicked(); break;
        case 9: _t->on_groupSendButton_clicked(); break;
        case 10: _t->on_logoutButton_clicked(); break;
        case 11: _t->on_friendList_itemClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 12: _t->on_groupList_itemClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 13: _t->socketConnected(); break;
        case 14: _t->socketDisconnected(); break;
        case 15: _t->socketReadyRead(); break;
        case 16: _t->socketError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 16:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::friendsUpdated)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::groupsUpdated)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::friendsUpdated()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void MainWindow::groupsUpdated()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
