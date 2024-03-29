#include "statictext.h"

const QString StaticText::HELP_CMD = "-help";
const QString StaticText::FILES_LOCATION_CMD = "-output=";
const QString StaticText::LANG_CMD = "-language=";
const QString StaticText::CONFIG_LOCATION_CMD = "-config=";
const QString StaticText::TEXT_LOCATION_CMD = "-text=";
const QString StaticText::LOG_LOCATION_CMD = "-log=";

const QString StaticText::HELP_MSG = "-help\t\t\tDisplay this message.\n"
                               "-output=/some/dir/\tOutput files will be stored in /some/dir/\n"
                               "-language=EN\t\tForce to use specified language. Possible values are: PL and EN.\n"
                               "-config=/some/cfg.ini\tUse settings from cfg.ini file. Other command line options are ignored.\n"
                               "-text=/some/file.txt\tUse file.txt as input for text generator.\n"
                               "-log=/some/file.log\tWrite log to specified file.";

const QString StaticText::WRONG_OUTPUT_MSG = "Error in \'-output=\' option!";
const QString StaticText::WRONG_LANGUAGE_MSG = "Error in \'-language=\' option!";
const QString StaticText::WRONG_CONFIG_MSG = "Error in \'-config=\' option .";
const QString StaticText::WRONG_INPUT_MSG = "Error in \'-text=\' option!";
const QString StaticText::WRONG_LOG_MSG = "Error in \'-log=\' option!";
const QString StaticText::WRONG_DEFAULT_MSG = "Error. Default runtime arguments are not valid.";
const QString StaticText::WRONG_CONFIG_FILE_MSG = "Error. Config file is corrupted.";

const QString StaticText::PL_LANG = "PL";
const QString StaticText::EN_LANG = "EN";

const QString StaticText::FILES_LOCATION_KEY = "output";
const QString StaticText::LANG_KEY = "language";
const QString StaticText::CONFIG_LOCATION_KEY = "config";
const QString StaticText::TEXT_LOCATION_KEY = "text";
const QString StaticText::LOG_LOCATION_KEY = "log";

/**
 * @brief StaticText::StaticText Private constructor. We don't need to create StaticText object.
 */
StaticText::StaticText()
{
}
