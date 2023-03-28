#ifndef DBMANAGER_H
#define DBMANAGER_H
#include <QSqlDatabase>

class DBManager {
    public:
        static DBManager& instance() {
            static DBManager instance; // Singleton
            return instance;
        }

        QSqlDatabase& database() {
            return m_database;
        }

    private:
        DBManager() {
            m_database = QSqlDatabase::addDatabase("QSQLITE");
            m_database.setDatabaseName("C:\\Workspace\\QT-Workspace\\Databeses\\user_sqlite.db");

            if (!m_database.open()) {
                // Gérer l'erreur de connexion
            }
        }

        ~DBManager() {
            m_database.close();
        }

        QSqlDatabase m_database;

        // Empêche la copie et l'affectation par valeur
        DBManager(const DBManager&);
        void operator=(const DBManager&);
};

#endif // DBMANAGER_H
