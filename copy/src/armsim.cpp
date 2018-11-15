/*----------------------------------------------------------------------------/
 * Abraham Steenhoek | class: CPS310 | login: astee529 | BJUID: 160520
 *
 * armsim.cpp
 *  - Contains the method definitions for armsim.h
 * --------------------------------------------------------------------------*/


#include "armsim.h"
#include "ui_armsim.h"

ArmSim::ArmSim(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ArmSim)
{
    ui->setupUi(this);
}

ArmSim::ArmSim(Options *opts, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ArmSim)
{
    ui->setupUi(this);

    // set up instance OutputDevice that watches the computer
    outputDevice = new OutputDevice();
    connect(outputDevice, SIGNAL(writeCharSignal()), this, SLOT(writeCharToConsole()));

    this->opts = opts;
    Options &_opts = *opts;
    // instantiate computer
    computer = new Computer(opts);
    // assign direct references too RAM & regs for easier access
    regs = computer->registers();
    RAM = computer->memory();
    computer->setTracingStream(new ofstream);
    RAM->setOutputDevice(outputDevice);

    setupPanels();

    // connect signal for key presses
    connect(ui->textBrowser_terminalView, SIGNAL(signal_keyPressed()), this, SLOT(keyPressed()));

    filepath = _opts["load"];
    if(!filepath.isEmpty()) {
        loadFile(_opts["load"]);

        updateDisplay();
        // exec
        if(opts->exec()) {
            // reset the trace file
            resetTraceFile();
            on_pushButton_run_clicked();
        }
    }
}

ArmSim::~ArmSim()
{
    delete ui;
}

void ArmSim::writeCharToConsole()
{
    ui->textBrowser_terminalView->moveCursor(QTextCursor::End);
    ui->textBrowser_terminalView->insertPlainText(outputDevice->getChar());
    ui->textBrowser_terminalView->moveCursor(QTextCursor::End);
}

void ArmSim::keyPressed()
{
    // IRQ pin goes high
    unsigned char key = ui->textBrowser_terminalView->getChar();
    //cout << "key pressed: " << QString(key).toStdString() << endl;
    RAM->setLastKeyPressed(key);
    //cout << "lastKeyPressed: " << RAM->getLastKeyPressed() << endl;
    computer->getCPU()->setIRQ(1);
    regs->setFlag(IF, 1);
}

/*
 * Method: setComputer
 *  - changes the mainWindow's reference to the computer model, and also changes the direct references to the computer's RAM and registers
 */
void ArmSim::setComputer(Computer *com)
{
    computer = com;
    regs = com->registers();
    RAM = com->memory();
}

void ArmSim::loadFile(QString filepath)
{
    // extract file info
    QFileInfo fi(filepath);
    QString filename = fi.fileName();

    if (!filepath.isEmpty()) {
        // zero out regs
        computer->clearMemory();
        // load new file into memory
        Loader loader(filepath, computer->getCPU());

        if (loader.loaded()) {
            if(computer->memory()->ReadWord(0) != 0x00000000) {
                computer->registers()->set(PC, 0);
                computer->registers()->set(SP, 0);
                regs->changeMode(SVC);
            }
            else {
                regs->changeMode(SYS);
                regs->set(PC, RAM->progEntryPoint());
                regs->set(SP, 0x7000);
            }

            justLoaded = true;

            // display the checksum
            updateChecksum(QString::number(computer->memory()->calcChecksumForRAM()));
            updateFilename(filename);

            ui->checkBox_trace->setChecked(true);
            resetTraceFile();

            ui->textBrowser_terminalView->clear();
            //computer->printBreakpoints();
        }
        else {

            updateChecksum("");
            updateFilename("None");
        }
    }
}

void ArmSim::setupPanels()
{
    // set up register panel
    QStandardItemModel *model = new QStandardItemModel(16, 2, this);
    model->setHorizontalHeaderItem(0, new QStandardItem(QString(" Registers ")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString(" Value (0x16)")));
    for(int i = 0; i < 16; i++) {
    model->setItem(i,0,new QStandardItem(QString("r%1").arg(QString::number(i))));
    model->setItem(i,1,new QStandardItem(QString("          ")));
    }
    ui->tableView_regView->setModel(model);
    ui->tableView_regView->resizeColumnsToContents();

    //*
    // set up flag panel
    QStandardItemModel *model_flags = new QStandardItemModel(6, 1, this);
    //TODO: try and make vertical headers bold?
    model_flags->setItem(0, 0, new QStandardItem(QString("MODE")));
    model_flags->setItem(1, 0, new QStandardItem(QString(" N")));
    model_flags->setItem(2, 0, new QStandardItem(QString(" Z")));
    model_flags->setItem(3, 0, new QStandardItem(QString(" C")));
    model_flags->setItem(4, 0, new QStandardItem(QString(" F")));
    model_flags->setItem(5, 0, new QStandardItem(QString("IRQ")));

    model_flags->setItem(0,1, new QStandardItem(QString("   ")));
    model_flags->setItem(1,1, new QStandardItem(QString("   ")));
    model_flags->setItem(2,1, new QStandardItem(QString("   ")));
    model_flags->setItem(3,1, new QStandardItem(QString("   ")));
    model_flags->setItem(4,1, new QStandardItem(QString("   ")));
    model_flags->setItem(5,1, new QStandardItem(QString("   ")));

    ui->tableView_flagPanel->setModel(model_flags);
    ui->tableView_flagPanel->resizeColumnsToContents();

    //*/

    // set up memory panel
    ui->listWidget_memory->clear();

    ui->listWidget_disassembly->clear();

    ui->listWidget_stack->clear();

    ui->checkBox_trace->setChecked(false);

    ui->textBrowser_terminalView->clear();
}

void ArmSim::updateDisplay()
{
    updateRegPanel();
    updateFlagPanel();
    updateMemoryPanel();
    updateDisassemblyPanel();
    updateStackPanel();
}

//TODO: put filename and checksum in textboxes for cleaner display
void ArmSim::updateChecksum(QString checksum)
{
    //ui->menuBar_checksum->setTitle(checksum);
    ui->label_checksum->setText(QString("Checksum: %1").arg(checksum));
}

void ArmSim::updateFilename(QString filename) {
    //ui->menuBar_filename->setTitle(filename);
    ui->label_filename->setText(QString("File: %1").arg(filename));
}

void ArmSim::updateRegPanel()
{
    QStandardItemModel *model = new QStandardItemModel(16, 2, this);
    model->setHorizontalHeaderItem(0, new QStandardItem(QString(" Registers ")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString(" Value (0x16) ")));
    for(int i = 0; i < 16; i++) {
    QString regName = QString("r%1").arg(QString::number(i));
    int regValue = regs->get(i);
    QString regValueStr = QString("0x%1").arg(regValue, 8, 16, QChar('0'));

    model->setItem(i,0,new QStandardItem(regName));
    model->setItem(i,1,new QStandardItem(regValueStr));
    }
    ui->tableView_regView->setModel(model);
}

void ArmSim::updateFlagPanel()
{
    QStandardItemModel *model_flags = new QStandardItemModel(6, 1, this);
    //TODO: try and make vertical headers bold?
    model_flags->setItem(0, 0, new QStandardItem(QString("MODE")));
    model_flags->setItem(1, 0, new QStandardItem(QString(" N")));
    model_flags->setItem(2, 0, new QStandardItem(QString(" Z")));
    model_flags->setItem(3, 0, new QStandardItem(QString(" C")));
    model_flags->setItem(4, 0, new QStandardItem(QString(" F")));
    model_flags->setItem(5, 0, new QStandardItem(QString("IRQ")));
    bool n = regs->getFlag(NF);
    bool z = regs->getFlag(ZF);
    bool c = regs->getFlag(CF);
    bool f = regs->getFlag(VF);
    bool i = regs->getFlag(IF);
    model_flags->setItem(1,1, new QStandardItem(QString(" %1 ").arg(n)));
    model_flags->setItem(2,1, new QStandardItem(QString(" %1 ").arg(z)));
    model_flags->setItem(3,1, new QStandardItem(QString(" %1 ").arg(c)));
    model_flags->setItem(4,1, new QStandardItem(QString(" %1 ").arg(f)));
    model_flags->setItem(5,1, new QStandardItem(QString(" %1 ").arg(i)));
    QString mode = "SYS";
    if(computer->mode() == SVC)
        mode = "SVC";
    else if (computer->mode() == IRQ)
        mode = "IRQ";
    model_flags->setItem(0,1, new QStandardItem(mode));

    ui->tableView_flagPanel->setModel(model_flags);
}

void ArmSim::updateMemoryPanel()
{
    if(ui->lineEdit_memory->text().isEmpty()) {

    }
    else {
        ui->listWidget_memory->clear();
        bool ok;
        uint addr = ui->lineEdit_memory->text().toUInt(&ok, 16);

        // TODO: try using a tableWidget/tableview for better display?
        // TODO: account for reading past end of memory
        for(int i = 0; i < 20; i++) {
            QString line = QString("0x%1  ").arg(addr, 8, 16, QChar('0'));

            QString hexLine = "";

            QString charLine = "";

            for(uint j = 0; j < 16; j++) {
                unsigned char byte = computer->memory()->ReadByte(addr++);

                // display 16 bytes per line
                hexLine.append(QString("%1 ").arg(byte, 2, 16, QChar('0')));

                // display the char value of each byte
                if(byte == '\n' || byte == 0)
                    charLine.append(QChar('.'));
                else
                    charLine.append(QChar(byte));

            }

            line.append(hexLine);
            line.append(" " + charLine);

            new QListWidgetItem(line, ui->listWidget_memory);
        }
    }
}


//TODO: make breakpoints visible
void ArmSim::updateDisassemblyPanel()
{
    ui->listWidget_disassembly->clear();

    uint addr = regs->get(15);
    uint offset = (addr/4 < 5) ? addr/4 : 5;
    //uint highlight = 0;

    //cout << "here" << endl;
    QString line = "";

    // print 3 or less lines before current line at PC
    for(int i = offset; i > 0; i--) {

        uint curAddr = addr - (i*4);
        uint curInstr = RAM->ReadWord(curAddr);

        line.append(generateDisassemblyForPanel(curAddr, curInstr, regs, RAM));

        // append the line to thedisassembly panel
        new QListWidgetItem(line, ui->listWidget_disassembly);

        line = "";
    }

    //*
    line.append(generateDisassemblyForPanel(addr, RAM->ReadWord(addr), regs, RAM));

    // add row of cur instr and highlight it
    new QListWidgetItem(line, ui->listWidget_disassembly);
    if(justLoaded)
        ui->listWidget_disassembly->item(offset)->setBackgroundColor(Qt::yellow);
    else
        ui->listWidget_disassembly->item(offset - 1)->setBackgroundColor(Qt::yellow);

    line = "";

    //*/

    offset = 0;
    while(offset++ < 20 && (RAM->addr_space() > addr + offset*4)) {
        uint curAddr = addr + offset*4;
        uint curInstr = RAM->ReadWord(curAddr);

        line.append(generateDisassemblyForPanel(curAddr, curInstr, regs, RAM));

        // append the line to thedisassembly panel
        new QListWidgetItem(line, ui->listWidget_disassembly);

        // reset line
        line = "";
    }
}

QString ArmSim::generateDisassemblyForPanel(uint curAddr, uint curInstr, RegisterBank* regs, Memory* memory)
{
    QString line = "";
    //cout  << "print line" <<  endl;
    //cout << "print instr: " << QString("%1").arg(curInstr,8,16,QChar('0')).toStdString() << " at addr " << QString("%1").arg(curAddr,8,16,QChar('0')).toStdString() << endl;
    // append the address
    line.append(QString("0x%1  ").arg(curAddr, 8, 16, QChar('0')));
    // append the machine language translation of the instruction at that address
    line.append(QString("0x%1\t").arg(curInstr, 8, 16, QChar('0')));
    line.append(CPU::disassemblyForInstr(curInstr, regs, memory, curAddr));
    //cout << "finished printing line" << endl;
    return line;
}

void ArmSim::updateStackPanel()
{
    ui->listWidget_stack->clear();
    uint addr = regs->get(13);


    for(int i = addr; i >= 0; i-=4) {
        uint word = computer->memory()->ReadWord(i);

        QString line = QString("0x%1  ").arg(i, 8, 16, QChar('0'));
        line.append(QString("0x%1").arg(word, 8, 16, QChar('0')));
        new QListWidgetItem(line, ui->listWidget_stack);
    }
}

void ArmSim::resetTraceFile()
{
    if(computer->getTracingStream() != nullptr) {
        computer->getTracingStream()->flush();
        computer->getTracingStream()->close();
    }
    ui->checkBox_trace->setChecked(true);
    computer->getTracingStream()->open("trace.log");
    computer->setTracing(true);
}

void ArmSim::on_pushButton_clicked()
{
    QString filepath_temp = filepath;
    filepath = QFileDialog::getOpenFileName(
                this,
                tr("Load File"),
                QDir::currentPath(),
                ".exe Files (*.exe);;All Files (*.*)"
                );
    if(!filepath.isEmpty() && filepath != "") {
        //cout << "load" << endl;
        loadFile(filepath);
    }
    else {
        filepath = filepath_temp;
        /*
        setupPanels();
        updateChecksum("");
        updateFilename("");
        */
    }
    updateDisplay();
}

void ArmSim::on_pushButton_reset_clicked()
{
    // if a file has already been loaded
    if(!filepath.isEmpty()) {
        loadFile(filepath);
        updateDisplay();
        ui->textBrowser_terminalView->clear();
    }
}

void ArmSim::on_pushButton_step_clicked()
{
    // cannot step after the last instruction
    if(regs->get(15)+4 < RAM->addr_space()) {
        computer->step();
        updateDisplay();
    }
}

void ArmSim::on_pushButton_run_clicked()
{
    if(!filepath.isEmpty()) {
        justLoaded = false;
        ui->pushButton->setEnabled(false);
        ui->pushButton_run->setEnabled(false);
        ui->pushButton_step->setEnabled(false);
        ui->pushButton_run->setIcon(QIcon(":/icons/running.png"));
        computer->setRunning(true);
        RunThread *thread = new RunThread(computer);
        connect(thread, &QThread::finished, this, &ArmSim::threadEnded);
        thread->start();
    }
}

void ArmSim::threadEnded()
{
    computer->setRunning(false);
    //cout << "GUI received HALT signal" << endl;
    ui->pushButton_run->setIcon(QIcon(":/icons/run.png"));
    ui->pushButton->setEnabled(true);
    ui->pushButton_run->setEnabled(true);
    ui->pushButton_step->setEnabled(true);
    updateDisplay();


    if(opts->exec()) {
        computer->getTracingStream()->flush();
        computer->getTracingStream()->close();
        exit(1);
    }
}

void ArmSim::on_lineEdit_memory_returnPressed()
{
    if(!filepath.isEmpty() && !ui->lineEdit_memory->text().isEmpty()) {
        updateMemoryPanel();
    }
    else {
        QMessageBox msgBox;
        QFont f("Segoe UI", 12);
        msgBox.setFont(f);
        msgBox.setText("Load a file into memory.");
        msgBox.setWindowTitle("Error");
        msgBox.exec();
    }
}

void ArmSim::on_pushButton_stop_clicked()
{
    justLoaded = true;
    // turn off the computer's running flag
    computer->setRunning(false);
}

void ArmSim::on_checkBox_trace_clicked()
{
    if (ui->checkBox_trace->isChecked()) {
        computer->getTracingStream()->open("trace.log");
        computer->setTracing(true);
    }
    else {
        computer->getTracingStream()->flush();
        computer->getTracingStream()->close();
        computer->setTracing(false);
    }

}

// TODO: dd functionality of removing breakpoints
void ArmSim::on_pushButton_add_breakpoint_clicked()
{
    if(filepath.isEmpty()){
        QMessageBox msgBox;
        QFont f("Segoe UI", 12);
        msgBox.setFont(f);
        msgBox.setText("Load a file into memory.");
        msgBox.setWindowTitle("Error");
        msgBox.exec();
    }
    else {
        QString bp = QInputDialog::getText(this, "Add Breakpoint", "Breakpoint at address:");
        bool ok;
        uint breakpoint = bp.toUInt(&ok, 16);

        // breakpoint address must be divisible by 4
        if (breakpoint % 4 != 0 || breakpoint < 0) {
                QMessageBox msgBox;
                QFont f("Segoe UI", 12);
                msgBox.setFont(f);
                msgBox.setText("Breakpoint address must be a positive integer divisible by 4.");
                msgBox.setWindowTitle("Error");
                msgBox.exec();
        }
        computer->addBreakpoint(breakpoint);
    }

}

void ArmSim::on_checkBox_breakpoint_clicked()
{
    if (ui->checkBox_trace->isChecked()) {
        computer->setBreakPoint(true);
    }
    else {
        computer->setBreakPoint(false);
    }
}

