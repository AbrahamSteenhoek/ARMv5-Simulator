/*----------------------------------------------------------------------------/
 * Abraham Steenhoek | class: CPS310 | login: astee529 | BJUID: 160520
 *
 * armsim.h
 *  - handles the VIEW side of the GUI
 * --------------------------------------------------------------------------*/

#include <QMainWindow>
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include <QFileInfo>
#include <QStandardItem>
#include <QString>
#include <QMessageBox>
#include <QListView>
#include <QTableView>
#include <QColor>
#include <fstream>
#include <QScrollBar>
#include <QInputDialog>
#include <QKeyEvent>
#include "computer.h"
#include "loader.h"
#include "runthread.h"
#include "outputdevice.h"

#ifndef ARMSIM_H
#define ARMSIM_H



namespace Ui {
class ArmSim;
}

class ArmSim : public QMainWindow
{
    Q_OBJECT

    Computer* computer;
    RegisterBank* regs;
    Memory* RAM;
    QString filepath;

    QStringList headerLbls;

    Options *opts;

    OutputDevice *outputDevice;

    // flag to indicate if highlighted line in disassembly panel should be PC + 4 or PC
    bool justLoaded;

public:
    explicit ArmSim(QWidget *parent = nullptr);
    explicit ArmSim(Options* opts, QWidget *parent = nullptr);
    void setComputer(Computer* com);
    void loadFile(QString filepath);

    void setupPanels();

    // METHODS TO UPDATE THE DISPLAY
    void updateDisplay();
    // updates the text box that displays the filename
    void updateFilename(QString filename);
    // updates the text box that displays the checksum for the given ELF file
    void updateChecksum(QString checksum);
    // updates the contents of r0-r15
    void updateRegPanel();
    // updates the flags in the CPSR register
    void updateFlagPanel();
    // updates the display of the memory at a certain address
    void updateMemoryPanel();
    // updates the disassembly panel
    void updateDisassemblyPanel();
    QString generateDisassemblyForPanel(uint, uint, RegisterBank *regs, Memory *memory);
    //updates the stack panel
    void updateStackPanel();

    void resetTraceFile();

    ~ArmSim();


private slots:
    void writeCharToConsole();

    void keyPressed();

    void on_pushButton_clicked();

    void on_pushButton_reset_clicked();

    void on_pushButton_step_clicked();

    void on_pushButton_run_clicked();

    // listens for a signal when the thread is finished

    void threadEnded();

    void on_lineEdit_memory_returnPressed();

    void on_pushButton_stop_clicked();

    void on_checkBox_trace_clicked();

    void on_pushButton_add_breakpoint_clicked();

    void on_checkBox_breakpoint_clicked();

private:
    Ui::ArmSim *ui;
};

#endif // ARMSIM_H
