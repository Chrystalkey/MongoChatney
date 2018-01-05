#include "newconnectiondialog.h"
#include <QHostAddress>

NewConnectionDialog::NewConnectionDialog(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    validIp = new QRegExpValidator(QRegExp("\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}"), this);
    ipEdit->setValidator(validIp);
    connect(this, SIGNAL(accepted()), this, SLOT(close()));
    connect(this, SIGNAL(rejected()), this, SLOT(close()));
}

QHostAddress NewConnectionDialog::currentHostAddress() const{
    return QHostAddress(ipEdit->text());
}

NewConnectionDialog::~NewConnectionDialog(){
    delete validIp;
}
