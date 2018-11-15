/*----------------------------------------------------------------------------/
 * Abraham Steenhoek | class: CPS310 | login: astee529 | BJUID: 160520
 *
 * options.cpp
 *  - contains the definitions for the Options class and all of its methods
 * --------------------------------------------------------------------------*/


#include "options.h"


Options::Options(QApplication *app) {

    parser.addHelpOption();
    parser.addVersionOption();

    parser.addOptions({
        // --test
        {"test",
            QCoreApplication::translate("main", "run unit tests and then exit")},
        // --load [elf-file]
        {"load",
            QCoreApplication::translate("main", "load elf-file into simulated RAM"),
            QCoreApplication::translate("main", "elf file")},
        // --mem [memsize]
        {"mem",
            QCoreApplication::translate("main", "specify size of simulated RAM"),
            QCoreApplication::translate("main", "mem size")},
        {"exec",
            QCoreApplication::translate("main", "when set with --load, load file and invoke Start function")},
        {"traceall",
            QCoreApplication::translate("main", "when set, turn exception tracing on.  Otherwise only trace when in SYS mode")},
        {"log",
            QCoreApplication::translate("main", "when set, log the progress of the loader as it is loading a file")}
        }

        );
    parser.process(*app);

    // ELF file is now loaded using the GUI
    /*
    // there must be a --load option when running armsim.exe
    if (!parser.isSet("load") && !parser.isSet("test")) {
        cerr << "usage: armsim.exe --load elf_file [--mem n_bytes] [--test]" << endl;
        exit(1);
    }
    */
}

/*
 * Overloaded operator []
 *  - allows user to access options class like a C++ map structure or a Python dictionary
 */
QString Options::operator[](const char* arg_char) {
    QString arg = QString(arg_char);
    if(parser.isSet(arg)) {
        return parser.value(arg);
    }
    else {
        return nullptr;
    }
}
