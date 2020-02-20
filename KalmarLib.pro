# Copyright (C) 2020 FeZar97.
# Distributed under the lgplv3 software license, see the accompanying
# Everyone is permitted to copy and distribute verbatim copies
# of this license document, but changing it is not allowed.

QT -= gui
CONFIG += c++11

TARGET = KalmarLib
TEMPLATE = lib

DEFINES += KALMARRECEIVER_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS

CONFIG(release, debug|release): {
    DESTDIR = $$PWD/build/release
} else {
    DESTDIR = $$PWD/build/debug
}

VERSION = 0.1.0

HEADERS += KalmarDefinitions.h \
           KalmarTract.h \
           KalmarKalibrator.h \
           KalmarReceiver_global.h \
           KalmarReceiver.h

SOURCES += KalmarTract.cpp \
           KalmarKalibrator.cpp \
           KalmarReceiver.cpp
