#ifndef CONSOLE_H
#define CONSOLE_H

#include <QString>
#include <QTextStream>

class Console
{
private:
    //Constructor
    Console();

public:
    //Static methods
    static void print(const QString &txt);

private:
    //Static vars
    static QTextStream stream;

};

#endif // CONSOLE_H
