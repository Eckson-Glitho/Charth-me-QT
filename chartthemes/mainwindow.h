#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "uimain.h"
//#include "person.h"
#include <QString>
#include <QList>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow :
        public QMainWindow, public UIMain
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    MainWindow(QObject *controller, QList<QString> classroomList, QList<QString> studyList, QWidget *parent = nullptr);
    ~MainWindow();

    QString getFirstName();
    QString getLastName();
    QString getClassroom();
    QString getGender();
    QString getStudy();
    QString getType();

    void clear();

    void disableUpdateButton();
    void enableUpdateButton();
    void populate(QString firstname, QString lastname, QString classroom, QString gender);
    void setClassroomList(const QList<QString> &newClassroomList);
    void updateClassroomByStudy();

private slots:

private:
    Ui::MainWindow *ui;
    QList<QString> classroomList;
    QList<QString> studyList;
};

#endif // MAINWINDOW_H
