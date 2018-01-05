#include "database.h"
#include "mongochatneydefs.h"
#include <QSqlQuery>
#include <QDate>
#include <QDebug>
#include <QVariant>

Database::Database(){
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("log.mongo");
    if(!db.open()){
        qDebug() << "Not abled to open database. Please ask the mongo, who constructed this";
        exit(2);
    }
    currTable = "["+QDate::currentDate().toString(Qt::ISODate)+"]";
    QSqlQuery query;
    if(!query.exec("CREATE TABLE " + currTable + " (date varchar(100), who varchar(16), message TEXT);"))
        qDebug() << "Failed to create new Table";
}


void Database::newEntry(const QString &date, const QString &user, const QString &msg){
    QSqlQuery query;
    query.prepare("INSERT INTO "+currTable+" (date, who, message) VALUES (:vDate, :vWho, :vMsg)");
    query.bindValue(":vDate", QVariant(date));
    query.bindValue(":vWho", QVariant(user));
    query.bindValue(":vMsg", QVariant(msg));
    if(!query.exec())
        qDebug() << "Failed to write entry into table";
}

Database::~Database(){
    db.close();
}
