#include "dbmanager.h"
#include <QDebug>

DBManager* DBManager::_db_manager = nullptr;

DBManager* DBManager::getInstance()
{
    if(_db_manager== nullptr) _db_manager = new DBManager();
    return _db_manager;
}

DBManager::DBManager()
{
    _db = QSqlDatabase::addDatabase("QPSQL");
    _db.setHostName("abul.db.elephantsql.com");
    _db.setDatabaseName("wpqbitaa");
    _db.setUserName("wpqbitaa");
    _db.setPassword("y31HWiGr_8fsZSTLr9RoNAbHES-kOiLo");

    if (!_db.open())
    {
       qDebug() << "Error: connection with database fail";
    }
    else
    {
       qDebug() << "Database: connection ok";
    }
}

DBManager::~DBManager()
{
    if (_db.isOpen())
    {
        _db.close();
    }
}

bool DBManager::isOpen() const
{
    return _db.isOpen();
}
