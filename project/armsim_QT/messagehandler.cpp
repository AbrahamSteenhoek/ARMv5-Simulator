/*----------------------------------------------------------------------------/
 * Abraham Steenhoek | class: CPS310 | login: astee529 | BJUID: 160520
 *
 * messagehandler.cpp
 *  - contains the definitions for the MessageHandler class and all of its methods
 *  - note: messagehandler is a singleton class so that its output stream can be accessed anywhere
 * --------------------------------------------------------------------------*/

#include "messagehandler.h"

MessageHandler* MessageHandler::msgHandler = nullptr;

MessageHandler::MessageHandler()
{
    // stderr by default
    output = stderr;
}

/*
 * Method: getInstance
 *  - gives user access to MessageHandler instance since constructor is private
 */
MessageHandler *MessageHandler::getInstance()
{
    if(msgHandler == nullptr)
        return new MessageHandler();
    return msgHandler;
}
