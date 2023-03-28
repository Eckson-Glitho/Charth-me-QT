#ifndef LISTWINDOW_H
#define LISTWINDOW_H

#include <QMainWindow>
#include <QMainWindow>
#include <student.h>
#include <studentmodel.h>
#include "uimain.h"
#include <QAbstractTableModel>
#include <QItemSelectionModel>

namespace Ui {
class ListWindow;
}

class ListWindow : public QMainWindow, public UIMain
{
    Q_OBJECT

public:
    explicit ListWindow(QWidget *parent = nullptr);
    ListWindow(QObject *controller, QList<QString> classroomList, QList<QString> studyList, QWidget *parent = nullptr);
    ~ListWindow();
    void updateClassroomByStudy();
    void setTableViewModel(StudentModel* model);
    int getId();
    QString getSearch();
    QString getStudy();
    QString getClassroom();
    QString getType();
    void setClassroomList(const QList<QString> &newClassroomList);

private:
    Ui::ListWindow *ui;
    QList<QString> classroomList;
    QList<QString> studyList;
};

#endif // LISTWINDOW_H
