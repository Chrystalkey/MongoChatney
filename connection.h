#ifndef CONNECTION_H
#define CONNECTION_H

#include <QTcpSocket>
#include <QColor>

static const int MaxBufferSize = 1024000;

class Connection : public QTcpSocket
{
    Q_OBJECT
public:
    enum DataType{
        PlainText,
        Undefined
    };
    Connection(QObject *parent = nullptr);

    QColor who() const;
    bool sendMessage(const QString& msg);
signals:
    void readyForUse();
    void newMessage(QColor, const QString &msg);
private slots:
    void processReadyRead();
private:
    int readDataIntoBuffer(int maxSize = MaxBufferSize);
    int dataLengthForCurrentDataType();
    void processData();
    void setColor();

    QColor whoIsThat;
    QByteArray buffer;
    DataType type = Undefined;
    int numBytesForCurrentDataType = -1;
};

#endif // CONNECTION_H
