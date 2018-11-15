/*----------------------------------------------------------------------------/
 * Abraham Steenhoek | class: CPS310 | login: astee529 | BJUID: 160520
 *
 * messagehandler.h
 *  - contains the declarations for the MessageHandler class and all of its methods
 *  - note: messagehandler is a singleton class so that its output stream can be accessed anywhere
 * --------------------------------------------------------------------------*/


#include <iostream>
#include <fstream>
#include <QtGlobal>
#include <QString>

#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

using namespace std;

class MessageHandler
{
    // output stream controls where output functions display their messages
    FILE *output;
    static MessageHandler* msgHandler;
    MessageHandler();
    //void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &Qmsg);
public:
    /*
     * Method: setOutput()
     *  - allows user to change the output stream
     */
    void setOutput(FILE* strm) { output = strm; }

    static MessageHandler* getInstance();

    /*
     * Method: ostrm()
     *  - gives user access to MessageHandler's output stream
     */
    FILE* ostrm() { return output; }

};

#endif // MESSAGEHANDLER_H
