#ifndef STUDENT_H
#define STUDENT_H
#include <QString>


class Student
{
private:
    int id;
    QString firstName;
    QString lastName;
    QString gender;
    QString study;
    QString classroom;
    QString type;
public:
    Student();
    Student(QString firstName, QString lastName, QString gender, QString study, QString classroom, QString type);
    Student(int id, QString firstName, QString lastName, QString gender, QString classroom, QString study, QString type);
    ~Student(){}

    int getId(){return id;}
    QString getLastName() {return lastName;}
    QString getFirstName() {return firstName;}
    QString getGender() {return gender;}
    QString getStudy() {return study;}
    QString getClassroom() {return classroom;}
    QString getType() {return type;}

    void setId(int id){this->id = id;}
    void setFirstName(QString firstName){this->firstName = firstName;}
    void setLastName(QString lastName){this->lastName = lastName;}
    void setGender(QString gender){this->gender = gender;}
    void setStudy(QString study){this->study = study;}
    void setClassrom(QString classroom){this->classroom = classroom;}
    void setType(QString type){this->type = type;}
};

#endif // STUDENT_H
