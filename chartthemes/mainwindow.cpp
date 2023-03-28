#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::MainWindow(QObject *controller, QList<QString> classroomList, QList<QString> studyList, QWidget *parent) :  QMainWindow(parent), ui(new Ui::MainWindow)
{
    this->studyList = studyList;
    this->classroomList = classroomList;
    qDebug ("Creation/Initialization of the window which lists the Persons ...");
    ui->setupUi(this);
    connect(ui->pushButtonClose, SIGNAL(clicked()), controller, SLOT(onCloseMainWindow()));
    connect(ui->pushButtonCreate, SIGNAL(clicked()), controller, SLOT(onCreateStudent()));
    connect(ui->pushButtonUpdate, SIGNAL(clicked()), controller, SLOT(onUpdateStudent()));

    for (int i  = 0; i < this->studyList.size(); i++) {
        ui->comboBoxStudy->addItem(this->studyList[i]);
    }

    updateClassroomByStudy();

    connect(ui->comboBoxStudy, SIGNAL(currentIndexChanged(QString)), controller, SLOT(searchClassroomByStudy2(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::getFirstName() {
    return ui->lineEditFirstName->text();
}

QString MainWindow::getLastName() {
    return ui->lineEditLastName->text();
}

QString MainWindow::getClassroom() {
    return ui->comboBoxClassroom->currentText();
}

QString MainWindow::getGender() {
    return ui->comboBoxGender->currentText();
}

QString MainWindow::getStudy() {
    return ui->comboBoxStudy->currentText();
}

QString MainWindow::getType() {
    return ui->comboBoxType->currentText();
}

void MainWindow::clear(){
    ui->lineEditFirstName->clear();
    ui->lineEditLastName->clear();
    ui->comboBoxClassroom->clear();
    ui->comboBoxGender->clear();
}

void MainWindow::disableUpdateButton()
{
    ui->pushButtonUpdate->setEnabled(false);
    ui->pushButtonCreate->setEnabled(true);
}

void MainWindow::enableUpdateButton()
{
    ui->pushButtonUpdate->setEnabled(true);
    ui->pushButtonCreate->setEnabled(false);
}

void MainWindow::populate(QString firstname, QString lastname, QString classroom, QString gender)
{
   ui->lineEditFirstName->setText(firstname);
   ui->lineEditLastName->setText(lastname);
   ui->comboBoxClassroom->setCurrentText(classroom);
   ui->comboBoxGender->setCurrentText(gender);
}

void MainWindow::updateClassroomByStudy(){
    ui->comboBoxClassroom->clear();
    for (int i  = 0; i < this->classroomList.size(); i++) {
        if (classroomList[i] != "classroom"){
            ui->comboBoxClassroom->addItem(this->classroomList[i]);
        }
    }
}

void MainWindow::setClassroomList(const QList<QString> &newClassroomList)
{
    classroomList.clear();
    classroomList = newClassroomList;
    updateClassroomByStudy();
}
