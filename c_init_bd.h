#ifndef C_INIT_BD_H
#define C_INIT_BD_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QFile>

class C_INIT_BD
{
private:
    QSqlDatabase mydb;
public:
    C_INIT_BD();
    ~C_INIT_BD();
    bool Creation_BD();
    void Close_BD();
};

#endif // C_INIT_BD_H
