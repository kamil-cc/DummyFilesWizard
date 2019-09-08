#include "fileparser.h"


FileParser::FileParser(){
}


bool FileParser::parseConfigFile(QString filePath){
    if(!checkFileIsReadable(filePath)){
        Console::print(ST::WRONG_CONFIG_FILE_MSG);
        valid = false;
        return valid;
    }

    QSettings settings(filePath, QSettings::IniFormat);

    QString localOutput = settings.value(ST::FILES_LOCATION_KEY, "").toString();
    QString localLanguage = settings.value(ST::LANG_KEY, "").toString();
    QString localInput = settings.value(ST::TEXT_LOCATION_KEY, "").toString();
    QString localLog = settings.value(ST::LOG_LOCATION_KEY, "").toString();

    localOutput = localOutput.trimmed();
    localLanguage = localLanguage.trimmed();
    localInput = localInput.trimmed();
    localLog = localLog.trimmed();

    if(localOutput.length() == 0){
        valid = false;
    }

    if(localLanguage.length() == 0){
        valid = false;
    }

    if(localInput.length() == 0){
        //valid = false;
    }

    if(localLog.length() == 0){
        valid = false;
    }

    if(!valid){
        Console::print(ST::WRONG_CONFIG_FILE_MSG);
        return valid;
    }

    valid &= setOutputLocation(localOutput);
    valid &= setLanguage(localLanguage);
    /*valid &=*/ setInputLocation(localInput);
    valid &= setLogLocation(localLog);

    if(!valid){
        Console::print(ST::WRONG_CONFIG_FILE_MSG);
    }

    return valid;
}

