#include "dummywizard.h"
#include "ui_dummywizard.h"

#include <QDateTime>
#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QSettings>
#include <QStringList>

#include "text/statictext.h"
#include "console/console.h"


//Shortcut
typedef StaticText ST;


//Default filenames
#define CFG_FILENAME "cfg.ini"
#define LOG_FILENAME ".log"


//Initialize static vars
QDir DummyWizard::destination(QDir::currentPath());
QString DummyWizard::language("PL");
QString DummyWizard::config(QDir::currentPath() +
                            QString(QDir::separator()) + CFG_FILENAME);
QString DummyWizard::source("");
QString DummyWizard::log(QDir::currentPath() + QString(QDir::separator()) +
                         QDateTime::currentDateTime().toString() + LOG_FILENAME);
bool DummyWizard::useCmdArgs(false);
bool DummyWizard::configFromCmd(false);


/**
 * @brief DummyWizard::DummyWizard Constructs main object.
 * @param parent parent QWidget
 */
DummyWizard::DummyWizard(QWidget *parent) : QWizard(parent){
    //TODO Not implemented yet!
    mouseHoover = false;

    QFile file(config);
    if(file.exists() && (!useCmdArgs && )){ //
        //Have a config file. Try to load key-value pairs
        QSettings settings(config, QSettings::IniFormat);
        QString outputCfg = settings.value("output", "").toString();
        QString languageCfg = settings.value("language", "").toString();
        QString sourceCfg = settings.value("source", "").toString();
        QString logCfg = settings.value("log", "").toString();
    }else if(){
        //Do not have config.cfg. Create new.
        file.open(QIODevice::WriteOnly);
        file.close();
    }

    //Insanity checks. All arguments set to default
    if((!useCmdArgs) && (!configFromCmd)){
        if(!defaultCheck()){
            //TODO EXIT
        }
    }

    //wizard.addPage(createConclusionPage()); //TODO

    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setWindowTitle(tr("Dummy Files Wizard")); //TODO
}


/**
 * @brief DummyWizard::~DummyWizard Destructs main object.
 */
DummyWizard::~DummyWizard(){
}


/**
 * @brief DummyWizard::enableTranslator Function create translator object if QT_NO_TRANSLATION was not defined
 * @param app reference to main QApplication object
 */
void DummyWizard::enableTranslator(QApplication &app){
    (void)app; //Silence warning
#ifndef QT_NO_TRANSLATION
    //If translation is enabled
    QString translatorFileName = QLatin1String("qt_");
    translatorFileName += QLocale::system().name();
    QTranslator *translator = new QTranslator(&app);
    if (translator->load(translatorFileName,
                         QLibraryInfo::location(QLibraryInfo::TranslationsPath))){
        app.installTranslator(translator);
    }
#endif
}


/**
 * @brief DummyWizard::initRuntimeArgs Parse command line arguments.
 * @param inArgc counter received from main function
 * @param inArgv arguments received from main function
 * @param outArgc counter passing to QApplication constructor
 * @param outArgv arguments passing to QApplication constructor
 */
void DummyWizard::initRuntimeArgs(int inArgc, char *inArgv[], int *outArgc, char ***outArgv){
    QStringList list;

    for(int i = 0; i < inArgc; ++i){ //For each command line argument
        QString a(inArgv[i]);
        QString arg = a.trimmed();

        if(configFromCmd){
            break;
        }

        parse(arg, list);
    }

    int listLength = list.length();
    char **argv = new char*[listLength];

    for(int i = 0; i < listLength; ++i){
        const char *string = list.at(i).toUtf8().constData();
        int len = strlen(string);
        argv[i] = new char[len + 1]; //Terminating character \0
        strncpy(argv[i], string, len + 1);
    }

    //No delete statement because: https://doc.qt.io/qt-5/qapplication.html#QApplication
    //"argc and argv might be changed as Qt removes command line arguments that it recognizes"
    *outArgc = listLength;
    *outArgv = argv;
}


/**
 * @brief DummyWizard::parse Helper function for initRuntimeArgs
 * @param arg single argument
 * @param list transfer commands to QApplication
 */
void DummyWizard::parse(QString arg, QStringList &list){
    QString empty("");
    if(arg.startsWith(ST::HELP_CMD, Qt::CaseInsensitive)){
        displayHelp();
    }else if(arg.startsWith(ST::FILES_LOCATION_CMD, Qt::CaseInsensitive)){
        if(!setFilesLocation(arg.replace(ST::FILES_LOCATION_CMD,
                                         empty, Qt::CaseInsensitive))){
            Console::print(ST::WRONG_OUTPUT_MSG);
            exit(0);
        }
        useCmdArgs = true;
    }else if(arg.startsWith(ST::LANG_CMD, Qt::CaseInsensitive)){
        if(!setLanguage(arg.replace(ST::LANG_CMD,
                                 empty, Qt::CaseInsensitive))){
            Console::print(ST::WRONG_LANGUAGE_MSG);
            exit(0);
        }
        useCmdArgs = true;
    }else if(arg.startsWith(ST::CONFIG_LOCATION_CMD, Qt::CaseInsensitive)){
        if(!setConfigLocation(arg.replace(ST::CONFIG_LOCATION_CMD,
                                       empty, Qt::CaseInsensitive))){
            Console::print(ST::WRONG_CONFIG_MSG);
            exit(0);
        }
        configFromCmd = true;
        useCmdArgs = false;
    }else if(arg.startsWith(ST::TEXT_LOCATION_CMD, Qt::CaseInsensitive)){
        if(!setTextFileLocation(arg.replace(ST::TEXT_LOCATION_CMD,
                                         empty, Qt::CaseInsensitive))){
            Console::print(ST::WRONG_INPUT_MSG);
            exit(0);
        }
        useCmdArgs = true;
    }else if(arg.startsWith(ST::LOG_LOCATION_CMD, Qt::CaseInsensitive)){
        if(!setLogLocation(arg.replace(ST::LOG_LOCATION_CMD,
                                    empty, Qt::CaseInsensitive))){
            Console::print(ST::WRONG_LOG_MSG);
            exit(0);
        }
        useCmdArgs = true;
    }else{
        list << arg;
    }
}

/**
 * @brief DummyWizard::displayHelp Displays help and stops program before calling constructor QApplication()
 */
void DummyWizard::displayHelp(){
    Console::print(ST::HELP_MSG);
    exit(0);
}


/**
 * @brief DummyWizard::setFilesLocation Function checks if output dir exists and if is writable
 * @param location path to output dir
 * @return
 */
bool DummyWizard::setFilesLocation(QString &location){
    QDir dir = QDir(location);
    QFileInfo info(location);

    if(dir.exists() && info.isDir() && info.isWritable()){
        destination = dir;
    }else{
        return false;
    }
    return true;
}


/**
 * @brief DummyWizard::setLanguage Function check if langue parameter is valid
 * @param lang language abbreviation
 * @return
 */
bool DummyWizard::setLanguage(QString &lang){
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
 * @brief DummyWizard::setConfigLocation Checks if configuration file exists
 * @param location path to configuration file
 * @return
 */
bool DummyWizard::setConfigLocation(QString &location){
    QFile cfg(location);
    if(cfg.exists()){
        config = location;
    }else{
        return false;
    }
    return true;
}


/**
 * @brief DummyWizard::setTextFileLocation Check if specified input file exists and it size is not equal to 0
 * @param location
 * @return
 */
bool DummyWizard::setTextFileLocation(QString &location){
    QFile src(location);
    if(src.exists() && (src.size() != 0)){
        source = location;
    }else{
        return false;
    }
    return true;
}


/**
 * @brief DummyWizard::setLogLocation Check if path to log file is valid and is writable
 * @param location path to log file
 * @return
 */
bool DummyWizard::setLogLocation(QString &location){
    QFile file(location);
    QFileInfo info(location);

    if(!file.exists()){
        file.open(QIODevice::WriteOnly);
        file.close();
    }
    if(info.isFile() && info.isWritable()){
        log = location;
    }else{
        return false;
    }
    return true;
}


/**
 * @brief DummyWizard::mousePressEvent Drag and drop functionality
 * @param event mouse left button clicked
 */
void DummyWizard::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        mouseX = event->x();
        mouseY = event->y();
    }
}


/**
 * @brief DummyWizard::mouseMoveEvent Drag and drop functionality
 * @param event mouse move
 */
void DummyWizard::mouseMoveEvent(QMouseEvent *event){
    if(!mouseHoover){ //TODO Not implemented yet!
        move(event->globalX() - mouseX, event->globalY() - mouseY);
    }
}


void defaultCheck(){
    QFileInfo info(destination.absolutePath());
    if(!info.isWritable()){
        QApplication::quit();
    }

    QFile file(config);
    if(!file.exists()){
        file.open(QIODevice::WriteOnly);
        file.close();
    }

    QFileInfo inf(config);
    if(!inf.isWritable()){
        QApplication::quit();
    }

    QFile file2(log);
    if(!file2.exists()){
        file2.open(QIODevice::WriteOnly);
        file2.close();
    }

    QFileInfo inf2(log);
    if(!inf2.isWritable()){
        QApplication::quit();
    }
}
