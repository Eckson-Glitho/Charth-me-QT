#include "studentmodel.h"
#include <QMetaType>
#include <QSqlField>
#include <QtDebug>
#include <QSqlError>

StudentModel::StudentModel()
{
    selectionModel = new QItemSelectionModel(this);
    dbaccess = new DBAccess();
}

StudentModel::~StudentModel()
{
    delete dbaccess;
}

Student StudentModel::read(int id)
{
    Student student;
    try {
        dbaccess->open();
        QSqlQuery query(dbaccess->database());

        query.prepare("SELECT * FROM t_students WHERE id=:id");
        query.bindValue(":id", id);

        query.exec();

        if (query.next())
        {
            student.setId(query.record().field("id").value().toInt());
            student.setFirstName(query.record().field("firstName").value().toString());
            student.setLastName(query.record().field("lastName").value().toString());
            student.setGender(query.record().field("gender").value().toString());
            student.setStudy(query.record().field("study").value().toString());
            student.setClassrom(query.record().field("classroom").value().toString());
            student.setType(query.record().field("type").value().toString());
        }

        dbaccess->close();

        qDebug ("Student retrieved successfully");
    }  catch (const QSqlError& error) {
        qDebug() << "An unexpected exception was thrown in the StudentModel read function" << error.text();
    }

    return student;
}

void StudentModel::create(Student student)
{
    try {
        dbaccess->open();
        QSqlQuery query(dbaccess->database());


        query.prepare("INSERT INTO t_students (firstName, lastName, gender, study, classroom, type) VALUES (:firstName, :lastName, :gender, :study, :classroom, :type)");
        query.bindValue(":firstName", student.getFirstName());
        query.bindValue(":lastName", student.getLastName());
        query.bindValue(":gender", student.getGender());
        query.bindValue(":study", student.getStudy());
        query.bindValue(":classroom", student.getClassroom());
        query.bindValue(":type", student.getType());

        query.exec();

        dbaccess->close();
        qDebug ("Student created successfully");
    }  catch (const QSqlError& error) {
        qDebug() << "An unexpected exception was thrown in the StudentModel create function" << error.text();
    }
}

QList<Student> StudentModel::list()
{
    Student student;
    QList<Student> students;
    try {
        dbaccess->open();
        QSqlQuery query(dbaccess->database());

        query.prepare("SELECT * FROM t_students WHERE 1");
        query.exec();

        while (query.next())
        {
            student.setId(query.record().field("id").value().toInt());
            student.setFirstName(query.record().field("firstName").value().toString());
            student.setLastName(query.record().field("lastName").value().toString());
            student.setGender(query.record().field("gender").value().toString());
            student.setStudy(query.record().field("study").value().toString());
            student.setClassrom(query.record().field("classroom").value().toString());
            student.setType(query.record().field("type").value().toString());
            students.push_back(student);
        }

        dbaccess->close();

        qDebug ("Student list retrieved successfully");
    }  catch (const QSqlError& error) {
        qDebug() << "An unexpected exception was thrown in the StudentModel list function" << error.text();
    }

    return students;
}

void StudentModel::update(Student student)
{
    try {
        dbaccess->open();
        QSqlQuery query(dbaccess->database());

        query.prepare("UPDATE t_students SET firstName=:firstName, lastName=:lastName, gender=:gender, study=:study, classroom=:classroom, type=:type WHERE id=:id");

        query.bindValue(":id", student.getId());
        query.bindValue(":firstName", student.getFirstName());
        query.bindValue(":lastName", student.getLastName());
        query.bindValue(":gender", student.getGender());
        query.bindValue(":study", student.getStudy());
        query.bindValue(":classroom", student.getClassroom());
        query.bindValue(":type", student.getType());

        query.exec();
        readAll();

        dbaccess->close();
        qDebug ("Student updated successfully");
    }  catch (const QSqlError& error) {
        qDebug() << "An unexpected exception was thrown in the StudentModel update function" << error.text();
    }
}

void StudentModel::_delete(int id)
{
    try {
        dbaccess->open();
        QSqlQuery query(dbaccess->database());

        query.prepare("DELETE FROM t_students WHERE id=:id");
        query.bindValue(":id", id);

        query.exec();
        readAll();

        dbaccess->close();
        qDebug ("Student delete successfully");
    }  catch (const QSqlError& error) {
        qDebug() << "An unexpected exception was thrown in the StudentModel _delete function" << error.text();
    }
}

void StudentModel::readAll()
{
    try {
        dbaccess->open();

        QSqlDatabase database = dbaccess->database();

        this->setQuery("SELECT * FROM t_students", database);
        this->setHeaderData(0, Qt::Horizontal, tr("Id"));
        this->setHeaderData(1, Qt::Horizontal, tr("Firstname"));
        this->setHeaderData(2, Qt::Horizontal, tr("Lastname"));
        this->setHeaderData(3, Qt::Horizontal, tr("Gender"));
        this->setHeaderData(4, Qt::Horizontal, tr("studdy"));
        this->setHeaderData(5, Qt::Horizontal, tr("classroom"));
        this->setHeaderData(6, Qt::Horizontal, tr("type"));

        dbaccess->close();
        qDebug ("Students successfully read");
    }  catch (const QSqlError& error) {
        qDebug() << "An unexpected exception was thrown in the StudentModel readAll function" << error.text();
    }
}

void StudentModel::remove()
{
    try {
        dbaccess->open();

        QModelIndex currentIndex = selectionModel->currentIndex();

        if(currentIndex.isValid()) {
            int line = currentIndex.row();
            QSqlRecord record = this->record(line);
            int id = record.field(0).value().toInt();

            QSqlQuery query(dbaccess->database());
            query.prepare("DELETE FROM t_students WHERE id=:id");
            query.bindValue(":id", id);

            query.finish();
            query.exec();

        }

        dbaccess->close();
        readAll();
        qDebug ("Student remove successfully");
    } catch (const QSqlError& error) {
        qDebug() << "An unexpected exception was thrown in the StudentModel remove function" << error.text();
    }
}

QList<QString> StudentModel::getClassroomList(){
    QList<QString> studies;

    dbaccess->open();
    QSqlQuery query(dbaccess->database());

    query.prepare("SELECT * FROM t_classroom WHERE 1");
    query.exec();

    while (query.next()) {
        QString label = query.record().field("name").value().toString();
        studies.push_back(label);
    }

    dbaccess->close();

    return studies;
}

void StudentModel::searchStudent(QString label)
{
    dbaccess->open();

    QSqlQuery query(dbaccess->database());

    QString str = "SELECT * FROM t_students WHERE firstname LIKE :label OR lastname LIKE :label";
    query.prepare(str);
    query.bindValue(":label", "%" + label + "%");
    query.exec();

    this->setQuery(query);

    this->setHeaderData(0, Qt::Horizontal, tr("Id"));
    this->setHeaderData(1, Qt::Horizontal, tr("Firstname"));
    this->setHeaderData(2, Qt::Horizontal, tr("Lastname"));
    this->setHeaderData(3, Qt::Horizontal, tr("Gender"));
    this->setHeaderData(4, Qt::Horizontal, tr("studdy"));
    this->setHeaderData(4, Qt::Horizontal, tr("classroom"));
    this->setHeaderData(4, Qt::Horizontal, tr("type"));

    dbaccess->close();
}

void StudentModel::searchStudentByStudy(QString study){
    dbaccess->open();

    QSqlQuery query(dbaccess->database());

    query.prepare("SELECT * FROM t_students WHERE study=:study");
    query.bindValue(":study", study);
    query.exec();

    this->setQuery(query);

    this->setHeaderData(0, Qt::Horizontal, tr("Id"));
    this->setHeaderData(1, Qt::Horizontal, tr("Firstname"));
    this->setHeaderData(2, Qt::Horizontal, tr("Lastname"));
    this->setHeaderData(3, Qt::Horizontal, tr("Gender"));
    this->setHeaderData(4, Qt::Horizontal, tr("study"));
    this->setHeaderData(4, Qt::Horizontal, tr("classroom"));
    this->setHeaderData(4, Qt::Horizontal, tr("type"));

    dbaccess->close();

}

void StudentModel::searchStudentByClassroom(QString classroom){
    dbaccess->open();

    QSqlQuery query(dbaccess->database());

    query.prepare("SELECT * FROM t_students WHERE classroom = :classroom");
    query.bindValue(":classroom", classroom);
    query.exec();

    this->setQuery(query);

    this->setHeaderData(0, Qt::Horizontal, tr("Id"));
    this->setHeaderData(1, Qt::Horizontal, tr("Firstname"));
    this->setHeaderData(2, Qt::Horizontal, tr("Lastname"));
    this->setHeaderData(3, Qt::Horizontal, tr("Gender"));
    this->setHeaderData(4, Qt::Horizontal, tr("study"));
    this->setHeaderData(4, Qt::Horizontal, tr("classroom"));
    this->setHeaderData(4, Qt::Horizontal, tr("type"));

    dbaccess->close();

}

QList<QString> StudentModel::  getClassroomList(QString study) {
    QList<QString> classrooms;

    dbaccess->open();
    QSqlQuery query(dbaccess->database());

    query.prepare("SELECT * FROM t_classroom WHERE study = :study");
    query.bindValue(":study", study);
    query.exec();

    while (query.next()) {
        QString label = query.record().field("name").value().toString();
        classrooms.push_back(label);
    }

    dbaccess->close();

    return classrooms;
}

QList<QString> StudentModel::getStudyList(){
    QList<QString> studies;

    dbaccess->open();
    QSqlQuery query(dbaccess->database());

    query.prepare("SELECT * FROM t_study WHERE 1");
    query.exec();

    while (query.next()) {
        QString label = query.record().field("name").value().toString();
        studies.push_back(label);
    }

    dbaccess->close();

    return studies;
}
