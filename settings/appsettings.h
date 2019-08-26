#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <QDateTime>
#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QSettings>
#include <QStringList>
#include <QDir>

#include "text/statictext.h"
#include "console/console.h"


class AppSettings : public QObject
{
    Q_OBJECT
public:
    AppSettings(int inArgc, char *inArgv[], int *outArgc, char ***outArgv);

private:
    //Methods
    void defaultCheck();
    void displayHelp();
    bool setFilesLocation(QString &location);
    bool setLanguage(QString &language);
    bool setConfigLocation(QString &location);
    bool setTextFileLocation(QString &location);
    bool setLogLocation(QString &location);
    void parse(QString arg, QStringList &list);
    void argsInit();
    bool loadFromFile();
    bool loadFromCmd();
    bool loadDefaults();

private:
    //Variables
    QDir destination;
    QString language;
    QString config;
    QString source;
    QString log;
    bool useCmdArgs;
    bool configFromCmd;
    QStringList propertiesList;

private:
    static const QString CFG_FILENAME;
    static const QString LOG_FILENAME;
};

#endif // APPSETTINGS_H
