Visual Studio Template Readme

In order to use this Visual Studio project, you must complete the following steps:
1. Run the code generator (python main.py in codegen). If the templates have somehow gotten Windows line endings (git may do this to you automatically) you'll need to run dos2unix on all of them or else the output will have CR|CR|LF throughout the generated files and VS won't build them.
2. Copy lex.yy.h and lex.yy.cpp from a Linux build into codegen/sexp/ (I tried building with a copy of flex for Windows, but it doesn't generate headers...?)

Notes:
* If you want to make your own solution/project from scratch, you'll need to define THREADLESS and YY_NO_UNISTD_H for the project.

*  On build, the VS project will delete codegen/output/c/AI.h and codegen/output/c/AI.cpp to prevent some weird header mismatches that cause stack corruption (The VS project adds the codegen output folder to the include path, the compiler then sees AI.h in there and in the project folder and isn't consistent about which one it uses). Since the makefile copies AI.h and AI.cpp into the codegen folder with each build, this should be fine.

For distribution:
All of the steps above are one shot things and should only need to be done once. You should be able to drop the makefile in to the VS folder (or the VS sln and vcproj into a makefile based ai) and they should play nicely. I prefer the VS debugger and IDE, especially when pressed for time...
