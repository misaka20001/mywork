#include "shapewidget.h"
#include <QPushButton>
#include <QTimer>
#include <QTime>
#include <QMenu>


ShapeWidget::ShapeWidget(QWidget *parent)
    : QWidget(parent, Qt::FramelessWindowHint)
{
    QPixmap pix;
    pix.load(":/images/1.png", 0, Qt::AvoidDither | Qt::ThresholdAlphaDither);
    resize(pix.size());
    setMask(pix.mask());

    Act_Maxsize     = new QAction(tr("TEST"), this);
    Act_Minimize     = new QAction(tr("MINIMIZE"), this);
    Act_close      = new QAction(tr("&exit"),this);
    Act_timekeeping = new QAction(tr("TIMEKEEP"), this);
    Act_About      = new QAction(tr("ABOUT"), this);
    Act_timekeeping->setCheckable(true);
    connect(Act_Minimize, SIGNAL(triggered()), this, SLOT(showMinimized()));
    connect(Act_close, SIGNAL(triggered()), this, SLOT(close()));
    connect(Act_timekeeping, SIGNAL(triggered()), this, SLOT(selectTimeKeeping()));

    messagebox = new QMessageBox(QMessageBox::NoIcon, tr("About"), tr("<h2>Miku Clock Ver1.0</h2>"
         "<p>Copyright © 2010 0xdeadbeef. All rights reserved.""<p>Miku Clock Ver1.0 is developed based on QT4.0 "
         "entirely follow GPL agreement. Anyone who has interests in this software can modify the source code. "
         "<p><h3>Author: 0xdeadbeef<br>Email: misakamm20001@gmail.com</h3><p>"));

    messagebox->setIconPixmap(QPixmap(":/images/5.png"));
    connect(Act_About, SIGNAL(triggered()), messagebox, SLOT(exec()));

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(1000);

    //Phonon::VideoPlayer *player = new Phonon::VideoPlayer(Phonon::VideoCategory, this);
    //player->load("/home/shana/dudulu.mp3");
    //player->play();
    source = Phonon::MediaSource("/home/shana/dudulu.mp3");
    music = Phonon::createPlayer(Phonon::MusicCategory, source);
    music->play();

    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
}

void ShapeWidget::selectTimeKeeping()
{
    static bool isSelectTimeKeeping = 0;
    isSelectTimeKeeping = !isSelectTimeKeeping;
    Act_timekeeping->setChecked(isSelectTimeKeeping);
}


void ShapeWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        dragPosition = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
    //if (event->button() == Qt::RightButton)
        //close();
}

void ShapeWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() && Qt::LeftButton)
    {
        move(event->globalPos() - dragPosition);
        event->accept();
    }
}

void ShapeWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, QPixmap(":/images/1.png"));
    painter.translate(102, 251);
    static QPixmap pic1(":/images/2.png");
    static QPixmap pic2(":/images/3.png");
    static QPixmap pic3(":/images/4.png");


    QTime time = QTime::currentTime();

    painter.save();
    painter.rotate(30.0 * (time.hour() + time.minute() / 60.0));
    painter.drawPixmap(-pic1.width()/2 , - pic1.height(), pic1.width(), pic1.height(), pic1);
    painter.restore();

    painter.save();
    painter.rotate(90.0 + 6.0 * (time.minute() + time.second() / 60.0));
    painter.drawPixmap( - pic2.width() , -pic2.height()/2, pic2);
    painter.restore();

    painter.save();
    painter.rotate(-90.0 + 6.0 * time.second());
    painter.drawPixmap(0, 0, pic3);
    painter.restore();

    if (time.minute() == 0 && time.second() == 0){
        if (Act_timekeeping->isChecked())
            music->play();
    }
}

void ShapeWidget::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu *menu = new QMenu();
    menu->addSeparator();
    menu->addSeparator();
    menu->addAction(Act_Maxsize);
    menu->addSeparator();
    menu->addSeparator();
    menu->addAction(Act_Minimize);
    menu->addSeparator();
    menu->addSeparator();
    menu->addAction(Act_timekeeping);
    menu->addSeparator();
    menu->addSeparator();
    menu->addAction(Act_About);
    menu->addSeparator();
    menu->addSeparator();
    menu->addAction(Act_close);
    menu->exec(event->globalPos());
    delete menu;
}
