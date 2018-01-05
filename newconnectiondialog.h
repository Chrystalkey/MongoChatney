#ifndef NEWCONNECTIONDIALOG_H
#define NEWCONNECTIONDIALOG_H

#include "ui_newconnectiondialog.h"
#include "mongochatneydefs.h"
#include <QHostAddress>

class NewConnectionDialog : public QDialog, private Ui::NewConnectionDialog
{
    Q_OBJECT

public:
    explicit NewConnectionDialog(QWidget *parent = 0);
    ~NewConnectionDialog();
    QHostAddress currentHostAddress() const;
private:
    QRegExpValidator *validIp;
};

#endif // NEWCONNECTIONDIALOG_H
