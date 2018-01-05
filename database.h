#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>

class Database
{
public:
    Database();
    ~Database();
    void newEntry(const QString &date, const QString &user, const QString &msg);
private:
    QSqlDatabase db;
    QString currTable;
};

#endif // DATABASE_H
