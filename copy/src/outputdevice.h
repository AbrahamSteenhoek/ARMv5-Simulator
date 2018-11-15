#ifndef OUTPUTDEVICE_H
#define OUTPUTDEVICE_H

#include <QObject>

class OutputDevice : public QObject
{
    Q_OBJECT

    char outputChar;

public:
    explicit OutputDevice(QObject *parent = nullptr);

    void writeCharToConsole(char c);

    QChar getChar() { return outputChar; }

signals:
    void writeCharSignal();

public slots:

};

#endif // OUTPUTDEVICE_H
