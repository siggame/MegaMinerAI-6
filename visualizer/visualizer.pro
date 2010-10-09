INCLUDEPATH += ./parser ./parser/sexp

LIBS += ./parser/sexp/sexp.a
SOURCES += main.cpp visualizerWindow.cpp gameboardWidget.cpp
SOURCES += ./parser/parser.cpp 
SOURCES += ./parser/structures.cpp
SOURCES += texture.cpp statsDialog.cpp
HEADERS += visualizerWindow.h gameboardWidget.h
HEADERS += texture.h statsDialog.h
CONFIG += debug
QT += opengl
