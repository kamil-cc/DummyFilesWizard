#ifndef CMDPARSER_H
#define CMDPARSER_H

#include <QString>
#include <QStringList>

#include "settingsbase.h"


class CmdParser: public SettingsBase
{
    Q_OBJECT

public:
    //Constructor
    CmdParser();

    //Destructor
    ~CmdParser();

    //Methods
    bool parseConfigCmd(QStringList keysToConsume, QStringList valuesToConsume);
};

#endif // CMDPARSER_H
