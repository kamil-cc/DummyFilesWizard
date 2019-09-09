#include "cmdparser.h"

#include "console/console.h"
#include "text/statictext.h"

//Constructor
CmdParser::CmdParser(){
}

//Destructor
CmdParser::~CmdParser(){
}

//Methods
bool CmdParser::parseConfigCmd(QStringList keysToConsume,
                               QStringList valuesToConsume){
    int len = keysToConsume.length();
    if(len != valuesToConsume.length() || len == 0){
        return false;
    }

    for(int i = 0; i < len; ++i){
        QString key = keysToConsume.at(i).trimmed();
        QString value = valuesToConsume.at(i).trimmed();

        if(key.startsWith(ST::FILES_LOCATION_KEY, Qt::CaseInsensitive)){
            if(value.length() == 0 || !setOutputLocation(value)){
                Console::print(ST::WRONG_OUTPUT_MSG);
            }
        }else if(key.startsWith(ST::LANG_KEY, Qt::CaseInsensitive)){
            if(value.length() == 0 || !setLanguage(value)){
                Console::print(ST::WRONG_LANGUAGE_MSG);
            }
        }else if(key.startsWith(ST::TEXT_LOCATION_KEY, Qt::CaseInsensitive)){
            if(value.length() == 0 || !setInputLocation(value)){
                Console::print(ST::WRONG_INPUT_MSG);
            }
        }else if(key.startsWith(ST::LOG_LOCATION_KEY, Qt::CaseInsensitive)){
            if(value.length() == 0 || !setLogLocation(value)){
                Console::print(ST::WRONG_LOG_MSG);
            }
        }
    }
    return validate();
}
