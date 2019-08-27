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
 * @param outArgc counter passing to QApplication constructor
 * @param outArgv arguments passing to QApplication constructor
 */
AppSettings::AppSettings(int inArgc, char *inArgv[],
                         int *outArgc, char ***outArgv) :
                         useCmdArgs(false), configFromCmd(false),
                         prepareToStore(false) {
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
 * @brief AppSettings::argsInit Set precedence of config sources. Load settings.
 */
void AppSettings::argsInit(){
    defaultArgsInit();
    bool lastKnownConfig = lastKnownConfigExists();
    bool result = false;

    //Check settings sources in right order.
    //If one fails try another.
    do{
        if(configFromCmd){
            result = loadSettingsFromProvidedFile();
            if(!result){
                Console::print(ST::WRONG_CONFIG_MSG);
                configFromCmd = false;
            }
        }else if(useCmdArgs){
            result = loadSettingsFromCmd();
            if(!result){
                useCmdArgs = false;
            }
        }else if(lastKnownConfig){
            result = loadLastKnownConfig();
            if(!result){
                lastKnownConfig = false;
            }else{
                prepareToStore = true;
            }
        }else{
            result = loadSettingsFromDefaults();
            if(!result){
                exit(0);
            }else{
                prepareToStore = true;
            }
        }
    }while(!result);

    if(prepareToStore){

    }
}


/**
 * @brief AppSettings::defaultArgsInit Set default configuration values.
 */
void AppSettings::defaultArgsInit(){
    defaultOutputVal = QDir::currentPath();
    defaultLanguageVal = ST::PL_LANG;
    defaultConfigVal = QDir::currentPath() +
                       QString(QDir::separator()) +
                       CFG_FILENAME;
    defaultInputVal = "";
    defaultLogVal = QDir::currentPath() +
                    QString(QDir::separator()) +
                    QDateTime::currentDateTime().toString() +
                    LOG_FILENAME;
}


/**
 * @brief AppSettings::lastKnownConfigExists Check if default configuration file exists.
 * @return true if file exist, false if file does not exist
 */
bool AppSettings::lastKnownConfigExists(){
    QFile file(defaultConfigVal);
    QFileInfo info(defaultConfigVal);

    if((!file.exists()) || (!info.isReadable())){
        return false;
    }
    return true;
}


/**
 * @brief AppSettings::loadLastKnownConfig Load confing file from execution directory.
 * @return
 */
bool AppSettings::loadLastKnownConfig(){
    return loadSettingsFromFile(defaultConfigVal);
}


/**
 * @brief AppSettings::loadSettingsFromProvidedFile
 * @return
 */
bool AppSettings::loadSettingsFromProvidedFile(){
    QString filePath("");
    int listLength = propertiesList.length();
    for(int i = 0; i < listLength; ++i){ //Map emulation
        QString key = propertiesList.at(i).split(ST::EQUAL_SIGN).at(0);
        QString value = propertiesList.at(i).split(ST::EQUAL_SIGN).at(1);
        if(QString::compare(key, ST::CONFIG_KEY, Qt::CaseInsensitive) == 0){
            filePath = value;
        }
    }
    if(filePath.length() == 0){
        return false;
    }

    QFile file(filePath);
    QFileInfo info(filePath);
    if((!file.exists()) || (!info.isReadable())){
        return false;
    }

    return loadSettingsFromFile(filePath);
}


/**
 * @brief AppSettings::loadSettingsFromFile load settings from specified file
 * @param filePath path to configuration file
 * @return true if settings imported, false otherwise
 */
bool AppSettings::loadSettingsFromFile(QString filePath){
    bool flags[COUNT] = {0};
    QSettings settings(filePath, QSettings::IniFormat);
    QString outputVal = settings.value(ST::OUTPUT_KEY, "").toString();
    QString languageVal = settings.value(ST::LANGUAGE_KEY, "").toString();
    QString configVal = settings.value(ST::CONFIG_KEY, "").toString();
    QString inputVal = settings.value(ST::INPUT_KEY, "").toString();
    QString logVal = settings.value(ST::LOG_KEY, "").toString();

    if(outputVal.length() != 0){
        flags[OUTPUT_ENUM] = true;
    }
    if(languageVal.length() != 0){
        flags[LANGUAGE_ENUM] = true;
    }

    flags[CONFIG_ENUM] = true; //By definition
    flags[INPUT_ENUM] = true; //By definition

    if(logVal.length() != 0){
        flags[LOG_ENUM] = true;
    }

    for(int i = 0; i < COUNT; ++i){
        if(flags[i] == false){
            return false;
        }
    }

    if(!setOutputDirLocation(outputVal)){
        return false;
    }

    if(!setLanguage(languageVal)){
        return false;
    }

    setConfigFileLocation(filePath); //Do not check

    if(!setInputFileLocation(inputVal)){
        return false;
    }

    if(!setLogFileLocation(logVal)){
        return false;
    }
    return true;
}

/**
 * @brief AppSettings::loadSettingsFromCmd Try to initialize settings with commandline arguments.
 * @return true commandline arguments are valid, false commandline arguments are invalid
 */
bool AppSettings::loadSettingsFromCmd(){
    bool flags[COUNT] = {0};
    int listLength = propertiesList.length();

    //For each given cmdline argument
    for(int i = 0; i < listLength; ++i){ //QMap emulation
        QString key = propertiesList.at(i).split(ST::EQUAL_SIGN).at(0);
        QString value = propertiesList.at(i).split(ST::EQUAL_SIGN).at(1);

        //Detect command type and try to set corresponding variable
        if(QString::compare(key, ST::OUTPUT_KEY, Qt::CaseInsensitive) == 0){
            if(setOutputDirLocation(value)){ //Load from cmd
                flags[OUTPUT_ENUM] = true;
            }else{
                Console::print(ST::WRONG_OUTPUT_MSG);
                return false;
            }
        }
        if(QString::compare(key, ST::LANGUAGE_KEY, Qt::CaseInsensitive) == 0){
            if(setLanguage(value)){
                flags[LANGUAGE_ENUM] = true;
            }else{
                Console::print(ST::WRONG_LANGUAGE_MSG);
                return false;
            }
        }
        if(QString::compare(key, ST::CONFIG_KEY, Qt::CaseInsensitive) == 0){
            if(setConfigFileLocation(value)){
                flags[CONFIG_ENUM] = true;
            }else{
                Console::print(ST::WRONG_CONFIG_MSG);
                return false;
            }
        }
        if(QString::compare(key, ST::INPUT_KEY, Qt::CaseInsensitive) == 0){
            if(setInputFileLocation(value)){
                flags[INPUT_ENUM] = true;
            }else{
                Console::print(ST::WRONG_INPUT_MSG);
                return false;
            }
        }
        if(QString::compare(key, ST::LOG_KEY, Qt::CaseInsensitive) == 0){
            if(setLogFileLocation(value)){
                flags[CONFIG_ENUM] = true;
            }else{
                Console::print(ST::WRONG_LOG_MSG);
                return false;
            }
        }
    }

    //For uninitialized setting variables
    for(int i = 0; i < COUNT; ++i){
        if(flags[i] == false){
            switch (static_cast<Keys>(i)) {
            case OUTPUT_ENUM:
                if(!setOutputDirLocation(defaultOutputVal)){
                    Console::print(ST::WRONG_DEFAULT_MSG);
                    exit(0);
                }
                break;
            case LANGUAGE_ENUM:
                if(!setLanguage(defaultLanguageVal)){
                    Console::print(ST::WRONG_DEFAULT_MSG);
                    exit(0);
                }
                break;
            case CONFIG_ENUM:
                setConfigFileLocation(defaultConfigVal);
                break;
            case INPUT_ENUM:
                    source = defaultInputVal;
                break;
            case LOG_ENUM:
                if(!setLogFileLocation(defaultLogVal)){
                    Console::print(ST::WRONG_DEFAULT_MSG);
                    exit(0);
                }
                break;
            default:
                break;
            }
        }
    }
    return true;
}


/**
 * @brief AppSettings::loadSettingsFromDefaults Loads and verifies default generic settings
 * @return true if settings are correct, false otherwise
 */
bool AppSettings::loadSettingsFromDefaults(){
    for(int i = 0; i < COUNT; ++i){
        switch (static_cast<Keys>(i)) {
        case OUTPUT_ENUM:
            if(!setOutputDirLocation(defaultOutputVal)){
                Console::print(ST::WRONG_DEFAULT_MSG);
                exit(0);
            }
            break;
        case LANGUAGE_ENUM:
            if(!setLanguage(defaultLanguageVal)){
                Console::print(ST::WRONG_DEFAULT_MSG);
                exit(0);
            }
            break;
        case CONFIG_ENUM:
            createDefaultConfigFile();
            break;
        case INPUT_ENUM:
                source = defaultInputVal;
            break;
        case LOG_ENUM:
            break;
            if(!setLogFileLocation(defaultLogVal)){
                Console::print(ST::WRONG_DEFAULT_MSG);
                exit(0);
            }
        default:
            break;
        }
    }
    return true;
}

/**
 * @brief AppSettings::createDefaultConfigFile Create file if does not exist.
 */
void AppSettings::createDefaultConfigFile(){
    QFile file(defaultConfigVal);
    if(!file.exists()){
        file.open(QIODevice::WriteOnly);
        file.close();
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
 * @brief AppSettings::setOutputDirLocation Function checks if output dir exists and if is writable
 * @param location path to output dir
 * @return true output dir exist and is writable, false output dir does not exist or is not writable
 */
bool AppSettings::setOutputDirLocation(QString &location){
    QDir dir = QDir(location);
    QFileInfo info(location);

    if(dir.exists() && info.isDir() && info.isWritable()){
        output = dir;
    }else{
        return false;
    }
    return true;
}


/**
 * @brief AppSettings::setLanguage Function check if langue parameter is valid
 * @param lang language abbreviation
 * @return true language argument is valid, false language argument is not valid
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
 * @brief AppSettings::setConfigFileLocation Checks if configuration file exists
 * @param location path to configuration file
 * @return true when file exist and is readable, false if file does not exist or is not readable
 */
bool AppSettings::setConfigFileLocation(QString &location){
    QFile cfg(location);
    QFileInfo info(location);
    if(cfg.exists() && info.isReadable()){
        config = location;
    }else{
        return false;
    }
    return true;
}


/**
 * @brief AppSettings::setInputFileLocation Check if specified input file exists and it size is not equal to 0
 * @param location path to input file
 * @return true if file exists, has size >0 and is readable, false otherwise
 */
bool AppSettings::setInputFileLocation(QString &location){
    if(location.length() == 0){
        return true;
    }

    QFile src(location);
    QFileInfo info(location);

    if(((info.isFile()) && src.exists()) && ((src.size() != 0) && (info.isReadable()))){
        source = location;
    }else{
        return false;
    }
    return true;
}


/**
 * @brief AppSettings::setLogFileLocation Check if path to log file is valid and is writable
 * @param location path to log file
 * @return true if file exist and is writable, false when could not be created or is not writable
 */
bool AppSettings::setLogFileLocation(QString &location){
    QFile file(location);
    if(!file.exists()){
        file.open(QIODevice::WriteOnly);
        file.close();
    }

    QFileInfo info(location);
    if(info.isFile() && info.isWritable()){
        log = location;
    }else{
        return false;
    }
    return true;
}
