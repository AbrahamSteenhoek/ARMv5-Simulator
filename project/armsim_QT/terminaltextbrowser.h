#ifndef TERMINALTEXTBROWSER_H
#define TERMINALTEXTBROWSER_H

#include <QObject>
#include <QWidget>
#include <QTextBrowser>
#include <QKeyEvent>
#include <iostream>

class TerminalTextBrowser : public QTextBrowser
{
    Q_OBJECT

    unsigned char inputChar;
public:
    explicit TerminalTextBrowser(QWidget *parent = nullptr);
    TerminalTextBrowser();
    unsigned char getChar() { return inputChar; }
signals:
    void signal_keyPressed();
private:
    void keyPressEvent(QKeyEvent *event);

};

#endif // TERMINALTEXTBROWSER_H
