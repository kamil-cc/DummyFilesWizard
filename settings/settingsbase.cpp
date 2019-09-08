#include "settingsbase.h"


const QString SettingsBase::CFG_FILENAME = "cfg.ini";
const QString SettingsBase::LOG_FILENAME = ".log";


SettingsBase::SettingsBase() : valid(true),
    output(), language(), config(), input(), log(),
    DEFAULT_OUTPUT(QDir::currentPath()),
    DEFAULT_LANGUAGE(ST::PL_LANG),
    DEFAULT_CONFIG(QDir::currentPath()
                   + QDir::separator() + CFG_FILENAME),
    DEFAULT_INPUT(),
    DEFAULT_LOG(QDir::currentPath() + QDir::separator()
                + QDateTime::currentDateTime().toString(Qt::ISODate)
                + LOG_FILENAME){
}


SettingsBase::~SettingsBase(){
}


bool SettingsBase::validate(){
    if(output.isNull()){
        setOutputLocation(DEFAULT_OUTPUT);
    }
    if(output.isNull()){
        valid &= false;
    }

    if(language.isNull()){
        setLanguage(DEFAULT_LANGUAGE);
    }
    if(language.isNull()){
        valid &= false;
    }

    if(config.isNull()){
        setConfigLocation(DEFAULT_CONFIG);
    }
    if(config.isNull()){
        valid &= false;
    }

    if(input.isNull()){
        setInputLocation(DEFAULT_INPUT);
    }
    if(input.isNull()){
        //valid &= false;
    }

    if(log.isNull()){
        setLogLocation(DEFAULT_LOG);
    }
    if(log.isNull()){
        valid &= false;
    }

    return valid;
}


QString SettingsBase::getOutputLocation(){
    return output;
}


QString SettingsBase::getLanguage(){
    return language;
}


QString SettingsBase::getConfig(){
    return config;
}


QString SettingsBase::getInputLocation(){
    return input;
}


QString SettingsBase::getLogLocation(){
    return log;
}


bool SettingsBase::setOutputLocation(QString localOutput){
    createDir(localOutput);

    if(checkDirectoryIsWritable(localOutput)){
        output = localOutput;
        return true;
    }

    return false;
}


bool SettingsBase::setLanguage(QString localLanguage){
    bool result = false;

    if(QString::compare(localLanguage, ST::PL_LANG, Qt::CaseInsensitive)){
        result = true;
    }

    if(QString::compare(localLanguage, ST::EN_LANG, Qt::CaseInsensitive)){
        result = true;
    }

    if(result){
        language = localLanguage;
    }

    return result;
}


bool SettingsBase::setInputLocation(QString localInput){
    if(checkFileIsReadable(localInput)){
        QFile file(localInput);
        if(file.size() > 0){
            input = localInput;
            return true;
        }
    }
    return false;
}


bool SettingsBase::setLogLocation(QString localLog){
    bool readable = checkFileIsReadable(localLog);
    if(!readable){
        createFile(localLog);
    }
    return checkFileIsWritable(localLog);
}


bool SettingsBase::setConfigLocation(QString configLocation){
    return setLogLocation(configLocation);
}


bool SettingsBase::checkFileIsReadable(QString filePath){
    QFileInfo fileInfo(filePath);
    if(fileInfo.exists() &&
            (fileInfo.isFile() && fileInfo.isReadable())){
        return true;
    }
    return false;
}


bool SettingsBase::checkDirectoryIsWritable(QString dirPath){
    QFileInfo info(dirPath);
    if(info.exists() &&
            (info.isDir() && info.isWritable())){
        return true;
    }
    return false;
}


bool SettingsBase::checkFileIsWritable(QString filePath){
    QFileInfo info(filePath);
    if(info.exists() &&
            (info.isFile() && info.isWritable())){
        return true;
    }
    return false;
}


void SettingsBase::createFile(QString path){
    QFile file(path);
    file.open(QIODevice::WriteOnly);
    file.close();
}


void SettingsBase::createDir(QString localOutput){
    QFileInfo info(localOutput);
    if(!info.exists()){
        QDir dir(localOutput);
        dir.mkdir(".");
    }
}

