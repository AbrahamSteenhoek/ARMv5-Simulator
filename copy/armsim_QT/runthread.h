/*----------------------------------------------------------------------------/
 * Abraham Steenhoek | class: CPS310 | login: astee529 | BJUID: 160520
 *
 * runthread.h
 *  - contains the declarations of the constructor and all methods for the runThread class
 * --------------------------------------------------------------------------*/
#pragma once
#include <QThread>
#include "computer.h"
#ifndef RUNTHREAD_H
#define RUNTHREAD_H


class RunThread : public QThread
{
    Computer *computer;
public:
    RunThread(Computer *com);

    void run();


};

#endif // RUNTHREAD_H
