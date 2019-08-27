#include "console.h"

QTextStream Console::stream(stdout);

/**
 * @brief Console::Console Private constructor. We don't need to create Console object.
 */
Console::Console()
{
}

/**
 * @brief Console::print Print any QString to stdout (console).
 * @param txt text to print
 */
void Console::print(const QString &txt){
    stream << txt << "\n";
}
