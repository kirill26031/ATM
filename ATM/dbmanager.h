#ifndef DBMANAGER_H
#define DBMANAGER_H
#include <QSqlDatabase>

class DBManager
{
public:
    ~DBManager();
    static DBManager* getInstance();

    bool isOpen() const;

    const QSqlDatabase& db() const {return _db;}
protected:
        DBManager();
private:
    QSqlDatabase _db;
    static DBManager* _db_manager;
};

#endif // DBMANAGER_H
