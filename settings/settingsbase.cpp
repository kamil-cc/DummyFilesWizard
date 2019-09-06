#include "settingsbase.h"


SettingsBase::SettingsBase() : valid(false),
    language(""), config(""), input(""), log(""){

}


SettingsBase::~SettingsBase(){

}


bool SettingsBase::validate(){
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


bool SettingsBase::checkFileIsReadable(QString filePath){
    QFileInfo fileInfo(filePath);
    if(fileInfo.exists() &&
            (fileInfo.isFile() && fileInfo.isReadable())){
        return true;
    }
    return false;
}


bool SettingsBase::setOutputLocation(QString localOutput){
    QFileInfo info(localOutput);

    if(!info.exists()){
        QDir dir(localOutput);
        dir.mkdir(".");
    }

    QFileInfo infoCreated(localOutput);
    if(infoCreated.exists() &&
            (infoCreated.isDir() && infoCreated.isWritable())){
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

    return checkFileIsReadable(localLog);
}


void SettingsBase::createFile(QString path){
    QFile file(path);
    file.open(QIODevice::WriteOnly);
    file.close();
}
