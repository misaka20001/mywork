#ifndef SHAPEWIDGET_H
#define SHAPEWIDGET_H

#include <QtGui>
#include <QAction>
#include <QMessageBox>
#include <phonon>

class QPoint;

class ShapeWidget : public QWidget
{
    Q_OBJECT
public:
    ShapeWidget(QWidget *parent = 0);
    void selectTimeKeeping();
    void minimize();

protected:
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);
    void contextMenuEvent(QContextMenuEvent *);

private:
    QPoint dragPosition;
    QMessageBox *messagebox;
    QAction*    Act_Maxsize;
    QAction*    Act_Minimize;
    QAction*    Act_close;
    QAction*    Act_timekeeping;
    QAction*    Act_About;
    Phonon::MediaObject *music;
    Phonon::MediaSource source;

};

#endif // SHAPEWIDGET_H
