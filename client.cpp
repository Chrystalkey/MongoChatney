#include "client.h"

#include "connection.h"
#include <QProcessEnvironment>
#include <QColor>

Client::Client()
{
    QStringList envVars;
    envVars << "USERNAME" << "USER" << "USERDOMAIN" << "HOSTNAME" << "DOMAINNAME";
    QProcessEnvironment environment = QProcessEnvironment::systemEnvironment();
    foreach(QString str, envVars){
        if(environment.contains(str)){
            name = environment.value(str).toUtf8();
            break;
        }
    }
    if(name.isEmpty())
        name = "Unknown User";

    QObject::connect(&server, SIGNAL(newConnection(Connection*)), this, SLOT(newConnection(Connection*)));
    QObject::connect(this, SIGNAL(newConnectionInitiated(Connection*)), this, SLOT(newConnection(Connection*)));
    QObject::connect(&server, SIGNAL(stateUpdate(State)), this, SIGNAL(stateChanged(State)));
}

void Client::sendMessage(const QString &msg){
    qDebug() << "@Client::sendMessage " << msg;
    qDebug() << "Connections: " << connections.size();
    if(msg.isEmpty())
        return;
    foreach(Connection* connection, connections){
        qDebug() << connection->sendMessage(msg);
    }
}

QString Client::userName() const{
    return name.isEmpty()?"Unknown User":name;
}

bool Client::hasConnection(const QHostAddress &senderIp, int senderPort){
    if(senderPort == -1)
        return peers.contains(senderIp);
    if(!peers.contains(senderIp))
        return false;
    foreach(Connection * ptr, connections){
        if(ptr->peerPort() == senderPort)
            return true;
    }
    return false;
}

void Client::newConnection(Connection *connection){
    connect(connection, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(connectionError(QAbstractSocket::SocketError)));
    connect(connection, SIGNAL(disconnected()),
            this, SLOT(disconnected()));
    connect(connection ,SIGNAL(readyForUse()),
            this, SLOT(readyForUse()));
    connect(connection, SIGNAL(newMessage(QColor,QString)),
            this, SIGNAL(newMessage(QColor,QString)));
    participants.insert(connection, connection->who());
    connections.append(connection);
    emit newMongo(connection->who());
    emit stateChanged(Connected);
}

void Client::readyForUse(){
    Connection *connection = qobject_cast<Connection *>(sender());
    if(!connection||hasConnection(connection->peerAddress(), connection->peerPort()))
        return;
    connect(connection, SIGNAL(newMessage(QColor, QString)), this, SIGNAL(newMessage(QColor, QString)));
    peers.insert(connection->peerAddress(), connection);
    QColor who = connection->who();
    if(who != QColor(Qt::black))
        emit newMongo(who);
}

void Client::disconnected(){
    if(Connection *connection = qobject_cast<Connection *>(sender()))
        removeConnection(connection);
    if(connections.isEmpty())
        emit stateChanged(Unconnected);
}
void Client::removeConnection(Connection *connection){
    if(peers.contains(connection->peerAddress())){
        peers.remove(connection->peerAddress());
        QColor who = connection->who();
        if(who != QColor(Qt::black))
            emit mongoLeft(who);
    }
    connections.removeAll(connection);
    emit mongoLeft(connection->who());
    connection->deleteLater();
}
void Client::initiateNewConnection(const QHostAddress &hostIp){
    qDebug() << "@Client::initiateNewConnection";
    Connection *connection  = new Connection(this);
    connection->connectToHost(hostIp, PORT);
    emit newConnectionInitiated(connection);
}

void Client::connectionError(QAbstractSocket::SocketError){
    if(Connection *connection = qobject_cast<Connection*>(sender())){
        qDebug() << "@Client::connectionError:\t" << connection->who() << ' ' << connection->errorString();
        removeConnection(connection);
    }
}
