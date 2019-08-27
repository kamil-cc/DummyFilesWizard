#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QSettings>
#include <QStringList>

#include "text/statictext.h"
#include "console/console.h"


// Enum to easily create flags array
enum Keys {OUTPUT_ENUM, LANGUAGE_ENUM, CONFIG_ENUM, INPUT_ENUM, LOG_ENUM, COUNT};


class AppSettings : public QObject
{
    Q_OBJECT

public:
    //Constructor
    AppSettings(int inArgc, char *inArgv[], int *outArgc, char ***outArgv);

private:
    //Methods
    void displayHelp();
    void parse(QString arg, QStringList &list);
    void argsInit();
    void defaultArgsInit();
    bool loadSettingsFromProvidedFile();
    bool loadSettingsFromCmd();
    bool loadSettingsFromDefaults();
    bool lastKnownConfigExists();
    bool loadLastKnownConfig();
    bool loadSettingsFromFile(QString filePath);

    //Smart setters
    bool setOutputLocation(QString &location);
    bool setLanguage(QString &language);
    bool setConfigLocation(QString &location);
    bool setTextFileLocation(QString &location);
    bool setLogLocation(QString &location);

private:
    //Settings vars
    QDir output;
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
    //Static constants
    static const QString CFG_FILENAME;
    static const QString LOG_FILENAME;
};

#endif // APPSETTINGS_H
