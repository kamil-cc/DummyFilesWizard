#ifndef DUMMYWIZARD_H
#define DUMMYWIZARD_H

#include <QApplication>
#include <QDir>
#include <QMouseEvent>
#include <QString>
#include <QWizard>

#define QT_NO_TRANSLATION

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
    explicit DummyWizard(QWidget *parent = 0);
    ~DummyWizard();

public:
    //Static methods
    static void enableTranslator(QApplication &app);
    static void initRuntimeArgs(int inArgc, char *inArgv[],
                                int *outArgc, char ***outArgv);

private:
    //Methods
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    //Static methods
    static void displayHelp();
    static bool setFilesLocation(QString &location);
    static bool setLanguage(QString &language);
    static bool setConfigLocation(QString &location);
    static bool setTextFileLocation(QString &location);
    static bool setLogLocation(QString &location);
    static void parse(QString arg, QStringList &list);

private:
    //Vars
    int mouseX;
    int mouseY;
    bool mouseHoover;

private:
    //Static vars
    static QDir destination;
    static QString language;
    static QString config;
    static QString source;
    static QString log;
    static bool useCmdArgs;
    static bool configFromCmd;
};

#endif // DUMMYWIZARD_H
