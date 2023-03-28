#ifndef STUDENTMODEL_H
#define STUDENTMODEL_H
#include "dbaccess.h"
#include "student.h"
#include <QtDebug>
#include <QMetaType>
#include <QSqlQuery>
#include <QSqlField>
#include <QSqlRecord>
#include <QSqlQueryModel>
#include <QItemSelectionModel>
#include <QModelIndex>


class StudentModel : public QSqlQueryModel
{
private:
    DBAccess* dbaccess;
    QItemSelectionModel* selectionModel;

public:
    StudentModel();
    ~StudentModel();

    void create(Student student);
    void update(Student student);
    Student read(int id);
    void _delete (int id);
    QList<Student> list();
    void readAll();
    void remove();
    void searchStudent(QString arg);
    QItemSelectionModel* getSelectionModel() {return selectionModel;}
    QList<QString>getClassroomList();
    QList<QString>getClassroomList(QString study);
    void searchStudentByStudy(QString study);
    void searchStudentByClassroom(QString classroom);
    QList<QString>getStudyList();
};

#endif // STUDENTMODEL_H
