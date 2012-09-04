#ifndef LZWDIALOG_H
#define LZWDIALOG_H

#include <QDialog>
#include "ui_lzwdialog.h"
#include "lzw.h"

class LzwDialog : public QDialog, public Ui::Dialog
{
    Q_OBJECT

public:
    LzwDialog(QWidget *parent = 0);
    void initComboBox();
private slots:
    void lzwOpenFile();
    void lzwComboBoxOpenFile( int index );
    void callLzwEncode();
    void callLzwDecode();

protected:
    void paintEvent( QPaintEvent * event );

private:
    friend class lzw_compress;
    friend class lzw_decompress;
    QStringList pathList;
    QString filePath;
    QString fileSavePath;
};

#endif // LZWDIALOG_H
