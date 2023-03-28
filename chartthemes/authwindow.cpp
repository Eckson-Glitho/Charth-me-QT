#include "authwindow.h"
#include "ui_authwindow.h"

AuthWindow::AuthWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::AuthWindow)
{
    ui->setupUi(this);
}

AuthWindow::AuthWindow(QObject *controller)
    : ui(new Ui::AuthWindow)
{
    ui->setupUi(this);

    connect(ui->pushButtonCancel, SIGNAL(clicked()), controller, SLOT(onCancelAuthWindow()));
    connect(ui->pushButtonSubmit, SIGNAL(clicked()), controller, SLOT(onSubmitAuthForm()));
}

AuthWindow::~AuthWindow()
{
    delete ui;
}

QString AuthWindow::getLogin() {
    return ui->lineEditLogin->text();
}

QString AuthWindow::getPassword() {
    return ui->lineEditPassword->text();
}

void AuthWindow::clear(){
    ui->lineEditLogin->clear();
    ui->lineEditPassword->clear();
}
