#ifndef STATICTEXT_H
#define STATICTEXT_H

#include <QString>

class StaticText
{
private:
    StaticText();

public:
    //Static constants
    static const QString HELP_CMD;
    static const QString FILES_LOCATION_CMD;
    static const QString LANG_CMD;
    static const QString CONFIG_LOCATION_CMD;
    static const QString TEXT_LOCATION_CMD;
    static const QString LOG_LOCATION_CMD;

    static const QString HELP_MSG;
    static const QString WRONG_OUTPUT_MSG;
    static const QString WRONG_LANGUAGE_MSG;
    static const QString WRONG_CONFIG_MSG;
    static const QString WRONG_INPUT_MSG;
    static const QString WRONG_LOG_MSG;

    static const QString PL_LANG;
    static const QString EN_LANG;
};

#endif // STATICTEXT_H
