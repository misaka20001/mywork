#include "dial-up.h"
#include <QPalette>
#include <QPainter>
#include <QBrush>
#include <QProcess>
#include <QDesktopServices>

DialWindow::DialWindow(QWidget *parent)
    : QWidget(parent)
{
    setupUi(this);

    channels<<"chinanet"<<"cmcc"<<"chinaunicom"<<"wzu";
    //QImageWidget->setAutoFillBackground( true );
    //QPalette palette = QImageWidget->palette();
    //palette.setBrush(QPalette::Window, QBrush(QPixmap(":/images/1.png")));
    //QImageWidget->setPalette(palette);
    QImageWidget->setStyleSheet("QWidget{background: url(:/images/1.png)}");
    this->setFixedSize( this->width(), this->height() );
    this->setWindowIcon( QIcon(":/images/icon.png") );

    QObject::connect( QConnectpushButton,     SIGNAL(clicked()), this, SLOT(connect()) );
    QObject::connect( QDisconnectpushButton,  SIGNAL(clicked()), this, SLOT(disconnect()) );
    QObject::connect( QSelfServicepushButton, SIGNAL(clicked()), this, SLOT(self_service()) );

    const QString informations = QDir::homePath() + "/.informations";
    QFile file( informations );
    if ( file.exists() ){
        file.open( QIODevice::ReadOnly );
        if ( file.isOpen() ){
            char buf[20];
            memset( buf, 0, 20 );
            int len = file.readLine( buf, 20 );
            buf[ strlen(buf)-1 ] = 0;
            if ( len != -1)
                QUsernamelineEdit->setText( QString(buf) );

            memset( buf, 0, 20 );
            len = file.readLine( buf, 20 );
            buf[ strlen(buf)-1 ] = 0;
            if ( len != -1){
                QPasswordlineEdit->setText( QString(buf) );
                QPasswordcheckBox->setChecked( true );
            }
        }
    }
    QPasswordlineEdit->setEchoMode(QLineEdit::Password);

    QDisconnectpushButton->setDisabled( true );

    for ( int i=0; i < channels.count(); i++ )
        QChannelcomboBox->insertItem( i, QIcon(QString(":/images"
             "/channel%1.png").arg(QString::number(i+1))), channels.at(i) );

}

int DialWindow::connect()
{
    QString usrname  = QUsernamelineEdit->text();
    QString password = QPasswordlineEdit->text();
    bool issave      = QPasswordcheckBox->isChecked();

    int result = test.connect( usrname, password, issave );

    switch ( result ){
    case LOGIN_SUCCESS:
        QMessageBox::information( this, "login ok", "login success" );
        QConnectpushButton->setDisabled( true );
        QDisconnectpushButton->setDisabled( false );
        break;

    case USRNAME_WRONG:
        QMessageBox::information( this, "login fail", "username wrong" );
        break;

    case PASSWORD_WRONG:
        QMessageBox::information( this, "login fail", "password wrong" );
        break;

    case HAS_LOGINED:
        QMessageBox::information( this, "login fail", "has logined" );
        break;

    case UNKNOWN_ERROR:
        QMessageBox::information( this, "login fail", "unkown error" );
        break;

    }
    return result;
}

int DialWindow::disconnect()
{
    QString usrname  = QUsernamelineEdit->text();
    QString password = QPasswordlineEdit->text();
    bool issave      = QPasswordcheckBox->isChecked();

    int result = test.disconnect( usrname, password, issave );

    switch ( result ){
    case LOGOUT_SUCCESS:
        QMessageBox::information( this, "logout ok", "logout success" );
        QConnectpushButton->setDisabled( false );
        QDisconnectpushButton->setDisabled( true );
        break;

    case UNKNOWN_ERROR:
        QMessageBox::information( this, "logout fail", "unkown error" );
        break;

    }
    return result;

}

void DialWindow::self_service()
{
    //QProcess *task = new QProcess();
    //QStringList arg;
    //arg<<"www.bilibili.tv";

    //task->start( "firefox", arg );
    if ( !QDesktopServices::openUrl(QUrl( "http://www.bilibili.tv" )) )
        QMessageBox::warning( this, "open browser error", "no internet browser found" );
}


