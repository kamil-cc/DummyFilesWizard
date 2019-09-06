#ifndef FILEPARSER_H
#define FILEPARSER_H


#include "console/console.h"
#include "text/statictext.h"
#include "settingsbase.h"


class FileParser : public SettingsBase
{
    Q_OBJECT
public:
    FileParser();
    bool parseConfigFile(QString filePath);
};

#endif // FILEPARSER_H
