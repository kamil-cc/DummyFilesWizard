#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QSettings>
#include <QString>
#include <QStringList>


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
    bool loadFromGivenConfigFile();
    bool checkFileIsReadable(QString filePath);
    bool parseConfigFile(QString filePath);
    bool checkAndCreateDirectory(QString filePath);
    void createFile(QString path);

    //Special setters
    bool setOutputLocation(QString localOutput);
    bool setLanguage(QString localLanguage);
    bool setInputLocation(QString localInput);
    bool setLogLocation(QString localLog);

private:
    //Variables
    bool useCmdArgs;
    bool configFileGiven;
    QStringList argsToBypass;
    QStringList keysToConsume;
    QStringList valuesToConsume;

    //From settings
    QString output;
    QString language;
    QString input;
    QString log;

private:
    //Static constants
    static const QString CFG_FILENAME;
    static const QString LOG_FILENAME;
};

#endif // APPSETTINGS_H
