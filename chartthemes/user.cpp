#include "user.h"

User::User(){}

User::User(QString login, QString password) {
    this->id = -1;
    this->login = login;
    this->password = password;
}

User::User(int id, QString login, QString password) {
    this->id = id;
    this->login = login;
    this->password = password;
}
