#include "console.h"

QTextStream Console::stream(stdout);

Console::Console()
{
}


void Console::print(const QString &txt){
    stream << txt << "\n";
}
