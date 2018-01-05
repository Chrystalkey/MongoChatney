#ifndef CLIENT_H
#define CLIENT_H

#include <QAbstractSocket>
#include <QHash>
#include <QHostAddress>
#include <QColor>
#include "mongochatneydefs.h"
#include "server.h"

class Connection;


class Client : public QObject
{
    Q_OBJECT
public:
    Client();

    void sendMessage(const QString& msg);
    QString userName() const;
    bool hasConnection(const QHostAddress &senderIp, int senderPort = -1);
    void initiateNewConnection(const QHostAddress &hostIp);
signals:
    void newMessage(QColor, const QString &);
    void newMongo(const QColor& name);
    void mongoLeft(const QColor &name);
    void stateChanged(State);
private slots:
    void newConnection(Connection*connection);
    void connectionError(QAbstractSocket::SocketError sError);
    void disconnected();
    void readyForUse();

private:
    void removeConnection(Connection *connection);
    QColor colorPick();

    Server server;
    QMap<Connection*, QColor> participants;
    QMultiHash<QHostAddress, Connection *> peers;
    QList<Connection*> connections;
    QByteArray name;
signals:
    void newConnectionInitiated(Connection *connection);
};

#endif // CLIENT_H
