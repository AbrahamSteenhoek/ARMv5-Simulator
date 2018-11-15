#include "outputdevice.h"

OutputDevice::OutputDevice(QObject *parent) : QObject(parent)
{

}

void OutputDevice::writeCharToConsole(char c)
{
    outputChar = c;
    emit writeCharSignal();
}
