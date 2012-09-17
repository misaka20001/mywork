#ifndef DIALUP_H
#define DIALUP_H

#include <QWidget>
#include "ui_dial-up.h"
#include "network.h"
#include <QMessageBox>

class DialWindow : public QWidget, public Ui::QDialWindow
{
    Q_OBJECT

public:
    DialWindow(QWidget *parent = 0);

public slots:
    int connect();
    int disconnect();
    void self_service();

protected:
    //void paintEvent( QPaintEvent * event );

private:
    network test;
    QStringList channels;

};

#endif // DIALUP_H
