#include "armsim.h"
#include "ui_armsim.h"

ArmSim::ArmSim(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ArmSim)
{
    ui->setupUi(this);
}

ArmSim::~ArmSim()
{
    delete ui;
}
