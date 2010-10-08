INCLUDEPATH += ./parser ./parser/sexp

LIBS += ./parser/sexp/sexp.a
SOURCES += main.cpp visualizerWindow.cpp gameboardWidget.cpp
SOURCES += ./parser/parser.cpp 
SOURCES += ./parser/structures.cpp
SOURCES += texture.cpp
HEADERS += visualizerWindow.h gameboardWidget.h
HEADERS += texture.h
CONFIG += debug
QT += opengl
