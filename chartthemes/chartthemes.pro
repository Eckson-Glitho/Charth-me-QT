QT += charts sql
requires(qtConfig(combobox))

HEADERS += \
    DBManager.h \
    authwindow.h \
    controller.h \
    dbaccess.h \
    listwindow.h \
    mainwindow.h \
    student.h \
    studentmodel.h \
    themewidget.h \
    uimain.h \
    user.h \
    usermodel.h

SOURCES += \
    authwindow.cpp \
    controller.cpp \
    dbaccess.cpp \
    listwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    student.cpp \
    studentmodel.cpp \
    themewidget.cpp \
    uimain.cpp \
    user.cpp \
    usermodel.cpp

target.path = $$[QT_INSTALL_EXAMPLES]/charts/chartthemes
INSTALLS += target

FORMS += \
    authwindow.ui \
    listwindow.ui \
    mainwindow.ui \
    themewidget.ui
