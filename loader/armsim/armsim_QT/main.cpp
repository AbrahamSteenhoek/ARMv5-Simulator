#include "armsim.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ArmSim w;
    w.show();

    return a.exec();
}
