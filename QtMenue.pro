QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
INCLUDEPATH += teensy_menue
INCLUDEPATH += teensy_menue/simulation
INCLUDEPATH += ../../BatDetector/lib/Menue/src
INCLUDEPATH += ../../BatDetector/lib/MemPool/src
INCLUDEPATH += ../../BatDetector/include

DEFINES += SIMU_DISPLAY
DEFINES += TEENSYDUINO=145
DEFINES += "F_CPU=180000000"
DEFINES += ARDUINO_TEENSY41

SOURCES += \
    ../../BatDetector/lib/MemPool/src/clDebugLog.cpp \
    ../../BatDetector/lib/MemPool/src/clFixMemPool.cpp \
    ../../BatDetector/lib/MemPool/src/clLog.cpp \
    ../../BatDetector/lib/MemPool/src/clPool.cpp \
    ../../BatDetector/lib/MemPool/src/clTimeUtils.cpp \
    ../../BatDetector/lib/Menue/src/MenueSystem.cpp \
    ../../BatDetector/lib/Menue/src/cpanel.cpp \
    ../../BatDetector/lib/Menue/src/cpargraph.cpp \
    ../../BatDetector/lib/Menue/src/ctext.cpp \
    ../../BatDetector/lib/Menue/src/cutils.cpp \
    ../../BatDetector/src/cAudio.cpp \
    ../../BatDetector/src/cCassette.cpp \
    ../../BatDetector/src/cLog.cpp \
    ../../BatDetector/src/cTerminal.cpp \
    ../../BatDetector/src/cWheels.cpp \
    ../../BatDetector/src/cfileinfo.cpp \
    ../../BatDetector/src/cgps.cpp \
    ../../BatDetector/src/cgpx.cpp \
    ../../BatDetector/src/cmain.cpp \
    ../../BatDetector/src/cmenue.cpp \
    ../../BatDetector/src/config.cpp \
    ../../BatDetector/src/cproject.cpp \
    ../../BatDetector/src/csunrise.cpp \
    ../../BatDetector/src/cxmlhelper.cpp \
    ../../BatDetector/src/fnt8x11.cpp \
    ../../BatDetector/src/pnlbats.cpp \
    ../../BatDetector/src/pnlfilebrowser.cpp \
    ../../BatDetector/src/pnlinfo.cpp \
    ../../BatDetector/src/pnllive.cpp \
    ../../BatDetector/src/pnlmain.cpp \
    ../../BatDetector/src/pnlparams.cpp \
    ../../BatDetector/src/pnlwaterfall.cpp \
    ../../BatDetector/src/texts.cpp \
    teensy_menue/main.cpp \
    teensy_menue/mainwindow.cpp \
    teensy_menue/simulation/Adafruit_Simu.cpp \
    teensy_menue/simulation/Arduino.cpp \
    teensy_menue/simulation/Audio.cpp \
    teensy_menue/simulation/Bounce.cpp \
    teensy_menue/simulation/Encoder.cpp \
    teensy_menue/simulation/ILI9341_t3.cpp \
    teensy_menue/simulation/Metro.cpp \
    teensy_menue/simulation/Print.cpp \
    teensy_menue/simulation/TinyGps.cpp \
    teensy_menue/simulation/cRtc.cpp \
    teensy_menue/simulation/cSdCard.cpp \
    teensy_menue/simulation/dirhelper.cpp \
    teensy_menue/simulation/glcdfont.c \
    teensy_menue/wdggraph.cpp

HEADERS += \
    ../../BatDetector/include/cAudio.h \
    ../../BatDetector/include/cCassette.h \
    ../../BatDetector/include/cLog.h \
    ../../BatDetector/include/cTerminal.h \
    ../../BatDetector/include/cWheels.h \
    ../../BatDetector/include/cfileinfo.h \
    ../../BatDetector/include/cgps.h \
    ../../BatDetector/include/cgpx.h \
    ../../BatDetector/include/cmenue.h \
    ../../BatDetector/include/config.h \
    ../../BatDetector/include/cproject.h \
    ../../BatDetector/include/cxmlhelper.h \
    ../../BatDetector/include/play_fats_raw.h \
    ../../BatDetector/include/pnlbats.h \
    ../../BatDetector/include/pnlfilebrowser.h \
    ../../BatDetector/include/pnllive.h \
    ../../BatDetector/include/pnlmain.h \
    ../../BatDetector/include/pnlparams.h \
    ../../BatDetector/include/pnlwaterfall.h \
    ../../BatDetector/include/types.h \
    ../../BatDetector/lib/MemPool/src/clFixMemPool.h \
    ../../BatDetector/lib/MemPool/src/clPool.h \
    ../../BatDetector/lib/MemPool/src/cldebuglog.h \
    ../../BatDetector/lib/MemPool/src/cllog.h \
    ../../BatDetector/lib/MemPool/src/cltimeutils.h \
    ../../BatDetector/lib/MemPool/src/myalloc.h \
    ../../BatDetector/lib/MemPool/src/objhndlglib.h \
    ../../BatDetector/lib/MemPool/src/typedef.h \
    ../../BatDetector/lib/Menue/src/MenueSystem.h \
    ../../BatDetector/lib/Menue/src/cpanel.h \
    ../../BatDetector/lib/Menue/src/cpargraph.h \
    ../../BatDetector/lib/Menue/src/crfft.h \
    ../../BatDetector/lib/Menue/src/crfft_o2.h \
    ../../BatDetector/lib/Menue/src/ctext.h \
    ../../BatDetector/lib/Menue/src/cutils.h \
    ../../BatDetector/lib/Menue/src/debug.h \
    ../../BatDetector/lib/Menue/src/menuedefs.h \
    ../../BatDetector/lib/Menue/src/my_vector.h \
    ../../BatDetector/src/csunrise.h \
    teensy_menue/errors.h \
    teensy_menue/mainwindow.h \
    teensy_menue/simulation/Adafruit_SPITFT_Macros.h \
    teensy_menue/simulation/Adafruit_Simu.h \
    teensy_menue/simulation/Arduino.h \
    teensy_menue/simulation/Audio.h \
    teensy_menue/simulation/AudioStream.h \
    teensy_menue/simulation/Bounce.h \
    teensy_menue/simulation/EEPROM.h \
    teensy_menue/simulation/Encoder.h \
    teensy_menue/simulation/ILI9341_t3.h \
    teensy_menue/simulation/InternalTemperature.h \
    teensy_menue/simulation/Metro.h \
    teensy_menue/simulation/Print.h \
    teensy_menue/simulation/Time.h \
    teensy_menue/simulation/TimeLib.h \
    teensy_menue/simulation/TinyGPS.h \
    teensy_menue/simulation/WProgram.h \
    teensy_menue/simulation/WString.h \
    teensy_menue/simulation/arduino.h \
    teensy_menue/simulation/cRtc.h \
    teensy_menue/simulation/cSdCard.h \
    teensy_menue/simulation/crfft.h \
    teensy_menue/simulation/dirhelper.h \
    teensy_menue/simulation/gfxfont.h \
    teensy_menue/simulation/pins_arduino.h \
    teensy_menue/simulation/utility/imxrt_hw.h \
    teensy_menue/strgtbl.h \
    teensy_menue/wdggraph.h

FORMS += \
    teensy_menue/mainwindow.ui \
    teensy_menue/wdggraph.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    teensy_menue/english.rc \
    teensy_menue/german.rc
