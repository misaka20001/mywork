/****************************************************************************
** Meta object code from reading C++ file 'lzwdialog.h'
**
** Created: Wed Aug 22 16:03:11 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "lzwdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'lzwdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_LzwDialog[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x08,
      31,   25,   10,   10, 0x08,
      56,   10,   10,   10, 0x08,
      72,   10,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_LzwDialog[] = {
    "LzwDialog\0\0lzwOpenFile()\0index\0"
    "lzwComboBoxOpenFile(int)\0callLzwEncode()\0"
    "callLzwDecode()\0"
};

const QMetaObject LzwDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_LzwDialog,
      qt_meta_data_LzwDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &LzwDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *LzwDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *LzwDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LzwDialog))
        return static_cast<void*>(const_cast< LzwDialog*>(this));
    if (!strcmp(_clname, "Ui::Dialog"))
        return static_cast< Ui::Dialog*>(const_cast< LzwDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int LzwDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: lzwOpenFile(); break;
        case 1: lzwComboBoxOpenFile((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: callLzwEncode(); break;
        case 3: callLzwDecode(); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
