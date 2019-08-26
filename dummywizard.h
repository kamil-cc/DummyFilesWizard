#ifndef DUMMYWIZARD_H
#define DUMMYWIZARD_H

#include <QApplication>
#include <QMouseEvent>
#include <QString>
#include <QWizard>
#include "settings/appsettings.h"

//#define QT_NO_TRANSLATION

#ifndef QT_NO_TRANSLATION
    //If translation is enabled
    #include <QTranslator>
    #include <QLibraryInfo>
#endif

namespace Ui {
class DummyWizard; //TODO Is that necessary?
}


class DummyWizard : public QWizard
{
    Q_OBJECT

public:
    //Methods
    DummyWizard(QApplication &app, AppSettings &settings, QWidget *parent = 0);
    ~DummyWizard();

private:
    //Methods
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void enableTranslator();

private:
    //Vars
    int mouseX;
    int mouseY;
    QApplication &application;
    AppSettings &configuration;

};

#endif // DUMMYWIZARD_H
