#ifndef DBMANAGER_H
#define DBMANAGER_H
#include <QSqlDatabase>

class DBManager
{
public:
    DBManager();
    ~DBManager();

    bool isOpen() const;
private:
    QSqlDatabase _db;
};

#endif // DBMANAGER_H
