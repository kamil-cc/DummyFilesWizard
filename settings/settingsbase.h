#ifndef SETTINGSBASE_H
#define SETTINGSBASE_H

#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QSettings>
#include <QString>

#include "text/statictext.h"

class SettingsBase : public QObject
{
    Q_OBJECT

public:
    //Constructor
    SettingsBase();

    //Destructor
    virtual ~SettingsBase();

    //Methods
    bool validate();
    QString getOutputLocation();
    QString getLanguage();
    QString getConfig();
    QString getInputLocation();
    QString getLogLocation();

    //Shortcut
    typedef StaticText ST;

protected:
    //Variables
    bool valid;
    QString output;
    QString language;
    QString config;
    QString input;
    QString log;

    //Smart setters
    bool setOutputLocation(QString localOutput);
    bool setLanguage(QString localLanguage);
    bool setInputLocation(QString localInput);
    bool setLogLocation(QString localLog);
    bool setConfigLocation(QString configLocation);

    //Other functions
    bool checkFileIsReadable(QString filePath);
    bool checkFileIsWritable(QString filePath);
    bool checkDirectoryIsWritable(QString dirPath);
    void createFile(QString path);
    void createDir(QString localOutput);

    //Const
    const QString DEFAULT_OUTPUT;
    const QString DEFAULT_LANGUAGE;
    const QString DEFAULT_CONFIG;
    const QString DEFAULT_INPUT;
    const QString DEFAULT_LOG;

    //Static const
    static const QString CFG_FILENAME;
    static const QString LOG_FILENAME;
};

#endif // SETTINGSBASE_H
