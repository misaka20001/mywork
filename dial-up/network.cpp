#include "network.h"
#include <QString>
#include <QByteArray>
#include <QEventLoop>
#include <QDir>
#include <QMessageBox>

network::network()
{
    manager = new QNetworkAccessManager;

    request.setUrl( QUrl("http://172.16.2.66/cgi-bin/srun_portal") );
}

network::~network()
{
    //delete manager;
    //delete request;
    //delete reply;
}

int network::connect( QString usrname, QString password , bool issave )
{
    QByteArray content;

    QString contentStr=QString("action=login&uid=-1&is_pad=1&force=0&ac_id=2&pop=0"
      "&ac_type=juniper&rad_type=&gateway_auth=0&local_auth=1&is_debug=&is_ldap=0&user_ip=&mac="
        "&nas_ip=172.16.2.61&&username=%1%40chinanet&password=%2&drop=102&save_me=on").arg(usrname).arg(password);

    content.append(contentStr);

    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

    int length = issave?content.length():content.length() - QString("&save_me=on").length();
    request.setHeader(QNetworkRequest::ContentLengthHeader,length);

    const QString informations = QDir::homePath() + "/.informations";
    {
        QFile file( informations );
        file.open( QIODevice::WriteOnly );
        file.close();

        file.open( QIODevice::WriteOnly );
        QTextStream stream( &file );
            if ( file.isOpen() ){
                stream<<usrname<<'\n';

                if ( issave ){
                    stream<<password<<'\n';
                }
            }
        file.close();
    }

    reply = manager->post( request, content );
    QObject::connect(reply, SIGNAL(finished()), &waitDownload, SLOT(quit()));
    waitDownload.exec();

    data = reply->readAll();
    //qDebug()<<QString::fromUtf8(data);

    switch( data.size() ){
    case 151 :
        return LOGIN_SUCCESS;
    case 709:
        return PASSWORD_WRONG;
    case 712:
        return USRNAME_WRONG;
    case 733:
        return HAS_LOGINED;
    default:
        return UNKNOWN_ERROR;
    }

}

int network::disconnect( QString usrname, QString password, bool issave )
{
    QByteArray content;

    QString contentStr=QString("action=logout&uid=-1&is_pad=1&force=0&ac_id=2&pop=0&ac_type=&"
      "rad_type=&gateway_auth=0&local_auth=&is_debug=&is_ldap=0&user_ip=&mac=&nas_ip=172.16.2.61&ssid=&vlan"
        "=&wlanacname=&wbaredirect=&username=%1&password=%2&drop=102&save_me=on").arg(usrname).arg(password);

    content.append(contentStr);

    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

    int length = issave?content.length():content.length() - QString("&save_me=on").length();
    request.setHeader(QNetworkRequest::ContentLengthHeader,length);

    reply = manager->post( request, content );
    QObject::connect(reply, SIGNAL(finished()), &waitDownload, SLOT(quit()));
    waitDownload.exec();

    data = reply->readAll();
    //qDebug()<<QString::fromUtf8(data);
    //qDebug()<<data.size();

    switch ( data.size() ){
    case 706 :
        return LOGOUT_SUCCESS;
    default:
        return UNKNOWN_ERROR;
    }

}

