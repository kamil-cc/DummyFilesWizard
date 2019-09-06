#ifndef SETTINGSBASE_H
#define SETTINGSBASE_H

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

    //Inteligent setters
    bool setOutputLocation(QString localOutput);
    bool setLanguage(QString localLanguage);
    bool setInputLocation(QString localInput);
    bool setLogLocation(QString localLog);

    //Other functions
    bool checkFileIsReadable(QString filePath);
    void createFile(QString path);
};

#endif // SETTINGSBASE_H
