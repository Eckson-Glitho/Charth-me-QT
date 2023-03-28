#ifndef UIMAIN_H
#define UIMAIN_H

#include <QMessageBox>

class UIMain
{
public:
    explicit UIMain();

    int information(QWidget *parent, QString title, QString text);
    int warning(QWidget *parent, QString title, QString text);
    int question(QWidget *parent, QString title, QString text);
};

#endif // UIMAIN_H
