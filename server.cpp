#include "server.h"

#include "connection.h"

Server::Server(QObject *parent):
    QTcpServer(parent){
    listen(QHostAddress::Any, PORT);
    emit stateUpdate(isListening()?ServerOn:ServerOff);
    qDebug() << "@Server::Server():\t" << isListening();
    qDebug() << "Server Port: " << serverPort();
}

void Server::incomingConnection(qintptr socketDescriptor){
    Connection *connection = new Connection(this);
    connection->setSocketDescriptor(socketDescriptor);
    emit newConnection(connection);
}
