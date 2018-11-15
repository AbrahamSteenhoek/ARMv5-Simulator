#ifndef ARMSIM_H
#define ARMSIM_H

#include <QMainWindow>

namespace Ui {
class ArmSim;
}

class ArmSim : public QMainWindow
{
    Q_OBJECT

public:
    explicit ArmSim(QWidget *parent = nullptr);
    ~ArmSim();

private:
    Ui::ArmSim *ui;
};

#endif // ARMSIM_H
