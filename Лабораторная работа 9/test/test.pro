include(gtest_dependency.pri)
INCLUDEPATH += D:\Lab9_Project_for_tests
TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += thread
CONFIG -= qt

HEADERS += \
        ../../Lab9_Project_for_tests/IKeypad.h \
        ../../Lab9_Project_for_tests/ILatch.h \
        ../../Lab9_Project_for_tests/lockcontroller.h \
        mock_classes.h \
        tst_t1.h

SOURCES += \
        ../../Lab9_Project_for_tests/lockcontroller.cpp \
        main.cpp
