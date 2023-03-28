#include "student.h"

Student::Student(){}

Student::Student(QString firstName, QString lastName, QString gender, QString classroom, QString study, QString type)
{
    this->id = -1;
    this->firstName = firstName;
    this->lastName = lastName;
    this->gender = gender;
    this->study = study;
    this->classroom = classroom;
    this->type = type;
}

Student::Student(int id, QString firstName, QString lastName, QString gender, QString study, QString classroom, QString type)
{
    this->id = id;
    this->firstName = firstName;
    this->lastName = lastName;
    this->gender = gender;
    this->study = study;
    this->classroom = classroom;
    this->type = type;
}
