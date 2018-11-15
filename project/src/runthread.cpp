/*----------------------------------------------------------------------------/
 * Abraham Steenhoek | class: CPS310 | login: astee529 | BJUID: 160520
 *
 * runthread.cpp
 *  - contains the definitions of the constructor and all methods for the runThread class
 * --------------------------------------------------------------------------*/

#include "runthread.h"

RunThread::RunThread(Computer *com)
{
    computer = com;
    //com->setRunFlag(true);

}

void RunThread::run()
{
    computer->run();
}
