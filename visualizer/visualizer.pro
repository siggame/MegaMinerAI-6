INCLUDEPATH += ../codegen/output/visualizer ../codegen/output/visualizer/sexp

!exists( ../codegen/output/visualizer/parser.cpp ) {
	system( "cd ../codegen && python main.py ./templates" )
	system( "cd ../codegen/output/visualizer && make" )
}

LIBS += ../codegen/output/visualizer/sexp/sexp.a
SOURCES += main.cpp visualizerWindow.cpp gameboardWidget.cpp
SOURCES += ../codegen/output/visualizer/parser.cpp 
SOURCES += ../codegen/output/visualizer/structures.cpp
HEADERS += visualizerWindow.h gameboardWidget.h
CONFIG += debug
QT += opengl
