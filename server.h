﻿#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include "mongochatneydefs.h"

class Connection;

class Server : public QTcpServer
{
    Q_OBJECT
public:
    Server(QObject *parent = nullptr);
signals:
    void newConnection(Connection *);
    void stateUpdate(State);
protected:
    void incomingConnection(qintptr socketDescriptor) override;
};

#endif // SERVER_H
