#-------------------------------------------------
#
# Project created by QtCreator 2018-09-01T18:07:58
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = armsim
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11# console

SOURCES += \
        main.cpp \
        armsim.cpp \
    options.cpp \
    loader.cpp \
    testram.cpp \
    testloader.cpp \
    memory.cpp \
    cpu.cpp \
    computer.cpp \
    registerbank.cpp \
    runthread.cpp \
    testcpu.cpp \
    testcomputer.cpp \
    instruction.cpp \
    operand2.cpp \
    testinstruction.cpp \
    operand2_immediate.cpp \
    instruction_dataprocessing.cpp \
    operand2_regshiftimmediate.cpp \
    instruction_loadstore.cpp \
    instruction_branch.cpp \
    operand2_regshiftreg.cpp \
    barrelshifter.cpp \
    testbarrelshifter.cpp \
    testoperand2.cpp \
    instruction_exception.cpp \
    outputdevice.cpp \
    terminaltextbrowser.cpp

HEADERS += \
        armsim.h \
    options.h \
    elf.h \
    loader.h \
    testram.h \
    testloader.h \
    memory.h \
    cpu.h \
    computer.h \
    registerbank.h \
    runthread.h \
    testcpu.h \
    testcomputer.h \
    instruction.h \
    operand2.h \
    testinstruction.h \
    operand2_immediate.h \
    instruction_dataprocessing.h \
    operand2_regshiftimmediate.h \
    instruction_loadstore.h \
    instruction_branch.h \
    operand2_regshiftreg.h \
    barrelshifter.h \
    testbarrelshifter.h \
    testoperand2.h \
    instruction_exception.h \
    outputdevice.h \
    terminaltextbrowser.h

FORMS += \
        armsim.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc

DISTFILES += \
    icons/stop.png
