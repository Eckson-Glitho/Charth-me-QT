#include "dbaccess.h"

DBAccess::DBAccess()
{
    db = DBManager::instance().database();

    qDebug("Access to database 'users.db' effective!!!");
}

bool DBAccess::open()
{
    if (db.isOpen() == true) return true;

    if (db.open() == true)
    {
        qDebug("Open connection with the database!!!");
        return true;
    }
    else {
        qDebug("Failed to open database connection!!!!!!!!");
        return false;
    }
}

void DBAccess::close()
{
    if (db.isOpen() == false) return;

    db.close();
    qDebug("Connection closed successfully!!!");
}

DBAccess::~DBAccess(){}
