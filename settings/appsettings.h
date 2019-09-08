#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <QPointer>
#include <QString>
#include <QStringList>

#include "console/console.h"
#include "text/statictext.h"
#include "fileparser.h"

class AppSettings : public QObject
{
    Q_OBJECT

public:
    //Constructor
    AppSettings(int inArgc, char *inArgv[], int *outArgc, char ***outArgv);

    //Destructor
    ~AppSettings();

    //Shortcut
    typedef StaticText ST;

private:
    //Methods
    void parse(QString arg);
    void argsInit();
    bool loadConfigPath();
    void displayHelp();

private:
    //Variables
    bool useCmdArgs;
    bool configFileGiven;
    QStringList argsToBypass;
    QStringList keysToConsume;
    QStringList valuesToConsume;
    QString filePath;

    //Settings object
    SettingsBase *settings;

};

#endif // APPSETTINGS_H
