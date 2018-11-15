/********************************************************************************
** Form generated from reading UI file 'armsim.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ARMSIM_H
#define UI_ARMSIM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <terminaltextbrowser.h>

QT_BEGIN_NAMESPACE

class Ui_ArmSim
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QListWidget *listWidget_disassembly;
    QLabel *label_checksum;
    QLabel *label_4;
    QFrame *line_2;
    QLabel *label_flags;
    QTableView *tableView_regView;
    QLabel *label_5;
    QFrame *line;
    QListWidget *listWidget_memory;
    QLabel *label_filename;
    TerminalTextBrowser *textBrowser_terminalView;
    QListWidget *listWidget_stack;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton;
    QPushButton *pushButton_reset;
    QPushButton *pushButton_run;
    QPushButton *pushButton_stop;
    QPushButton *pushButton_step;
    QLabel *label;
    QHBoxLayout *horizontalLayout_3;
    QCheckBox *checkBox_trace;
    QCheckBox *checkBox_breakpoint;
    QPushButton *pushButton_add_breakpoint;
    QLineEdit *lineEdit_memory;
    QLabel *label_3;
    QLabel *label_regs;
    QTableView *tableView_flagPanel;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ArmSim)
    {
        if (ArmSim->objectName().isEmpty())
            ArmSim->setObjectName(QStringLiteral("ArmSim"));
        ArmSim->resize(871, 794);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ArmSim->sizePolicy().hasHeightForWidth());
        ArmSim->setSizePolicy(sizePolicy);
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/Untitled.png"), QSize(), QIcon::Normal, QIcon::Off);
        ArmSim->setWindowIcon(icon);
        centralWidget = new QWidget(ArmSim);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        listWidget_disassembly = new QListWidget(centralWidget);
        listWidget_disassembly->setObjectName(QStringLiteral("listWidget_disassembly"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(listWidget_disassembly->sizePolicy().hasHeightForWidth());
        listWidget_disassembly->setSizePolicy(sizePolicy1);
        listWidget_disassembly->setMaximumSize(QSize(16777215, 200));
        QFont font;
        font.setFamily(QStringLiteral("Lucida Console"));
        font.setPointSize(10);
        listWidget_disassembly->setFont(font);

        gridLayout->addWidget(listWidget_disassembly, 7, 0, 1, 3);

        label_checksum = new QLabel(centralWidget);
        label_checksum->setObjectName(QStringLiteral("label_checksum"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_checksum->sizePolicy().hasHeightForWidth());
        label_checksum->setSizePolicy(sizePolicy2);
        label_checksum->setMaximumSize(QSize(16777215, 30));
        QFont font1;
        font1.setFamily(QStringLiteral("Segoe UI Semibold"));
        font1.setPointSize(16);
        font1.setBold(true);
        font1.setWeight(75);
        label_checksum->setFont(font1);

        gridLayout->addWidget(label_checksum, 2, 0, 2, 2);

        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        sizePolicy2.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy2);
        QFont font2;
        font2.setFamily(QStringLiteral("Segoe UI Semibold"));
        font2.setPointSize(12);
        font2.setBold(true);
        font2.setWeight(75);
        label_4->setFont(font2);

        gridLayout->addWidget(label_4, 8, 4, 1, 1);

        line_2 = new QFrame(centralWidget);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_2, 4, 0, 1, 5);

        label_flags = new QLabel(centralWidget);
        label_flags->setObjectName(QStringLiteral("label_flags"));
        sizePolicy2.setHeightForWidth(label_flags->sizePolicy().hasHeightForWidth());
        label_flags->setSizePolicy(sizePolicy2);
        label_flags->setFont(font2);

        gridLayout->addWidget(label_flags, 6, 4, 1, 1);

        tableView_regView = new QTableView(centralWidget);
        tableView_regView->setObjectName(QStringLiteral("tableView_regView"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(tableView_regView->sizePolicy().hasHeightForWidth());
        tableView_regView->setSizePolicy(sizePolicy3);
        tableView_regView->setMaximumSize(QSize(256, 200));
        tableView_regView->setFont(font);
        tableView_regView->setLayoutDirection(Qt::LeftToRight);
        tableView_regView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableView_regView->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        tableView_regView->setGridStyle(Qt::SolidLine);
        tableView_regView->verticalHeader()->setVisible(false);

        gridLayout->addWidget(tableView_regView, 7, 4, 1, 1);

        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        sizePolicy2.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy2);
        label_5->setFont(font2);

        gridLayout->addWidget(label_5, 10, 0, 1, 1);

        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 1, 0, 1, 5);

        listWidget_memory = new QListWidget(centralWidget);
        listWidget_memory->setObjectName(QStringLiteral("listWidget_memory"));
        sizePolicy1.setHeightForWidth(listWidget_memory->sizePolicy().hasHeightForWidth());
        listWidget_memory->setSizePolicy(sizePolicy1);
        listWidget_memory->setMaximumSize(QSize(16777215, 200));
        listWidget_memory->setFont(font);

        gridLayout->addWidget(listWidget_memory, 9, 0, 1, 4);

        label_filename = new QLabel(centralWidget);
        label_filename->setObjectName(QStringLiteral("label_filename"));
        sizePolicy2.setHeightForWidth(label_filename->sizePolicy().hasHeightForWidth());
        label_filename->setSizePolicy(sizePolicy2);
        label_filename->setMaximumSize(QSize(16777215, 30));
        label_filename->setFont(font1);

        gridLayout->addWidget(label_filename, 0, 0, 1, 1);

        textBrowser_terminalView = new TerminalTextBrowser(centralWidget);
        textBrowser_terminalView->setObjectName(QStringLiteral("textBrowser_terminalView"));
        sizePolicy1.setHeightForWidth(textBrowser_terminalView->sizePolicy().hasHeightForWidth());
        textBrowser_terminalView->setSizePolicy(sizePolicy1);
        textBrowser_terminalView->setMaximumSize(QSize(16777215, 224));
        textBrowser_terminalView->setFont(font);
        textBrowser_terminalView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        gridLayout->addWidget(textBrowser_terminalView, 11, 0, 1, 5);

        listWidget_stack = new QListWidget(centralWidget);
        listWidget_stack->setObjectName(QStringLiteral("listWidget_stack"));
        sizePolicy3.setHeightForWidth(listWidget_stack->sizePolicy().hasHeightForWidth());
        listWidget_stack->setSizePolicy(sizePolicy3);
        listWidget_stack->setMaximumSize(QSize(256, 200));

        gridLayout->addWidget(listWidget_stack, 9, 4, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setSizeConstraint(QLayout::SetFixedSize);
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icons/open_file.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton->setIcon(icon1);
        pushButton->setIconSize(QSize(24, 24));

        horizontalLayout_2->addWidget(pushButton);

        pushButton_reset = new QPushButton(centralWidget);
        pushButton_reset->setObjectName(QStringLiteral("pushButton_reset"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/icons/reset.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_reset->setIcon(icon2);
        pushButton_reset->setIconSize(QSize(24, 24));

        horizontalLayout_2->addWidget(pushButton_reset);

        pushButton_run = new QPushButton(centralWidget);
        pushButton_run->setObjectName(QStringLiteral("pushButton_run"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/icons/run.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_run->setIcon(icon3);
        pushButton_run->setIconSize(QSize(24, 24));

        horizontalLayout_2->addWidget(pushButton_run);

        pushButton_stop = new QPushButton(centralWidget);
        pushButton_stop->setObjectName(QStringLiteral("pushButton_stop"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/icons/stop.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_stop->setIcon(icon4);
        pushButton_stop->setIconSize(QSize(24, 24));

        horizontalLayout_2->addWidget(pushButton_stop);

        pushButton_step = new QPushButton(centralWidget);
        pushButton_step->setObjectName(QStringLiteral("pushButton_step"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/icons/step_into.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_step->setIcon(icon5);
        pushButton_step->setIconSize(QSize(24, 24));

        horizontalLayout_2->addWidget(pushButton_step);


        gridLayout->addLayout(horizontalLayout_2, 0, 3, 1, 2);

        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        sizePolicy2.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy2);
        label->setMaximumSize(QSize(16777215, 20));
        label->setFont(font2);

        gridLayout->addWidget(label, 8, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setSizeConstraint(QLayout::SetFixedSize);
        checkBox_trace = new QCheckBox(centralWidget);
        checkBox_trace->setObjectName(QStringLiteral("checkBox_trace"));
        QFont font3;
        font3.setFamily(QStringLiteral("Segoe UI Semibold"));
        font3.setPointSize(10);
        font3.setBold(true);
        font3.setWeight(75);
        checkBox_trace->setFont(font3);
        checkBox_trace->setChecked(false);

        horizontalLayout_3->addWidget(checkBox_trace);

        checkBox_breakpoint = new QCheckBox(centralWidget);
        checkBox_breakpoint->setObjectName(QStringLiteral("checkBox_breakpoint"));
        checkBox_breakpoint->setFont(font3);

        horizontalLayout_3->addWidget(checkBox_breakpoint);

        pushButton_add_breakpoint = new QPushButton(centralWidget);
        pushButton_add_breakpoint->setObjectName(QStringLiteral("pushButton_add_breakpoint"));
        QFont font4;
        font4.setFamily(QStringLiteral("Segoe UI Semibold"));
        font4.setPointSize(9);
        font4.setBold(true);
        font4.setWeight(75);
        pushButton_add_breakpoint->setFont(font4);

        horizontalLayout_3->addWidget(pushButton_add_breakpoint);


        gridLayout->addLayout(horizontalLayout_3, 3, 3, 1, 2);

        lineEdit_memory = new QLineEdit(centralWidget);
        lineEdit_memory->setObjectName(QStringLiteral("lineEdit_memory"));
        lineEdit_memory->setMaximumSize(QSize(16777215, 20));

        gridLayout->addWidget(lineEdit_memory, 8, 1, 1, 3);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        sizePolicy2.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy2);
        label_3->setFont(font2);

        gridLayout->addWidget(label_3, 5, 0, 2, 2);

        label_regs = new QLabel(centralWidget);
        label_regs->setObjectName(QStringLiteral("label_regs"));
        sizePolicy2.setHeightForWidth(label_regs->sizePolicy().hasHeightForWidth());
        label_regs->setSizePolicy(sizePolicy2);
        label_regs->setFont(font2);

        gridLayout->addWidget(label_regs, 6, 3, 1, 1);

        tableView_flagPanel = new QTableView(centralWidget);
        tableView_flagPanel->setObjectName(QStringLiteral("tableView_flagPanel"));
        tableView_flagPanel->setEnabled(true);
        sizePolicy3.setHeightForWidth(tableView_flagPanel->sizePolicy().hasHeightForWidth());
        tableView_flagPanel->setSizePolicy(sizePolicy3);
        tableView_flagPanel->setMaximumSize(QSize(71, 200));
        tableView_flagPanel->setFont(font);
        tableView_flagPanel->setLineWidth(1);
        tableView_flagPanel->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableView_flagPanel->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableView_flagPanel->setShowGrid(true);
        tableView_flagPanel->setGridStyle(Qt::SolidLine);
        tableView_flagPanel->horizontalHeader()->setVisible(false);
        tableView_flagPanel->verticalHeader()->setVisible(false);

        gridLayout->addWidget(tableView_flagPanel, 7, 3, 1, 1);

        ArmSim->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ArmSim);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 871, 21));
        ArmSim->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ArmSim);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ArmSim->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ArmSim);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ArmSim->setStatusBar(statusBar);

        retranslateUi(ArmSim);

        QMetaObject::connectSlotsByName(ArmSim);
    } // setupUi

    void retranslateUi(QMainWindow *ArmSim)
    {
        ArmSim->setWindowTitle(QApplication::translate("ArmSim", "ArmSim", nullptr));
        label_checksum->setText(QApplication::translate("ArmSim", "Checksum:", nullptr));
        label_4->setText(QApplication::translate("ArmSim", "Stack", nullptr));
        label_flags->setText(QApplication::translate("ArmSim", "Registers", nullptr));
        label_5->setText(QApplication::translate("ArmSim", "Terminal", nullptr));
        label_filename->setText(QApplication::translate("ArmSim", "File:", nullptr));
        pushButton->setText(QString());
#ifndef QT_NO_SHORTCUT
        pushButton->setShortcut(QApplication::translate("ArmSim", "Ctrl+O", nullptr));
#endif // QT_NO_SHORTCUT
        pushButton_reset->setText(QString());
#ifndef QT_NO_SHORTCUT
        pushButton_reset->setShortcut(QApplication::translate("ArmSim", "Ctrl+R", nullptr));
#endif // QT_NO_SHORTCUT
        pushButton_run->setText(QString());
#ifndef QT_NO_SHORTCUT
        pushButton_run->setShortcut(QApplication::translate("ArmSim", "F5", nullptr));
#endif // QT_NO_SHORTCUT
        pushButton_stop->setText(QString());
#ifndef QT_NO_SHORTCUT
        pushButton_stop->setShortcut(QApplication::translate("ArmSim", "Ctrl+Q", nullptr));
#endif // QT_NO_SHORTCUT
        pushButton_step->setText(QString());
#ifndef QT_NO_SHORTCUT
        pushButton_step->setShortcut(QApplication::translate("ArmSim", "F10", nullptr));
#endif // QT_NO_SHORTCUT
        label->setText(QApplication::translate("ArmSim", "Memory:", nullptr));
        checkBox_trace->setText(QApplication::translate("ArmSim", "Trace", nullptr));
#ifndef QT_NO_SHORTCUT
        checkBox_trace->setShortcut(QApplication::translate("ArmSim", "Ctrl+T", nullptr));
#endif // QT_NO_SHORTCUT
        checkBox_breakpoint->setText(QApplication::translate("ArmSim", "Breakpoint", nullptr));
#ifndef QT_NO_SHORTCUT
        checkBox_breakpoint->setShortcut(QApplication::translate("ArmSim", "Ctrl+B", nullptr));
#endif // QT_NO_SHORTCUT
        pushButton_add_breakpoint->setText(QApplication::translate("ArmSim", "Add Breakpoint", nullptr));
        label_3->setText(QApplication::translate("ArmSim", "Disassembly", nullptr));
        label_regs->setText(QApplication::translate("ArmSim", "Flags", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ArmSim: public Ui_ArmSim {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ARMSIM_H
