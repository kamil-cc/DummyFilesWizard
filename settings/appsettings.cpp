#include "appsettings.h"

//Default filenames
const QString AppSettings::CFG_FILENAME = "cfg.ini";
const QString AppSettings::LOG_FILENAME = ".log";

//Shortcut
typedef StaticText ST;

/**
 * @brief AppSettings::initRuntimeArgs Parse command line arguments.
 * @param inArgc counter received from main function
 * @param inArgv arguments received from main function
 * @param outArgc counter passing to QApplication constructor
 * @param outArgv arguments passing to QApplication constructor
 */
AppSettings::AppSettings(int inArgc, char *inArgv[],
                         int *outArgc, char ***outArgv) :
                         useCmdArgs(false), configFromCmd(false){
    QStringList list;

    //For each command line argument
    for(int i = 0; i < inArgc; ++i){
        QString a(inArgv[i]);
        QString arg = a.trimmed();
        parse(arg, list);
    }

    int listLength = list.length();
    char **argv = new char*[listLength];

    //Bypass some args to QApplication
    for(int i = 0; i < listLength; ++i){
        const char *string = list.at(i).toUtf8().constData();
        int len = strlen(string);
        argv[i] = new char[len + 1]; //Terminating character \0
        strncpy(argv[i], string, len + 1);
    }

    //No delete statement because: https://doc.qt.io/qt-5/qapplication.html#QApplication
    //"argc and argv might be changed as Qt removes command line arguments that it recognizes"
    *outArgc = listLength;
    *outArgv = argv;

    //Initialize configuration variables
    argsInit();
}

/**
 * @brief AppSettings::parse Helper function for initRuntimeArgs
 * @param arg single argument
 * @param list transfer commands to QApplication
 */
void AppSettings::parse(QString arg, QStringList &list){
    QString empty("");
    if(arg.startsWith(ST::HELP_CMD, Qt::CaseInsensitive)){
        displayHelp();
    }else if(arg.startsWith(ST::FILES_LOCATION_CMD, Qt::CaseInsensitive)){
        arg.replace(ST::FILES_LOCATION_CMD, empty, Qt::CaseInsensitive);
        propertiesList << ST::OUTPUT_KEY + ST::EQUAL_SIGN + arg;
        useCmdArgs = true;
    }else if(arg.startsWith(ST::LANG_CMD, Qt::CaseInsensitive)){
        arg.replace(ST::LANG_CMD, empty, Qt::CaseInsensitive);
        propertiesList << ST::LANGUAGE_KEY + ST::EQUAL_SIGN + arg;
        useCmdArgs = true;
    }else if(arg.startsWith(ST::CONFIG_LOCATION_CMD, Qt::CaseInsensitive)){
        arg.replace(ST::CONFIG_LOCATION_CMD, empty, Qt::CaseInsensitive);
        propertiesList << ST::CONFIG_KEY + ST::EQUAL_SIGN + arg;
        configFromCmd = true;
    }else if(arg.startsWith(ST::TEXT_LOCATION_CMD, Qt::CaseInsensitive)){
        arg.replace(ST::TEXT_LOCATION_CMD, empty, Qt::CaseInsensitive);
        propertiesList << ST::INPUT_KEY + ST::EQUAL_SIGN + arg;
        useCmdArgs = true;
    }else if(arg.startsWith(ST::LOG_LOCATION_CMD, Qt::CaseInsensitive)){
        arg.replace(ST::LOG_LOCATION_CMD, empty, Qt::CaseInsensitive);
        propertiesList << ST::LOG_KEY + ST::EQUAL_SIGN + arg;
        useCmdArgs = true;
    }else{
        list << arg;
    }
}


/**
 * @brief AppSettings::argsInit Set precedence of settings source
 */
void AppSettings::argsInit(){
    bool result = false;
    do{
        if(configFromCmd){
            result = loadFromFile();
        }else if(useCmdArgs){
            result = loadFromCmd(); // + Fill unset
        }else{
            result = loadDefaults();
            if(!result){
                exit(0);
            }
        }
    }while(!result);
}


bool AppSettings::loadFromFile(){
    return true;
}

bool AppSettings::loadFromCmd(){
    return true;
}

bool AppSettings::loadDefaults(){
    return true;
}



void AppSettings::defaultCheck(){
    QFileInfo info(destination.absolutePath());
    if(!info.isWritable()){
        //QApplication::quit();
    }

    QFile file(config);
    if(!file.exists()){
        file.open(QIODevice::WriteOnly);
        file.close();
    }

    QFileInfo inf(config);
    if(!inf.isWritable()){
        //QApplication::quit();
    }

    QFile file2(log);
    if(!file2.exists()){
        file2.open(QIODevice::WriteOnly);
        file2.close();
    }

    QFileInfo inf2(log);
    if(!inf2.isWritable()){
        //QApplication::quit();
    }
}

/**
 * @brief AppSettings::displayHelp Displays help and stops program before calling constructor QApplication()
 */
void AppSettings::displayHelp(){
    Console::print(ST::HELP_MSG);
    exit(0);
}


/**
 * @brief AppSettings::setFilesLocation Function checks if output dir exists and if is writable
 * @param location path to output dir
 * @return
 */
bool AppSettings::setFilesLocation(QString &location){
    QDir dir = QDir(location);
    QFileInfo info(location);

    if(dir.exists() && info.isDir() && info.isWritable()){
        destination = dir;
    }else{
        return false;
    }
    return true;
}


/**
 * @brief AppSettings::setLanguage Function check if langue parameter is valid
 * @param lang language abbreviation
 * @return
 */
bool AppSettings::setLanguage(QString &lang){
    if(QString::compare(lang, ST::EN_LANG, Qt::CaseInsensitive) == 0){
        language = ST::EN_LANG;
    }else if(QString::compare(lang, ST::PL_LANG, Qt::CaseInsensitive) == 0){
        language = ST::PL_LANG;
    }else{
        return false;
    }
    return true;
}


/**
 * @brief AppSettings::setConfigLocation Checks if configuration file exists
 * @param location path to configuration file
 * @return
 */
bool AppSettings::setConfigLocation(QString &location){
    QFile cfg(location);
    if(cfg.exists()){
        config = location;
    }else{
        return false;
    }
    return true;
}


/**
 * @brief AppSettings::setTextFileLocation Check if specified input file exists and it size is not equal to 0
 * @param location
 * @return
 */
bool AppSettings::setTextFileLocation(QString &location){
    QFile src(location);
    if(src.exists() && (src.size() != 0)){
        source = location;
    }else{
        return false;
    }
    return true;
}


/**
 * @brief AppSettings::setLogLocation Check if path to log file is valid and is writable
 * @param location path to log file
 * @return
 */
bool AppSettings::setLogLocation(QString &location){
    QFile file(location);
    QFileInfo info(location);

    if(!file.exists()){
        file.open(QIODevice::WriteOnly);
        file.close();
    }
    if(info.isFile() && info.isWritable()){
        log = location;
    }else{
        return false;
    }
    return true;
}

//Initialize static vars
/*QDir AppSettings::destination(QDir::currentPath());
QString AppSettings::language("PL");
QString AppSettings::config(QDir::currentPath() +
                            QString(QDir::separator()) + CFG_FILENAME);
QString AppSettings::source("");
QString AppSettings::log(QDir::currentPath() + QString(QDir::separator()) +
                         QDateTime::currentDateTime().toString() + LOG_FILENAME);
bool AppSettings::useCmdArgs(false);
bool AppSettings::configFromCmd(false);*/
