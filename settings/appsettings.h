#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <QDateTime>
#include <QFile>
#include <QFileInfo>
#include <QSettings>
#include <QStringList>
#include <QDir>

#include "text/statictext.h"
#include "console/console.h"


enum Keys {OUTPUT_ENUM, LANGUAGE_ENUM, CONFIG_ENUM, INPUT_ENUM, LOG_ENUM, Count};


class AppSettings : public QObject
{
    Q_OBJECT
public:
    AppSettings(int inArgc, char *inArgv[], int *outArgc, char ***outArgv);

private:
    //Methods
    void defaultCheck(); //TODO DELETE? !
    void displayHelp();

    //Smart setters
    bool setFilesLocation(QString &location);
    bool setLanguage(QString &language);
    bool setConfigLocation(QString &location);
    bool setTextFileLocation(QString &location);
    bool setLogLocation(QString &location);

    void parse(QString arg, QStringList &list);
    void argsInit();
    void defaultArgsInit();
    bool loadFromFile();
    bool loadFromCmd();
    bool loadDefaults();
    bool lastKnownConfigExists();
    bool loadLastKnownConfig();
    bool loadSettingsFromFile(QString filePath);

private:
    //Settings vars
    QDir destination;
    QString language;
    QString config;
    QString source;
    QString log;

    //Default settings
    QString defaultOutputVal;
    QString defaultLanguageVal;
    QString defaultConfigVal;
    QString defaultInputVal;
    QString defaultLogVal;

    //Variables
    bool useCmdArgs;
    bool configFromCmd;
    QStringList propertiesList;

private:
    static const QString CFG_FILENAME;
    static const QString LOG_FILENAME;
};

#endif // APPSETTINGS_H
