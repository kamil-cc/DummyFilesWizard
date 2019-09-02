#include "dummywizard.h"
#include "ui_dummywizard.h"


/**
 * @brief DummyWizard::DummyWizard Main object constructor.
 * @param parent parent QWidget
 */
DummyWizard::DummyWizard(QApplication &app, AppSettings &settings, QWidget *parent)
                        : QWizard(parent), application(app), configuration(settings){
#ifndef QT_NO_TRANSLATION
    enableTranslator();
#endif

    //wizard.addPage(createConclusionPage()); //TODO

    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setWindowTitle(tr("Dummy Files Wizard")); //TODO
}


/**
 * @brief DummyWizard::~DummyWizard Destructs main object.
 */
DummyWizard::~DummyWizard(){
}


/**
 * @brief DummyWizard::enableTranslator Function create translator object if QT_NO_TRANSLATION was not defined
 * @param application reference to main QApplication object
 */
void DummyWizard::enableTranslator(){
#ifndef QT_NO_TRANSLATION
    //If translation is enabled
    QString translatorFileName = QLatin1String("qt_");
    translatorFileName += QLocale::system().name();
    QTranslator *translator = new QTranslator(&application);
    if (translator->load(translatorFileName,
                         QLibraryInfo::location(QLibraryInfo::TranslationsPath))){
        application.installTranslator(translator);
    }
#endif
}

/**
 * @brief DummyWizard::mousePressEvent Drag and drop functionality
 * @param event mouse left button clicked
 */
void DummyWizard::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        mouseX = event->x();
        mouseY = event->y();
    }
}


/**
 * @brief DummyWizard::mouseMoveEvent Drag and drop functionality
 * @param event mouse move
 */
void DummyWizard::mouseMoveEvent(QMouseEvent *event){
    move(event->globalX() - mouseX, event->globalY() - mouseY);
}
