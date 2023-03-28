#include "usermodel.h"
#include <QMetaType>
#include <QtSql/QSqlField>
#include <QtDebug>
#include <QSqlError>

UserModel::UserModel()
{
    dbaccess = new DBAccess();
}

UserModel::~UserModel()
{
    delete dbaccess;
}

User UserModel::read(int id)
{
    User user;
    try {
        dbaccess->open();
        QSqlQuery query(dbaccess->database());

        query.prepare("SELECT * FROM t_users WHERE id=:id");
        query.bindValue(":id", id);

        query.exec();

        if (query.next())
        {
            user.setId(query.record().field("id").value().toInt());
            user.setLogin(query.record().field("login").value().toString());
            user.setPassword(query.record().field("password").value().toString());
        }

        dbaccess->close();
        qDebug ("User retrieved successfully");
    }  catch (const QSqlError& error) {
        qDebug() << "An unexpected exception was thrown in the usermodel read function" << error.text();
    }

    return user;
}

bool UserModel::readBy(QString login, QString password)
{
    bool status (false);

    dbaccess->open();
    QSqlQuery query(dbaccess->database());

    query.prepare("SELECT * FROM t_users WHERE login=:login AND password=:password");
    query.bindValue(":login", login);
    query.bindValue(":password", password);
    query.exec();

    if (query.next()) {
            status = true;
        }

    dbaccess->close();

    return status;
}

void UserModel::create(User user)
{
    try {
        dbaccess->open();
        QSqlQuery query(dbaccess->database());

        query.prepare("INSERT INTO t_users (login, password) VALUES (:login, :password)");

        query.bindValue(":login", user.getLogin());
        query.bindValue(":password", user.getPassword());

        query.exec();

        dbaccess->close();
        qDebug ("User created successfully");
    }  catch (const QSqlError& error) {
        qDebug() << "An unexpected exception was thrown in the usermodel create function" << error.text();
    }
}

void UserModel::update(User user)
{
    try {
        dbaccess->open();
        QSqlQuery query(dbaccess->database());

        query.prepare("UPDATE t_users SET login=:login, password=:password WHERE id=:id");

        query.bindValue(":id", user.getId());
        query.bindValue(":login", user.getLogin());
        query.bindValue(":password", user.getPassword());

        query.exec();

        dbaccess->close();
        qDebug ("User updated successfully");
    }  catch (const QSqlError& error) {
        qDebug() << "An unexpected exception was thrown in the usermodel update function" << error.text();
    }
}

void UserModel::_delete(int id)
{
    try {
        dbaccess->open();
        QSqlQuery query(dbaccess->database());

        query.prepare("DELETE FROM t_users WHERE id=:id");
        query.bindValue(":id", id);

        query.exec();

        dbaccess->close();
        qDebug ("User delete successfully");
    }  catch (const QSqlError& error) {
        qDebug() << "An unexpected exception was thrown in the usermodel _delete function" << error.text();
    }
}

QList<User> UserModel::list()
{
    User user;
    QList<User> users;
    try {
        dbaccess->open();
        QSqlQuery query(dbaccess->database());

        query.prepare("SELECT * FROM t_users WHERE 1");
        query.exec();

        while (query.next())
        {
            user.setId(query.record().field("id").value().toInt());
            user.setLogin(query.record().field("login").value().toString());
            user.setPassword(query.record().field("password").value().toString());

            users.push_back(user);
        }

        dbaccess->close();
        qDebug ("Student list retrieved successfully");
    }  catch (const QSqlError& error) {
        qDebug() << "An unexpected exception was thrown in the usermodel list function" << error.text();
    }

    return users;
}
