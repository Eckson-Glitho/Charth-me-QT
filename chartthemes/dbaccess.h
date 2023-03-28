#ifndef DBACCESS_H
#define DBACCESS_H
#include <QSqlDatabase>
#include "DBManager.h"


class DBAccess
{
    private:
        QSqlDatabase db;

    public:
        QSqlDatabase database()
        {
            return db;
        }
        DBAccess();
        ~DBAccess();

        bool open();
        void close();
};

#endif // DBACCESS_H
