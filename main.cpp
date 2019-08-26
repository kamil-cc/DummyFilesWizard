#include <QApplication>
#include "dummywizard.h"
#include "settings/appsettings.h"


/**
 * @brief main Entry point.
 * @param argc Counter for arguments.
 * @param argv Input arguments in *char format.
 * @return 0 on clean exit.
 */
int main(int argc, char *argv[]){
    int _argc;
    char **_argv;
    AppSettings settings(argc, argv, &_argc, &_argv);

    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    QApplication app(_argc, _argv);

    DummyWizard wizard(app, settings);
    wizard.show();

    return app.exec();
}
