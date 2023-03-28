#include "listwindow.h"
#include "ui_listwindow.h"

ListWindow::ListWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ListWindow)
{
    ui->setupUi(this);
}

ListWindow::ListWindow(QObject *controller, QList<QString> classroomList, QList<QString> studyList, QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::ListWindow())
{
    this->studyList = studyList;
    this->classroomList = classroomList;

    qDebug ("Creation/Initialization of the window which lists the students ...");
    ui->setupUi(this);

    connect(ui->pushButtonCloseListWindow, SIGNAL(clicked()), controller, SLOT(onCloseListWindow()));
    connect(ui->pushButtonUpdate, SIGNAL(clicked()), controller, SLOT(onUpdateUIListStudent()));
    connect(ui->pushButtonDelete, SIGNAL(clicked()), controller, SLOT(onDeleteListWindow()));
    connect(ui->lineEditSearch, SIGNAL(textChanged(QString)), controller, SLOT(onSearch(QString)));
    connect(ui->pushButtonSort, SIGNAL(clicked()), controller, SLOT(onSearch()));
    connect(ui->comboBoxStudy, SIGNAL(currentTextChanged(QString)), controller, SLOT(onSearch(QString)));

    for (int i  = 0; i < this->studyList.size(); i++) {
        ui->comboBoxStudy->addItem(this->studyList[i]);
    }

    updateClassroomByStudy();
}

void ListWindow::setTableViewModel(StudentModel* model)
{
    ui->tableViewListPerson->setModel(model);
    ui->tableViewListPerson->setSelectionModel(model->getSelectionModel());
    ui->tableViewListPerson->show();
}

int ListWindow::getId()
{
    return ui->lineEditSearch->text().toInt();
}

void ListWindow::setClassroomList(const QList<QString> &newClassroomList)
{
    classroomList.clear();
    classroomList = newClassroomList;
    updateClassroomByStudy();
}

ListWindow::~ListWindow()
{
    delete ui;
}

void ListWindow::updateClassroomByStudy(){
    ui->comboBoxClassroom->clear();
    for (int i  = 0; i < this->classroomList.size(); i++) {
        ui->comboBoxClassroom->addItem(this->classroomList[i]);
    }
}

QString ListWindow::getSearch()
{
    return ui->lineEditSearch->text();
}

QString ListWindow::getStudy()
{
    return ui->comboBoxStudy->currentText();
}

QString ListWindow::getClassroom()
{
    return ui->comboBoxClassroom->currentText();
}
