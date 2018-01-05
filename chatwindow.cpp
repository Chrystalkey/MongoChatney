#include "chatwindow.h"
#include <QTextTable>
#include <QTextCursor>
#include <QTime>
#include <QScrollBar>
#include <QShortcut>
#include <QMenuBar>

#include "newconnectiondialog.h"

ChatWindow::ChatWindow(QWidget *parent) :
    QMainWindow(parent)
{
    qDebug() << "@ChatWindow::ChatWindow";
    setupUi(this);
    client = new Client;
    nCW = new NewConnectionDialog(this);
    textEdit->setReadOnly(true);

    connect(lineEdit, SIGNAL(returnPressed()), this, SLOT(returnPressed()));
    connect(client, SIGNAL(newMessage(QColor, QString)), this,  SLOT(writeMessage(QColor,QString)));
    connect(client, SIGNAL(newMongo(QColor)), this, SLOT(newMongo(QColor)));
    connect(client, SIGNAL(mongoLeft(QColor)), this, SLOT(mongoLeft(QColor)));
    connect(client, SIGNAL(stateChanged(State)), this, SLOT(setState(State)));
    connect(actionNew_Connection, SIGNAL(triggered()), nCW, SLOT(show()));


    connect(nCW, SIGNAL(accepted()), this, SLOT(callClientForNewConnection()));

    tableFormat.setBorder(0);
    nCW->hide();
}

ChatWindow::~ChatWindow(){
    delete client;
}

void ChatWindow::setState(State s){
    QString server, client;
    switch (s) {
    case ServerOn:
        server = "server online";
        break;
    case ServerOff:
        server = "server offline";
        break;
    case Connected:
        client = "connected";
        break;
    case Unconnected:
        client = "not connected";
        break;
    default:
        client = server = "unknown";
        break;
    }
    qDebug() << "@ChatWindow::setState: " << server << client;
    stateLabel->setText("state: "+server+"\t"+client);
}

void ChatWindow::writeMessage(QColor who, const QString &msg){
    qDebug() << "@ChatWindow::writeMessage" << who;
    if(msg.isEmpty())
        return;
    textEdit->setTextColor(who);
    textEdit->append(("["+QTime::currentTime().toString(Qt::ISODate)+"]")+"  "+msg+"\n");
    QScrollBar *bar = textEdit->verticalScrollBar();
    bar->setValue(bar->maximum());
    db.newEntry(QTime::currentTime().toString(Qt::ISODate),qColorToString(who),msg);
}

void ChatWindow::returnPressed(){
    qDebug() << "@ChatWindow::returnPressed";
    QString text = lineEdit->text();
    if(text.isEmpty())
        return;
    client->sendMessage(text);
    writeMessage(QColor(Qt::black), text);
    lineEdit->clear();
}

void ChatWindow::newMongo(const QColor &who){
    if(who == QColor(Qt::black))
        return;
    textEdit->setTextColor(who);
    textEdit->append(("["+QTime::currentTime().toString(Qt::ISODate)+"]")+"  Have joined");
    textEdit->setTextColor(Qt::gray);
    textEdit->append("#NoFakeNews");
}
void ChatWindow::mongoLeft(const QColor &who){
    if(who == QColor(Qt::black))
        return;
    textEdit->setTextColor(who);
    textEdit->append(("["+QTime::currentTime().toString(Qt::ISODate)+"]")+"  Have left");
    textEdit->setTextColor(Qt::gray);
    textEdit->append("#NoFakeNews");
}

void ChatWindow::callClientForNewConnection(){
    client->initiateNewConnection(QHostAddress(nCW->currentHostAddress()));
}
