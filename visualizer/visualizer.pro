INCLUDEPATH += ./parser ./parser/sexp

LIBS += ./parser/sexp/sexp.a
SOURCES += main.cpp visualizerWindow.cpp gameboardWidget.cpp
SOURCES += ./parser/parser.cpp 
SOURCES += ./parser/structures.cpp
HEADERS += visualizerWindow.h gameboardWidget.h
CONFIG += debug
QT += opengl
