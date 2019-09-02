#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <QString>
#include <QStringList>
#include <QMap>

#include "text/statictext.h"
#include "console/console.h"


class AppSettings : public QObject
{
    Q_OBJECT

public:
    //Constructor
    AppSettings(int inArgc, char *inArgv[], int *outArgc, char ***outArgv);

private:
    //Methods
    void parse(QString arg);
    void argsInit();
    void displayHelp();

private:
    //Variables
    bool useCmdArgs;
    bool configFileGiven;
    QStringList argsToBypass;
    QStringList keysToConsume;
    QStringList valuesToConsume;

private:
    //Static constants
    static const QString CFG_FILENAME;
    static const QString LOG_FILENAME;
};

#endif // APPSETTINGS_H
