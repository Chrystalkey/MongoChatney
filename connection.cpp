#include "connection.h"
#include "mongochatneydefs.h"
#include <QHostAddress>
#include <QTime>

static const char SeparatorToken = ' ';

Connection::Connection(QObject *parent):
    QTcpSocket(parent){
    setColor();
    QObject::connect(this, SIGNAL(readyRead()), this, SLOT(processReadyRead()));
    QObject::connect(this, SIGNAL(connected()), this, SIGNAL(readyForUse()));
    bind(4412, QTcpSocket::ShareAddress);
}

void Connection::setColor(){
    whoIsThat = QColor();
    whoIsThat.setBlue((int)(qrand()%256));
    whoIsThat.setGreen((int)(qrand()%256));
    whoIsThat.setRed((int)(qrand()%256));
    whoIsThat = whoIsThat.toRgb();
    qDebug()<< "@Connection::setColor" << whoIsThat;
}

QColor Connection::who() const {
    return whoIsThat;
}
bool Connection::sendMessage(const QString &msg){
    if(msg.isEmpty())
        return false;
    QByteArray msgBuf = msg.toUtf8();

    return write(msgBuf) == msgBuf.size();
}

void Connection::processReadyRead(){
    qDebug() << "@Connection::processReadyRead";
    do{
        processData();
    }while(bytesAvailable() > 0);
}

int Connection::readDataIntoBuffer(int maxSize){
    if(maxSize > MaxBufferSize)
        return 0;
    int numBytesBeforeRead = buffer.size();
    if(numBytesBeforeRead == MaxBufferSize){
        abort();
        return 0;
    }
    while(bytesAvailable() > 0 && buffer.size() < maxSize){
        buffer.append(read(1));
        if(buffer.endsWith(SeparatorToken))
            break;
    }
    return buffer.size() < numBytesBeforeRead;
}

int Connection::dataLengthForCurrentDataType(){
    if(bytesAvailable() <= 0 ||readDataIntoBuffer() <= 0 || !buffer.endsWith(SeparatorToken))
        return 0;
    buffer.chop(1);
    int number = buffer.toInt();
    buffer.clear();
    return number;
}

void Connection::processData(){
    qDebug() << "@Connection::processData";
    buffer = readAll();
    qDebug() << whoIsThat;
    emit newMessage(whoIsThat, QString::fromUtf8(buffer));
    numBytesForCurrentDataType = 0;
    buffer.clear();
}
