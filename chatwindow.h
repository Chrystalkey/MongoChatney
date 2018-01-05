#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QMainWindow>
#include "ui_chatwindow.h"
#include "mongochatneydefs.h"
#include "client.h"
#include "database.h"

class NewConnectionDialog;

class ChatWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

public:
    explicit ChatWindow(QWidget *parent = 0);
    ~ChatWindow();
public slots:
    void setState(State s);
    void writeMessage(QColor from, const QString& msg);
private slots:
    void returnPressed();
    void newMongo(const QColor& who);
    void mongoLeft(const QColor& who);
    void callClientForNewConnection();
private:
    Client *client;
    Database db;
    QString myName;
    QTextTableFormat tableFormat;
    bool alreadyConnected;
    NewConnectionDialog *nCW;
};

#endif // CHATWINDOW_H
