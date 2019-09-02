#include "appsettings.h"


//Default filenames
const QString AppSettings::CFG_FILENAME = "cfg.ini";
const QString AppSettings::LOG_FILENAME = ".log";


//Shortcut
typedef StaticText ST;


/**
 * @brief AppSettings::AppSettings Parse command line arguments. Init settings.
 * @param inArgc counter received from main function
 * @param inArgv arguments received from main function
 * @param outArgc counter bypassing to QApplication constructor
 * @param outArgv arguments bypassing to QApplication constructor
 */
AppSettings::AppSettings(int inArgc, char *inArgv[],
                         int *outArgc, char ***outArgv) :
                         useCmdArgs(false), configFileGiven(false){
    //For each command line argument
    for(int i = 0; i < inArgc; ++i){
        QString a(inArgv[i]);
        QString arg = a.trimmed();
        parse(arg);
    }

    int listLength = argsToBypass.length();
    char **argv = new char*[listLength];

    //Bypass some args to QApplication
    for(int i = 0; i < listLength; ++i){
        const char *string = argsToBypass.at(i).toUtf8().constData();
        int len = strlen(string);
        argv[i] = new char[len + 1]; //Terminating character \0
        strncpy(argv[i], string, len + 1);
    }

    //No delete statement because:
    //https://doc.qt.io/qt-5/qapplication.html#QApplication
    //"argc and argv might be changed as Qt
    //removes command line arguments that it recognizes"
    *outArgc = listLength;
    *outArgv = argv;

    //Initialize configuration variables
    argsInit();
}


/**
 * @brief AppSettings::parse Divide arguments list into two subests
 * @param arg single argument
 * @param list transfer commands to QApplication
 */
void AppSettings::parse(QString arg){
    QString equals("=");

    if(arg.startsWith(ST::HELP_CMD, Qt::CaseInsensitive)){
        displayHelp();
    }else if(arg.startsWith(ST::FILES_LOCATION_CMD, Qt::CaseInsensitive)){
        QStringList splitted = arg.split(equals);
        QString key = QString(splitted.at(0));
        key = key.remove(0, 1);
        keysToConsume << key;
        valuesToConsume << QString(splitted.at(1));
        useCmdArgs = true;
    }else if(arg.startsWith(ST::LANG_CMD, Qt::CaseInsensitive)){
        QStringList splitted = arg.split(equals);
        QString key = QString(splitted.at(0));
        key = key.remove(0, 1);
        keysToConsume << key;
        valuesToConsume << QString(splitted.at(1));
        useCmdArgs = true;
    }else if(arg.startsWith(ST::CONFIG_LOCATION_CMD, Qt::CaseInsensitive)){
        QStringList splitted = arg.split(equals);
        QString key = QString(splitted.at(0));
        key = key.remove(0, 1);
        keysToConsume << key;
        valuesToConsume << QString(splitted.at(1));
        configFileGiven = true;
    }else if(arg.startsWith(ST::TEXT_LOCATION_CMD, Qt::CaseInsensitive)){
        QStringList splitted = arg.split(equals);
        QString key = QString(splitted.at(0));
        key = key.remove(0, 1);
        keysToConsume << key;
        valuesToConsume << QString(splitted.at(1));
        useCmdArgs = true;
    }else if(arg.startsWith(ST::LOG_LOCATION_CMD, Qt::CaseInsensitive)){
        QStringList splitted = arg.split(equals);
        QString key = QString(splitted.at(0));
        key = key.remove(0, 1);
        keysToConsume << key;
        valuesToConsume << QString(splitted.at(1));
        useCmdArgs = true;
    }else{
        argsToBypass << arg;
    }
}


/**
 * @brief AppSettings::argsInit Set precedence of config sources. Load settings.
 */
void AppSettings::argsInit(){
    QString filePath;





}


/*int length = keysToConsume.length();
if(length > 0){
    if(keysToConsume.contains(ST::CONFIG_LOCATION_KEY)){
        int idx = keysToConsume.indexOf(ST::CONFIG_LOCATION_KEY);
        filePath = valuesToConsume.at(idx);
    }
}*/


/**
 * @brief AppSettings::displayHelp Displays help and stops program before calling constructor QApplication()
 */
void AppSettings::displayHelp(){
    Console::print(ST::HELP_MSG);
    exit(0);
}

