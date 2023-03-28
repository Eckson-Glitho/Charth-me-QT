#ifndef AUTHWINDOW_H
#define AUTHWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QString>
#include "mainwindow.h"
#include "uimain.h"
#include <iostream>

namespace Ui {
class AuthWindow;
}

class AuthWindow : public QMainWindow, public UIMain
{
    Q_OBJECT

public:
    explicit AuthWindow(QWidget *parent = nullptr);
    AuthWindow(QObject *controller);
    ~AuthWindow();
    QString getLogin();
    QString getPassword();
    void clear();

private:
    Ui::AuthWindow *ui;
};

#endif // AUTHWINDOW_H
