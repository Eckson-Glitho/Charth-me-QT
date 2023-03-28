#ifndef USER_H
#define USER_H
#include <QString>


class User
{
private:
    int id;
    QString login;
    QString password;

public:
    User();
    User(QString login, QString password);
    User(int id, QString login, QString password);
    ~User() {}

    int getId() { return id; }
    QString getPassword() { return password; }
    QString getLogin() { return login; }


    void setId(int id) { this->id = id; }
    void setPassword(QString password) { this->password = password; }
    void setLogin(QString login) { this->login = login; }
};

#endif // USER_H
