#include "controller.h"
#include "usermodel.h"

Controller::Controller(QObject *parent) : QObject(parent),
    authWindow(nullptr), mainWindow(nullptr), usermodel(new UserModel()),
    studentmodel(new StudentModel()), listWindow(nullptr), themewidget(nullptr) {}

void Controller::execute(){
    authWindow = new AuthWindow(this);
    authWindow->show();
}

Controller::~Controller() {
    if(mainWindow != nullptr) {
        delete mainWindow;
    }

    if(authWindow != nullptr) {
        delete authWindow;
    }

    if(usermodel != nullptr) {
        delete usermodel;
    }

    if(studentmodel != nullptr) {
        delete studentmodel;
    }

    if(listWindow != nullptr) {
        delete listWindow;
    }

    if(themewidget != nullptr) {
        delete themewidget;
    }
}

void Controller::onCloseMainWindow() {
    bool bCloseWindow(false);

    if(!mainWindow->getFirstName().isEmpty() ||
            !mainWindow->getLastName().isEmpty()) {
        if(QMessageBox::Yes == mainWindow->question(mainWindow,
                                 "Save unchanged data",
                                 "The data have chnaged. Exit anyway ?")) {
            bCloseWindow = true;
        }
    }
    else
    {
        mainWindow->close();
        mainWindow = nullptr;
    }

    if(bCloseWindow) {
        mainWindow->close();
        mainWindow = nullptr;
    }
}

void Controller::onCancelAuthWindow() {
    if(authWindow->question(authWindow, "Quit", "Do you want to quit the application?") == QMessageBox::Yes) {
       authWindow->close();
       authWindow = nullptr;
    }
}

void Controller::onSubmitAuthForm() {
    QString login = authWindow->getLogin();
    QString password = authWindow->getPassword();

    bool status = usermodel->readBy(login, password);
    qDebug(status ? "Yes" : "No");

    if(status == true) {
        themewidget = new ThemeWidget(this, studentmodel->list());
        themewidget->show();
        authWindow->clear();
        authWindow->hide();
    qDebug() << "User luser logged in successfully";
    } else {
         authWindow->warning(authWindow, "Bad", "Incorrect Login/Password, please try again !");
    }
}

void Controller::onCreateStudentMainWindow(){
    QList<QString> studyList = studentmodel->getStudyList();
    QList<QString> classroomList = studentmodel->getClassroomList(studyList.at(0));
    mainWindow = new MainWindow(this, classroomList, studyList);
    mainWindow->disableUpdateButton();
    mainWindow->show();
}

void Controller::onCreateStudent(){
    QString firstName = mainWindow->getFirstName();
    QString lastName = mainWindow->getLastName();
    QString gender = mainWindow->getGender();
    QString study = mainWindow->getStudy();
    QString classroom = mainWindow->getClassroom();
    QString type = mainWindow->getType();

    if (firstName.isEmpty() || lastName.isEmpty())
    {
        mainWindow->warning(mainWindow, "Error", "please complete all fields");
    }
    else
    {
        Student student(firstName, lastName, gender, classroom, study, type);
        studentmodel->create(student);
        mainWindow->clear();
        mainWindow->information(mainWindow, "Creation of a student", "The student has been created successfully");
    }
}

void Controller::onDisplayStudentListWindow()
{
    QList<QString> studyList = studentmodel->getStudyList();
    QList<QString> classroomList = studentmodel->getClassroomList();
    listWindow = new ListWindow(this, classroomList, studyList);
    listWindow->setTableViewModel(studentmodel);
    studentmodel->readAll();
    listWindow->show();
}

void Controller::searchClassroomByStudy(QString study){
    QList<QString> classroomList = studentmodel->getClassroomList(study);
    listWindow->setClassroomList(classroomList);
    //mainWindow->setClassroomList(classroomList);
}

void Controller::searchClassroomByStudy2(QString study){
    QList<QString> classroomList = studentmodel->getClassroomList(study);
    //listWindow->setClassroomList(classroomList);
    mainWindow->setClassroomList(classroomList);
}

void Controller::onUpdateStudent()
{
    QString firstname = mainWindow->getFirstName();
    QString lastname = mainWindow->getLastName();

    if (firstname.isEmpty() || lastname.isEmpty())
    {
        mainWindow->warning(mainWindow, "Error",
                            "Please fill in all fields.");
    }
    else
    {
        QString classroom = mainWindow->getClassroom();
        QString gender = mainWindow->getGender();
        QString study = mainWindow->getStudy();
        QString type = mainWindow->getType();

        QModelIndex index = studentmodel->getSelectionModel()->currentIndex();
        int id = studentmodel->record(index.row()).field(0).value().toInt();

        Student student(id, firstname, lastname, gender, study, classroom, type);
        studentmodel->update(student);

        mainWindow->information(mainWindow, "Updating Student Information",
                                "Successful update.");
        mainWindow->clear();
    }
}

void Controller::onUpdateUIListStudent()
{
    listWindow->close();

    mainWindow = new MainWindow(this, studentmodel->getStudyList(), studentmodel->getStudyList());
    mainWindow->enableUpdateButton();
    mainWindow->show();

    // 1- Récupérer les informations de la person sélectionnée
    QModelIndex index = studentmodel->getSelectionModel()->currentIndex();
    if (index.isValid())
    {
        int ligne = index.row();
        QString firstname = studentmodel->record(ligne).field(1).value().toString();
        QString lastname = studentmodel->record(ligne).field(2).value().toString();
        QString classroom = studentmodel->record(ligne).field(4).value().toString();
        QString gender = studentmodel->record(ligne).field(4).value().toString();

        // 2- Remplir les champs du formulaire mainWindow avec les infos récupérées
        mainWindow->populate(firstname, lastname, classroom, gender);
    }
}

void Controller::onCloseListWindow()
{
    listWindow->close();
    listWindow = nullptr;
}

void Controller::onDeleteListWindow(){
    if (listWindow->question(listWindow, "Suppression", "Êtes vous sûr de vouloir supprimer ?")){
        studentmodel->remove();
    }
 }

void Controller::onSearch(QString arg)
{
    searchClassroomByStudy(arg);
}


void Controller::onSearch()
{
    //QString arg = listWindow->getStudy();
    //searchClassroomByStudy(arg);

    if (!listWindow->getSearch().isEmpty()){
        studentmodel->searchStudent(listWindow->getSearch());
    }
    else if (listWindow->getStudy() != "Studies" && listWindow->getClassroom() == "classroom") {
        studentmodel->searchStudentByStudy(listWindow->getStudy());
    }
    else if (listWindow->getStudy() != "Studies" && listWindow->getClassroom() != "Classrooms") {
        studentmodel->searchStudentByClassroom(listWindow->getClassroom());
    }
    else if (listWindow->getStudy() == "Studies"){
        studentmodel->readAll();
    }
}

void Controller::graph(QString sort){
    QList<Student> students = studentmodel->list();
    QList<QString> classrooms = studentmodel->getClassroomList();
    QList<QString> study = studentmodel->getStudyList();
    if (sort == "Total effectif by gender"){
        themewidget->totalEffectifByGenderBuilder(students);
    }
    else if (themewidget->getGraphSort() == "Students per class") {
        themewidget->studentPerClassesBuilder(students, classrooms);
    }
    else if (themewidget->getGraphSort() == "Students by study"){
        themewidget->studentbyStudyBuilder(students, study);
    }
    else if (themewidget->getGraphSort() == "Student classes type"){
        themewidget->studentInDayAndEveningClassesBuilder(students);
    }
    else {
        themewidget->totalEffectifByGenderBuilder(students);
    }
}
