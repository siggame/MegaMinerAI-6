# Microsoft Developer Studio Generated NMAKE File, Format Version 4.10
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=ZlibTool - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to ZlibTool - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "ZlibTool - Win32 Release" && "$(CFG)" !=\
 "ZlibTool - Win32 Debug" && "$(CFG)" != "ZlibTool - Win32 Unicode Debug" &&\
 "$(CFG)" != "ZlibTool - Win32 Unicode Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "ZlibTool.mak" CFG="ZlibTool - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ZlibTool - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ZlibTool - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ZlibTool - Win32 Unicode Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ZlibTool - Win32 Unicode Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 
################################################################################
# Begin Project
# PROP Target_Last_Scanned "ZlibTool - Win32 Debug"
RSC=rc.exe
MTL=mktyplib.exe
CPP=cl.exe

!IF  "$(CFG)" == "ZlibTool - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP BASE Target_Ext "ocx"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# PROP Target_Ext "ocx"
OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\ZlibTool.ocx" "$(OUTDIR)\ZlibTool.pch"\
 "$(OUTDIR)\regsvr32.trg"

CLEAN : 
	-@erase "$(INTDIR)\Adler32.obj"
	-@erase "$(INTDIR)\Deflate.obj"
	-@erase "$(INTDIR)\Infblock.obj"
	-@erase "$(INTDIR)\Infcodes.obj"
	-@erase "$(INTDIR)\Inffast.obj"
	-@erase "$(INTDIR)\Inflate.obj"
	-@erase "$(INTDIR)\Inftrees.obj"
	-@erase "$(INTDIR)\Infutil.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\Trees.obj"
	-@erase "$(INTDIR)\zlibengn.obj"
	-@erase "$(INTDIR)\ZlibTool.obj"
	-@erase "$(INTDIR)\ZlibTool.pch"
	-@erase "$(INTDIR)\ZlibTool.res"
	-@erase "$(INTDIR)\ZlibTool.tlb"
	-@erase "$(INTDIR)\ZlibToolCtl.obj"
	-@erase "$(INTDIR)\ZlibToolPpg.obj"
	-@erase "$(INTDIR)\Zutil.obj"
	-@erase "$(OUTDIR)\regsvr32.trg"
	-@erase "$(OUTDIR)\ZlibTool.exp"
	-@erase "$(OUTDIR)\ZlibTool.lib"
	-@erase "$(OUTDIR)\ZlibTool.ocx"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\zlibengn" /I "..\zlib" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /c
# SUBTRACT CPP /YX /Yc /Yu
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "..\zlibengn" /I "..\zlib" /D "WIN32" /D\
 "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS"\
 /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/ZlibTool.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/ZlibTool.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/ZlibTool.pdb" /machine:I386 /def:".\ZlibTool.def"\
 /out:"$(OUTDIR)/ZlibTool.ocx" /implib:"$(OUTDIR)/ZlibTool.lib" 
DEF_FILE= \
	".\ZlibTool.def"
LINK32_OBJS= \
	"$(INTDIR)\Adler32.obj" \
	"$(INTDIR)\Deflate.obj" \
	"$(INTDIR)\Infblock.obj" \
	"$(INTDIR)\Infcodes.obj" \
	"$(INTDIR)\Inffast.obj" \
	"$(INTDIR)\Inflate.obj" \
	"$(INTDIR)\Inftrees.obj" \
	"$(INTDIR)\Infutil.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Trees.obj" \
	"$(INTDIR)\zlibengn.obj" \
	"$(INTDIR)\ZlibTool.obj" \
	"$(INTDIR)\ZlibTool.res" \
	"$(INTDIR)\ZlibToolCtl.obj" \
	"$(INTDIR)\ZlibToolPpg.obj" \
	"$(INTDIR)\Zutil.obj"

"$(OUTDIR)\ZlibTool.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Registering OLE control...
OutDir=.\Release
TargetPath=.\Release\ZlibTool.ocx
InputPath=.\Release\ZlibTool.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   regsvr32 /s /c "$(TargetPath)"
   echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg"

# End Custom Build

!ELSEIF  "$(CFG)" == "ZlibTool - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP BASE Target_Ext "ocx"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# PROP Target_Ext "ocx"
OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\ZlibTool.ocx" "$(OUTDIR)\ZlibTool.pch"\
 "$(OUTDIR)\regsvr32.trg"

CLEAN : 
	-@erase "$(INTDIR)\Adler32.obj"
	-@erase "$(INTDIR)\Deflate.obj"
	-@erase "$(INTDIR)\Infblock.obj"
	-@erase "$(INTDIR)\Infcodes.obj"
	-@erase "$(INTDIR)\Inffast.obj"
	-@erase "$(INTDIR)\Inflate.obj"
	-@erase "$(INTDIR)\Inftrees.obj"
	-@erase "$(INTDIR)\Infutil.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\Trees.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(INTDIR)\zlibengn.obj"
	-@erase "$(INTDIR)\ZlibTool.obj"
	-@erase "$(INTDIR)\ZlibTool.pch"
	-@erase "$(INTDIR)\ZlibTool.res"
	-@erase "$(INTDIR)\ZlibTool.tlb"
	-@erase "$(INTDIR)\ZlibToolCtl.obj"
	-@erase "$(INTDIR)\ZlibToolPpg.obj"
	-@erase "$(INTDIR)\Zutil.obj"
	-@erase "$(OUTDIR)\regsvr32.trg"
	-@erase "$(OUTDIR)\ZlibTool.exp"
	-@erase "$(OUTDIR)\ZlibTool.ilk"
	-@erase "$(OUTDIR)\ZlibTool.lib"
	-@erase "$(OUTDIR)\ZlibTool.ocx"
	-@erase "$(OUTDIR)\ZlibTool.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\zlibengn" /I "..\zlib" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /c
# SUBTRACT CPP /YX /Yc /Yu
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\zlibengn" /I "..\zlib" /D\
 "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_WINDLL" /D "_AFXDLL" /D\
 "_MBCS" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/ZlibTool.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/ZlibTool.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/ZlibTool.pdb" /debug /machine:I386 /def:".\ZlibTool.def"\
 /out:"$(OUTDIR)/ZlibTool.ocx" /implib:"$(OUTDIR)/ZlibTool.lib" 
DEF_FILE= \
	".\ZlibTool.def"
LINK32_OBJS= \
	"$(INTDIR)\Adler32.obj" \
	"$(INTDIR)\Deflate.obj" \
	"$(INTDIR)\Infblock.obj" \
	"$(INTDIR)\Infcodes.obj" \
	"$(INTDIR)\Inffast.obj" \
	"$(INTDIR)\Inflate.obj" \
	"$(INTDIR)\Inftrees.obj" \
	"$(INTDIR)\Infutil.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Trees.obj" \
	"$(INTDIR)\zlibengn.obj" \
	"$(INTDIR)\ZlibTool.obj" \
	"$(INTDIR)\ZlibTool.res" \
	"$(INTDIR)\ZlibToolCtl.obj" \
	"$(INTDIR)\ZlibToolPpg.obj" \
	"$(INTDIR)\Zutil.obj"

"$(OUTDIR)\ZlibTool.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Registering OLE control...
OutDir=.\Debug
TargetPath=.\Debug\ZlibTool.ocx
InputPath=.\Debug\ZlibTool.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   regsvr32 /s /c "$(TargetPath)"
   echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg"

# End Custom Build

!ELSEIF  "$(CFG)" == "ZlibTool - Win32 Unicode Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DebugU"
# PROP BASE Intermediate_Dir "DebugU"
# PROP BASE Target_Dir ""
# PROP BASE Target_Ext "ocx"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugU"
# PROP Intermediate_Dir "DebugU"
# PROP Target_Dir ""
# PROP Target_Ext "ocx"
OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
# End Custom Macros

ALL : "$(OUTDIR)\ZlibTool.ocx" "$(OUTDIR)\ZlibTool.pch"\
 "$(OUTDIR)\regsvr32.trg"

CLEAN : 
	-@erase "$(INTDIR)\Adler32.obj"
	-@erase "$(INTDIR)\Deflate.obj"
	-@erase "$(INTDIR)\Infblock.obj"
	-@erase "$(INTDIR)\Infcodes.obj"
	-@erase "$(INTDIR)\Inffast.obj"
	-@erase "$(INTDIR)\Inflate.obj"
	-@erase "$(INTDIR)\Inftrees.obj"
	-@erase "$(INTDIR)\Infutil.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\Trees.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(INTDIR)\zlibengn.obj"
	-@erase "$(INTDIR)\ZlibTool.obj"
	-@erase "$(INTDIR)\ZlibTool.pch"
	-@erase "$(INTDIR)\ZlibTool.res"
	-@erase "$(INTDIR)\ZlibTool.tlb"
	-@erase "$(INTDIR)\ZlibToolCtl.obj"
	-@erase "$(INTDIR)\ZlibToolPpg.obj"
	-@erase "$(INTDIR)\Zutil.obj"
	-@erase "$(OUTDIR)\regsvr32.trg"
	-@erase "$(OUTDIR)\ZlibTool.exp"
	-@erase "$(OUTDIR)\ZlibTool.ilk"
	-@erase "$(OUTDIR)\ZlibTool.lib"
	-@erase "$(OUTDIR)\ZlibTool.ocx"
	-@erase "$(OUTDIR)\ZlibTool.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\zlibengn" /I "..\zlib" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /c
# SUBTRACT CPP /YX /Yc /Yu
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\zlibengn" /I "..\zlib" /D\
 "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_WINDLL" /D\
 "_AFXDLL" /D "_MBCS" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\DebugU/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/ZlibTool.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/ZlibTool.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/ZlibTool.pdb" /debug /machine:I386 /def:".\ZlibTool.def"\
 /out:"$(OUTDIR)/ZlibTool.ocx" /implib:"$(OUTDIR)/ZlibTool.lib" 
DEF_FILE= \
	".\ZlibTool.def"
LINK32_OBJS= \
	"$(INTDIR)\Adler32.obj" \
	"$(INTDIR)\Deflate.obj" \
	"$(INTDIR)\Infblock.obj" \
	"$(INTDIR)\Infcodes.obj" \
	"$(INTDIR)\Inffast.obj" \
	"$(INTDIR)\Inflate.obj" \
	"$(INTDIR)\Inftrees.obj" \
	"$(INTDIR)\Infutil.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Trees.obj" \
	"$(INTDIR)\zlibengn.obj" \
	"$(INTDIR)\ZlibTool.obj" \
	"$(INTDIR)\ZlibTool.res" \
	"$(INTDIR)\ZlibToolCtl.obj" \
	"$(INTDIR)\ZlibToolPpg.obj" \
	"$(INTDIR)\Zutil.obj"

"$(OUTDIR)\ZlibTool.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Registering OLE control...
OutDir=.\DebugU
TargetPath=.\DebugU\ZlibTool.ocx
InputPath=.\DebugU\ZlibTool.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   regsvr32 /s /c "$(TargetPath)"
   echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg"

# End Custom Build

!ELSEIF  "$(CFG)" == "ZlibTool - Win32 Unicode Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseU"
# PROP BASE Intermediate_Dir "ReleaseU"
# PROP BASE Target_Dir ""
# PROP BASE Target_Ext "ocx"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseU"
# PROP Intermediate_Dir "ReleaseU"
# PROP Target_Dir ""
# PROP Target_Ext "ocx"
OUTDIR=.\ReleaseU
INTDIR=.\ReleaseU
# Begin Custom Macros
OutDir=.\ReleaseU
# End Custom Macros

ALL : "$(OUTDIR)\ZlibTool.ocx" "$(OUTDIR)\ZlibTool.pch"\
 "$(OUTDIR)\regsvr32.trg"

CLEAN : 
	-@erase "$(INTDIR)\Adler32.obj"
	-@erase "$(INTDIR)\Deflate.obj"
	-@erase "$(INTDIR)\Infblock.obj"
	-@erase "$(INTDIR)\Infcodes.obj"
	-@erase "$(INTDIR)\Inffast.obj"
	-@erase "$(INTDIR)\Inflate.obj"
	-@erase "$(INTDIR)\Inftrees.obj"
	-@erase "$(INTDIR)\Infutil.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\Trees.obj"
	-@erase "$(INTDIR)\zlibengn.obj"
	-@erase "$(INTDIR)\ZlibTool.obj"
	-@erase "$(INTDIR)\ZlibTool.pch"
	-@erase "$(INTDIR)\ZlibTool.res"
	-@erase "$(INTDIR)\ZlibTool.tlb"
	-@erase "$(INTDIR)\ZlibToolCtl.obj"
	-@erase "$(INTDIR)\ZlibToolPpg.obj"
	-@erase "$(INTDIR)\Zutil.obj"
	-@erase "$(OUTDIR)\regsvr32.trg"
	-@erase "$(OUTDIR)\ZlibTool.exp"
	-@erase "$(OUTDIR)\ZlibTool.lib"
	-@erase "$(OUTDIR)\ZlibTool.ocx"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\zlibengn" /I "..\zlib" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /c
# SUBTRACT CPP /YX /Yc /Yu
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "..\zlibengn" /I "..\zlib" /D "WIN32" /D\
 "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_WINDLL" /D "_AFXDLL" /D\
 "_MBCS" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\ReleaseU/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/ZlibTool.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/ZlibTool.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/ZlibTool.pdb" /machine:I386 /def:".\ZlibTool.def"\
 /out:"$(OUTDIR)/ZlibTool.ocx" /implib:"$(OUTDIR)/ZlibTool.lib" 
DEF_FILE= \
	".\ZlibTool.def"
LINK32_OBJS= \
	"$(INTDIR)\Adler32.obj" \
	"$(INTDIR)\Deflate.obj" \
	"$(INTDIR)\Infblock.obj" \
	"$(INTDIR)\Infcodes.obj" \
	"$(INTDIR)\Inffast.obj" \
	"$(INTDIR)\Inflate.obj" \
	"$(INTDIR)\Inftrees.obj" \
	"$(INTDIR)\Infutil.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Trees.obj" \
	"$(INTDIR)\zlibengn.obj" \
	"$(INTDIR)\ZlibTool.obj" \
	"$(INTDIR)\ZlibTool.res" \
	"$(INTDIR)\ZlibToolCtl.obj" \
	"$(INTDIR)\ZlibToolPpg.obj" \
	"$(INTDIR)\Zutil.obj"

"$(OUTDIR)\ZlibTool.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Registering OLE control...
OutDir=.\ReleaseU
TargetPath=.\ReleaseU\ZlibTool.ocx
InputPath=.\ReleaseU\ZlibTool.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   regsvr32 /s /c "$(TargetPath)"
   echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg"

# End Custom Build

!ENDIF 

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

################################################################################
# Begin Target

# Name "ZlibTool - Win32 Release"
# Name "ZlibTool - Win32 Debug"
# Name "ZlibTool - Win32 Unicode Debug"
# Name "ZlibTool - Win32 Unicode Release"

!IF  "$(CFG)" == "ZlibTool - Win32 Release"

!ELSEIF  "$(CFG)" == "ZlibTool - Win32 Debug"

!ELSEIF  "$(CFG)" == "ZlibTool - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "ZlibTool - Win32 Unicode Release"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "ZlibTool - Win32 Release"

!ELSEIF  "$(CFG)" == "ZlibTool - Win32 Debug"

!ELSEIF  "$(CFG)" == "ZlibTool - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "ZlibTool - Win32 Unicode Release"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	"..\zlibtool\stdafx.h"\
	

!IF  "$(CFG)" == "ZlibTool - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /I "..\zlibengn" /I "..\zlib" /D "WIN32" /D\
 "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS"\
 /Fp"$(INTDIR)/ZlibTool.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\ZlibTool.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "ZlibTool - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\zlibengn" /I "..\zlib" /D\
 "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_WINDLL" /D "_AFXDLL" /D\
 "_MBCS" /Fp"$(INTDIR)/ZlibTool.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\ZlibTool.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "ZlibTool - Win32 Unicode Debug"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\zlibengn" /I "..\zlib" /D\
 "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_WINDLL" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/ZlibTool.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\ZlibTool.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "ZlibTool - Win32 Unicode Release"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /I "..\zlibengn" /I "..\zlib" /D "WIN32" /D\
 "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_WINDLL" /D "_AFXDLL" /D\
 "_MBCS" /Fp"$(INTDIR)/ZlibTool.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\ZlibTool.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ZlibTool.cpp
DEP_CPP_ZLIBT=\
	"..\zlibtool\stdafx.h"\
	".\ZlibTool.h"\
	

!IF  "$(CFG)" == "ZlibTool - Win32 Release"


"$(INTDIR)\ZlibTool.obj" : $(SOURCE) $(DEP_CPP_ZLIBT) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "ZlibTool - Win32 Debug"


"$(INTDIR)\ZlibTool.obj" : $(SOURCE) $(DEP_CPP_ZLIBT) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "ZlibTool - Win32 Unicode Debug"


"$(INTDIR)\ZlibTool.obj" : $(SOURCE) $(DEP_CPP_ZLIBT) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "ZlibTool - Win32 Unicode Release"


"$(INTDIR)\ZlibTool.obj" : $(SOURCE) $(DEP_CPP_ZLIBT) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ZlibTool.def

!IF  "$(CFG)" == "ZlibTool - Win32 Release"

!ELSEIF  "$(CFG)" == "ZlibTool - Win32 Debug"

!ELSEIF  "$(CFG)" == "ZlibTool - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "ZlibTool - Win32 Unicode Release"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ZlibTool.rc

!IF  "$(CFG)" == "ZlibTool - Win32 Release"

DEP_RSC_ZLIBTO=\
	".\ZlibTool.ico"\
	".\ZlibToolCtl.bmp"\
	
NODEP_RSC_ZLIBTO=\
	".\Release\ZlibTool.tlb"\
	

"$(INTDIR)\ZlibTool.res" : $(SOURCE) $(DEP_RSC_ZLIBTO) "$(INTDIR)"\
 "$(INTDIR)\ZlibTool.tlb"
   $(RSC) /l 0x409 /fo"$(INTDIR)/ZlibTool.res" /i "Release" /d "NDEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "ZlibTool - Win32 Debug"

DEP_RSC_ZLIBTO=\
	".\Debug\ZlibTool.tlb"\
	".\ZlibTool.ico"\
	".\ZlibToolCtl.bmp"\
	

"$(INTDIR)\ZlibTool.res" : $(SOURCE) $(DEP_RSC_ZLIBTO) "$(INTDIR)"\
 "$(INTDIR)\ZlibTool.tlb"
   $(RSC) /l 0x409 /fo"$(INTDIR)/ZlibTool.res" /i "Debug" /d "_DEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "ZlibTool - Win32 Unicode Debug"

DEP_RSC_ZLIBTO=\
	".\ZlibTool.ico"\
	".\ZlibToolCtl.bmp"\
	
NODEP_RSC_ZLIBTO=\
	".\DebugU\ZlibTool.tlb"\
	

"$(INTDIR)\ZlibTool.res" : $(SOURCE) $(DEP_RSC_ZLIBTO) "$(INTDIR)"\
 "$(INTDIR)\ZlibTool.tlb"
   $(RSC) /l 0x409 /fo"$(INTDIR)/ZlibTool.res" /i "DebugU" /d "_DEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "ZlibTool - Win32 Unicode Release"

DEP_RSC_ZLIBTO=\
	".\ZlibTool.ico"\
	".\ZlibToolCtl.bmp"\
	
NODEP_RSC_ZLIBTO=\
	".\ReleaseU\ZlibTool.tlb"\
	

"$(INTDIR)\ZlibTool.res" : $(SOURCE) $(DEP_RSC_ZLIBTO) "$(INTDIR)"\
 "$(INTDIR)\ZlibTool.tlb"
   $(RSC) /l 0x409 /fo"$(INTDIR)/ZlibTool.res" /i "ReleaseU" /d "NDEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ZlibTool.odl

!IF  "$(CFG)" == "ZlibTool - Win32 Release"


"$(OUTDIR)\ZlibTool.tlb" : $(SOURCE) "$(OUTDIR)"
   $(MTL) /nologo /D "NDEBUG" /tlb "$(OUTDIR)/ZlibTool.tlb" /win32 $(SOURCE)


!ELSEIF  "$(CFG)" == "ZlibTool - Win32 Debug"


"$(OUTDIR)\ZlibTool.tlb" : $(SOURCE) "$(OUTDIR)"
   $(MTL) /nologo /D "_DEBUG" /tlb "$(OUTDIR)/ZlibTool.tlb" /win32 $(SOURCE)


!ELSEIF  "$(CFG)" == "ZlibTool - Win32 Unicode Debug"


"$(OUTDIR)\ZlibTool.tlb" : $(SOURCE) "$(OUTDIR)"
   $(MTL) /nologo /D "_DEBUG" /tlb "$(OUTDIR)/ZlibTool.tlb" /win32 $(SOURCE)


!ELSEIF  "$(CFG)" == "ZlibTool - Win32 Unicode Release"


"$(OUTDIR)\ZlibTool.tlb" : $(SOURCE) "$(OUTDIR)"
   $(MTL) /nologo /D "NDEBUG" /tlb "$(OUTDIR)/ZlibTool.tlb" /win32 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ZlibToolCtl.cpp
DEP_CPP_ZLIBTOO=\
	"..\zlib\zconf.h"\
	"..\zlib\zlib.h"\
	"..\zlibengn\zlibengn.h"\
	"..\zlibtool\stdafx.h"\
	".\ZlibTool.h"\
	".\ZlibToolCtl.h"\
	".\ZlibToolPpg.h"\
	

!IF  "$(CFG)" == "ZlibTool - Win32 Release"


"$(INTDIR)\ZlibToolCtl.obj" : $(SOURCE) $(DEP_CPP_ZLIBTOO) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "ZlibTool - Win32 Debug"


"$(INTDIR)\ZlibToolCtl.obj" : $(SOURCE) $(DEP_CPP_ZLIBTOO) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "ZlibTool - Win32 Unicode Debug"


"$(INTDIR)\ZlibToolCtl.obj" : $(SOURCE) $(DEP_CPP_ZLIBTOO) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "ZlibTool - Win32 Unicode Release"


"$(INTDIR)\ZlibToolCtl.obj" : $(SOURCE) $(DEP_CPP_ZLIBTOO) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ZlibToolPpg.cpp
DEP_CPP_ZLIBTOOL=\
	"..\zlibtool\stdafx.h"\
	".\ZlibTool.h"\
	".\ZlibToolPpg.h"\
	

!IF  "$(CFG)" == "ZlibTool - Win32 Release"


"$(INTDIR)\ZlibToolPpg.obj" : $(SOURCE) $(DEP_CPP_ZLIBTOOL) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "ZlibTool - Win32 Debug"


"$(INTDIR)\ZlibToolPpg.obj" : $(SOURCE) $(DEP_CPP_ZLIBTOOL) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "ZlibTool - Win32 Unicode Debug"


"$(INTDIR)\ZlibToolPpg.obj" : $(SOURCE) $(DEP_CPP_ZLIBTOOL) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "ZlibTool - Win32 Unicode Release"


"$(INTDIR)\ZlibToolPpg.obj" : $(SOURCE) $(DEP_CPP_ZLIBTOOL) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=..\Zlib\Deflate.c
DEP_CPP_DEFLA=\
	"..\Zlib\deflate.h"\
	"..\zlib\zconf.h"\
	"..\zlib\zlib.h"\
	"..\Zlib\zutil.h"\
	

!IF  "$(CFG)" == "ZlibTool - Win32 Release"


"$(INTDIR)\Deflate.obj" : $(SOURCE) $(DEP_CPP_DEFLA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ZlibTool - Win32 Debug"


"$(INTDIR)\Deflate.obj" : $(SOURCE) $(DEP_CPP_DEFLA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ZlibTool - Win32 Unicode Debug"


"$(INTDIR)\Deflate.obj" : $(SOURCE) $(DEP_CPP_DEFLA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ZlibTool - Win32 Unicode Release"


"$(INTDIR)\Deflate.obj" : $(SOURCE) $(DEP_CPP_DEFLA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=..\Zlib\Inflate.c
DEP_CPP_INFLA=\
	"..\Zlib\infblock.h"\
	"..\zlib\zconf.h"\
	"..\zlib\zlib.h"\
	"..\Zlib\zutil.h"\
	

!IF  "$(CFG)" == "ZlibTool - Win32 Release"


"$(INTDIR)\Inflate.obj" : $(SOURCE) $(DEP_CPP_INFLA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ZlibTool - Win32 Debug"


"$(INTDIR)\Inflate.obj" : $(SOURCE) $(DEP_CPP_INFLA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ZlibTool - Win32 Unicode Debug"


"$(INTDIR)\Inflate.obj" : $(SOURCE) $(DEP_CPP_INFLA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ZlibTool - Win32 Unicode Release"


"$(INTDIR)\Inflate.obj" : $(SOURCE) $(DEP_CPP_INFLA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=..\Zlib\Zutil.c
DEP_CPP_ZUTIL=\
	"..\zlib\zconf.h"\
	"..\zlib\zlib.h"\
	"..\Zlib\zutil.h"\
	

!IF  "$(CFG)" == "ZlibTool - Win32 Release"


"$(INTDIR)\Zutil.obj" : $(SOURCE) $(DEP_CPP_ZUTIL) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ZlibTool - Win32 Debug"


"$(INTDIR)\Zutil.obj" : $(SOURCE) $(DEP_CPP_ZUTIL) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ZlibTool - Win32 Unicode Debug"


"$(INTDIR)\Zutil.obj" : $(SOURCE) $(DEP_CPP_ZUTIL) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ZlibTool - Win32 Unicode Release"


"$(INTDIR)\Zutil.obj" : $(SOURCE) $(DEP_CPP_ZUTIL) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=..\Zlib\Adler32.c
DEP_CPP_ADLER=\
	"..\zlib\zconf.h"\
	"..\zlib\zlib.h"\
	

!IF  "$(CFG)" == "ZlibTool - Win32 Release"


"$(INTDIR)\Adler32.obj" : $(SOURCE) $(DEP_CPP_ADLER) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ZlibTool - Win32 Debug"


"$(INTDIR)\Adler32.obj" : $(SOURCE) $(DEP_CPP_ADLER) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ZlibTool - Win32 Unicode Debug"


"$(INTDIR)\Adler32.obj" : $(SOURCE) $(DEP_CPP_ADLER) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ZlibTool - Win32 Unicode Release"


"$(INTDIR)\Adler32.obj" : $(SOURCE) $(DEP_CPP_ADLER) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=..\Zlib\Trees.c
DEP_CPP_TREES=\
	"..\Zlib\deflate.h"\
	"..\zlib\zconf.h"\
	"..\zlib\zlib.h"\
	"..\Zlib\zutil.h"\
	

!IF  "$(CFG)" == "ZlibTool - Win32 Release"


"$(INTDIR)\Trees.obj" : $(SOURCE) $(DEP_CPP_TREES) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ZlibTool - Win32 Debug"


"$(INTDIR)\Trees.obj" : $(SOURCE) $(DEP_CPP_TREES) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ZlibTool - Win32 Unicode Debug"


"$(INTDIR)\Trees.obj" : $(SOURCE) $(DEP_CPP_TREES) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ZlibTool - Win32 Unicode Release"


"$(INTDIR)\Trees.obj" : $(SOURCE) $(DEP_CPP_TREES) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=..\Zlib\Infblock.c
DEP_CPP_INFBL=\
	"..\Zlib\infblock.h"\
	"..\Zlib\infcodes.h"\
	"..\Zlib\inftrees.h"\
	"..\Zlib\infutil.h"\
	"..\zlib\zconf.h"\
	"..\zlib\zlib.h"\
	"..\Zlib\zutil.h"\
	

!IF  "$(CFG)" == "ZlibTool - Win32 Release"


"$(INTDIR)\Infblock.obj" : $(SOURCE) $(DEP_CPP_INFBL) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ZlibTool - Win32 Debug"


"$(INTDIR)\Infblock.obj" : $(SOURCE) $(DEP_CPP_INFBL) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ZlibTool - Win32 Unicode Debug"


"$(INTDIR)\Infblock.obj" : $(SOURCE) $(DEP_CPP_INFBL) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ZlibTool - Win32 Unicode Release"


"$(INTDIR)\Infblock.obj" : $(SOURCE) $(DEP_CPP_INFBL) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=..\Zlib\Inftrees.c
DEP_CPP_INFTR=\
	"..\Zlib\inftrees.h"\
	"..\zlib\zconf.h"\
	"..\zlib\zlib.h"\
	"..\Zlib\zutil.h"\
	

!IF  "$(CFG)" == "ZlibTool - Win32 Release"


"$(INTDIR)\Inftrees.obj" : $(SOURCE) $(DEP_CPP_INFTR) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ZlibTool - Win32 Debug"


"$(INTDIR)\Inftrees.obj" : $(SOURCE) $(DEP_CPP_INFTR) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ZlibTool - Win32 Unicode Debug"


"$(INTDIR)\Inftrees.obj" : $(SOURCE) $(DEP_CPP_INFTR) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ZlibTool - Win32 Unicode Release"


"$(INTDIR)\Inftrees.obj" : $(SOURCE) $(DEP_CPP_INFTR) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=..\Zlib\Infcodes.c
DEP_CPP_INFCO=\
	"..\Zlib\infblock.h"\
	"..\Zlib\infcodes.h"\
	"..\Zlib\inffast.h"\
	"..\Zlib\inftrees.h"\
	"..\Zlib\infutil.h"\
	"..\zlib\zconf.h"\
	"..\zlib\zlib.h"\
	"..\Zlib\zutil.h"\
	

!IF  "$(CFG)" == "ZlibTool - Win32 Release"


"$(INTDIR)\Infcodes.obj" : $(SOURCE) $(DEP_CPP_INFCO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ZlibTool - Win32 Debug"


"$(INTDIR)\Infcodes.obj" : $(SOURCE) $(DEP_CPP_INFCO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ZlibTool - Win32 Unicode Debug"


"$(INTDIR)\Infcodes.obj" : $(SOURCE) $(DEP_CPP_INFCO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ZlibTool - Win32 Unicode Release"


"$(INTDIR)\Infcodes.obj" : $(SOURCE) $(DEP_CPP_INFCO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=..\Zlib\Infutil.c
DEP_CPP_INFUT=\
	"..\Zlib\infblock.h"\
	"..\Zlib\infcodes.h"\
	"..\Zlib\inftrees.h"\
	"..\Zlib\infutil.h"\
	"..\zlib\zconf.h"\
	"..\zlib\zlib.h"\
	"..\Zlib\zutil.h"\
	

!IF  "$(CFG)" == "ZlibTool - Win32 Release"


"$(INTDIR)\Infutil.obj" : $(SOURCE) $(DEP_CPP_INFUT) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ZlibTool - Win32 Debug"


"$(INTDIR)\Infutil.obj" : $(SOURCE) $(DEP_CPP_INFUT) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ZlibTool - Win32 Unicode Debug"


"$(INTDIR)\Infutil.obj" : $(SOURCE) $(DEP_CPP_INFUT) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ZlibTool - Win32 Unicode Release"


"$(INTDIR)\Infutil.obj" : $(SOURCE) $(DEP_CPP_INFUT) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=..\Zlib\Inffast.c
DEP_CPP_INFFA=\
	"..\Zlib\infblock.h"\
	"..\Zlib\infcodes.h"\
	"..\Zlib\inffast.h"\
	"..\Zlib\inftrees.h"\
	"..\Zlib\infutil.h"\
	"..\zlib\zconf.h"\
	"..\zlib\zlib.h"\
	"..\Zlib\zutil.h"\
	

!IF  "$(CFG)" == "ZlibTool - Win32 Release"


"$(INTDIR)\Inffast.obj" : $(SOURCE) $(DEP_CPP_INFFA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ZlibTool - Win32 Debug"


"$(INTDIR)\Inffast.obj" : $(SOURCE) $(DEP_CPP_INFFA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ZlibTool - Win32 Unicode Debug"


"$(INTDIR)\Inffast.obj" : $(SOURCE) $(DEP_CPP_INFFA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ZlibTool - Win32 Unicode Release"


"$(INTDIR)\Inffast.obj" : $(SOURCE) $(DEP_CPP_INFFA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=..\zlibengn\zlibengn.cpp
DEP_CPP_ZLIBE=\
	"..\zlib\zconf.h"\
	"..\zlib\zlib.h"\
	"..\zlibengn\zlibengn.h"\
	

!IF  "$(CFG)" == "ZlibTool - Win32 Release"


"$(INTDIR)\zlibengn.obj" : $(SOURCE) $(DEP_CPP_ZLIBE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ZlibTool - Win32 Debug"


"$(INTDIR)\zlibengn.obj" : $(SOURCE) $(DEP_CPP_ZLIBE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ZlibTool - Win32 Unicode Debug"


"$(INTDIR)\zlibengn.obj" : $(SOURCE) $(DEP_CPP_ZLIBE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ZlibTool - Win32 Unicode Release"


"$(INTDIR)\zlibengn.obj" : $(SOURCE) $(DEP_CPP_ZLIBE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
