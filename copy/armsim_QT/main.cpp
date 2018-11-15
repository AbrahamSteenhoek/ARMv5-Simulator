/*----------------------------------------------------------------------------/
 * Abraham Steenhoek | class: CPS310 | login: astee529 | BJUID: 160520
 *
 * main.cpp
 *  Contains a method to run unit tests, a message handler to control logging output
 *  Main method opens an ELF file given from command line arguments loads the contents of the file into simulated RAM
 * --------------------------------------------------------------------------*/

#include <QApplication>
#include <iostream>
#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QTextStream>
#include <QDebug>
#include <QString>
#include <QStringList>
#include <QtGlobal>
#include <QtMessageHandler>
#include "armsim.h"
#include "options.h"
#include "elf.h"
#include "memory.h"
#include "loader.h"
#include "testloader.h"
#include "testram.h"
#include "testcpu.h"
#include "testcomputer.h"
#include "testinstruction.h"
#include "testbarrelshifter.h"
#include "testoperand2.h"
//#include "messagehandler.h"

using namespace std;

/*
 * unitTests()
 *  - creates instances of testRAM and testLoader classes that run unit tests on their respective classes
 */
void unitTests(Options *opts) {

    //TODO: make each call to test class not a pointer, and just have each class have a static test method
    qInfo() << "Begin unit tests" << endl;
    testRAM::runTests();
    testLoader::runTests();
    testCPU::runTests();
    testComputer::runTests(opts);
    testInstruction::runTests();
    testBarrelShifter::runTests();
    testOperand2::runTests();
    qInfo() << "End unit tests" << endl;
}

//TODO fix messagehandler
/*
 * myMessageOutput()
 *  - redirects default qt output methods to specified file streams to allow for redirection of logging output
 */
void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &Qmsg)
{
    QByteArray msg = Qmsg.toLocal8Bit();

    switch (type) {
    case QtDebugMsg:
        fprintf(stderr, "Debug: %s\n", msg.constData());
        break;
    case QtInfoMsg:
        fprintf(stdout, "%s\n", msg.constData());
        break;
    case QtWarningMsg:
        fprintf(stderr, "Warning: (%s:%u, %s)\n", context.file, context.line, context.function);
        break;
    case QtCriticalMsg:
        fprintf(stderr, "Critical: %s\n", msg.constData());
        break;
    case QtFatalMsg:
        fprintf(stderr, "Fatal: %s\n", msg.constData());
        abort();
    }
}

int main(int argc, char *argv[])
{
    // to change the output for the logging files, simply use MessageHandler::setOutput(FILE* strm)
    qInstallMessageHandler(myMessageOutput);

    // Application handles the model side of the GUI
    QApplication a(argc, argv);
    // parse command line args
    Options* opts = new Options(&a);
    // w handles the view side of the GUI
    ArmSim w(opts);

    // run unit tests
    if(opts->test()) {
        unitTests(opts);
        exit(0);
    }
    w.show();

    return a.exec();
}
