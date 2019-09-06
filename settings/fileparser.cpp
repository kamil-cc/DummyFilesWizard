#include "fileparser.h"

FileParser::FileParser()
{
}

bool FileParser::parseConfigFile(QString filePath){
    if(!checkFileIsReadable(filePath)){
        return false;
    }

    QSettings settings(filePath, QSettings::IniFormat);

    QString localOutput = settings.value(ST::FILES_LOCATION_KEY, "").toString();
    QString localLanguage = settings.value(ST::LANG_KEY, "").toString();
    QString localInput= settings.value(ST::TEXT_LOCATION_KEY, "").toString();
    QString localLog = settings.value(ST::LOG_LOCATION_KEY, "").toString();

    localOutput = localOutput.trimmed();
    localLanguage = localLanguage.trimmed();
    localInput = localInput.trimmed();
    localLog = localLog.trimmed();

    bool error = false;

    if(localOutput.length() == 0){
        error = true;
    }

    if(localLanguage.length() == 0){
        error = true;
    }

    if(localInput.length() == 0){
        error = true;
    }

    if(localLog.length() == 0){
        error = true;
    }

    if(error){
        Console::print(ST::WRONG_CONFIG_FILE_MSG);
        return error;
    }

    error |= setOutputLocation(localOutput);
    error |= setLanguage(localLanguage);
    error |= setInputLocation(localInput);
    error |= setLogLocation(localLog);

    if(error){
        Console::print(ST::WRONG_CONFIG_FILE_MSG);
    }

    return error;
}

