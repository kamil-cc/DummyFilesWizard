#include "dummywizard.h"
#include <QApplication>

/**
 * @brief main Entry point.
 * @param argc Counter for arguments.
 * @param argv Input arguments in *char format.
 * @return 0 on clean exit.
 */
int main(int argc, char *argv[]){
    int _argc;
    char **_argv;
    DummyWizard::initRuntimeArgs(argc, argv, &_argc, &_argv);

    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    QApplication app(_argc, _argv);

    DummyWizard::enableTranslator(app);
    DummyWizard wizard;
    wizard.show();

    return app.exec();
}
