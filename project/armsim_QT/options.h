/*----------------------------------------------------------------------------/
 * Abraham Steenhoek | class: CPS310 | login: astee529 | BJUID: 160520
 *
 * options.h
 *  - contains the declarations for the Options class and all of its methods
 * --------------------------------------------------------------------------*/


#ifndef OPTIONS_H
#define OPTIONS_H

#include <iostream>
#include <fstream>
#include <QApplication>
#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QTextStream>
#include <QDebug>
#include <QString>
#include <QStringList>
#include <QDir>
#include <stdio.h>

using namespace std;

/*
 * Class: Options
 *  - Uses the QCommandLineParser framework to parse command line arguments and store them in a QCommandLineParser object
 */
class Options
{
    // contains all of the arguments from the command line
    QCommandLineParser parser;
public:
    Options (QApplication *app);

    // allows user to access an instance of the Options class like a C++ map structure
    QString operator[](const char* arg);

    // Method: test - returns a bool that represents the --test option flag
    bool test() { return parser.isSet("test"); }
    bool exec() { return load() && parser.isSet("exec"); }
    bool load() { return parser.isSet("load"); }
    bool traceall() { return parser.isSet("traceall"); }
    bool log() { return parser.isSet("log"); }
};

#endif // OPTIONS_H
