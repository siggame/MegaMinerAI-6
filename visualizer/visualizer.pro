INCLUDEPATH += ./parser ./parser/sexp

LIBS += ./parser/sexp/sexp.a
SOURCES += main.cpp visualizerWindow.cpp gameboardWidget.cpp
SOURCES += ./parser/parser.cpp 
SOURCES += ./parser/structures.cpp
SOURCES += texture.cpp statsDialog.cpp config.cpp visettings.cpp log.cpp
HEADERS += visualizerWindow.h gameboardWidget.h log.h
HEADERS += texture.h statsDialog.h config.h visettings.h
CONFIG += debug
QT += opengl
