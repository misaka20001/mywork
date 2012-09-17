#ifndef NETWORK_H
#define NETWORK_H

#include <QtNetwork>
#include <QObject>

#define LOGIN_SUCCESS  1
#define PASSWORD_WRONG 2
#define USRNAME_WRONG  3
#define HAS_LOGINED    4
#define UNKNOWN_ERROR  5
#define LOGOUT_SUCCESS 6

class network: public QObject
{
    Q_OBJECT

public:
    network();
    ~network();

public slots:
    int connect( QString , QString , bool );
    int disconnect( QString , QString, bool );

private:
    QNetworkAccessManager *manager;
    QNetworkRequest request;
    QNetworkReply *reply;
    QEventLoop waitDownload;
    QByteArray data;
};

#endif // NETWORK_H
