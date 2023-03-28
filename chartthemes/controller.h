#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QObject>
#include <QMessageBox>
#include <QDate>
#include <QString>
#include <QList>
#include "authwindow.h"
#include "mainwindow.h"
#include "usermodel.h"
#include "studentmodel.h"
#include "listwindow.h"
#include "themewidget.h"


class Controller : public QObject
{
Q_OBJECT

private:
    AuthWindow* authWindow;
    MainWindow* mainWindow;
    UserModel* usermodel;
    StudentModel* studentmodel;
    ListWindow* listWindow;
    ThemeWidget* themewidget;

public slots:
    // Slots liés à la fenêtre MainWindow
    void onCloseMainWindow();
    void onCreateStudentMainWindow();
    void onDisplayStudentListWindow();
    void onCreateStudent();

    // Slots liés à la fenêtre AuthWindow
    void onCancelAuthWindow();
    void onSubmitAuthForm();

    // Slots liés à la fenêtre ListWindow
    void onCloseListWindow();
    void onDeleteListWindow();

    void onUpdateStudent();
    void onUpdateUIListStudent();
    void onSearch();
    void onSearch(QString arg);
    void searchClassroomByStudy(QString study);
    void searchClassroomByStudy2(QString study);
    void graph(QString sort);

public:
    explicit Controller(QObject *parent = nullptr);
    ~Controller();
    void execute();
};

#endif // CONTROLLER_H
