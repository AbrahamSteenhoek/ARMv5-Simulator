#include "terminaltextbrowser.h"

TerminalTextBrowser::TerminalTextBrowser(QWidget *parent)
{

}

TerminalTextBrowser::TerminalTextBrowser()
{

}

void TerminalTextBrowser::keyPressEvent(QKeyEvent *event)
{
    inputChar = event->text().toStdString()[0];
    emit signal_keyPressed();
}
