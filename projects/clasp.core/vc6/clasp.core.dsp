# Microsoft Developer Studio Project File - Name="clasp.core" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=clasp.core - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "clasp.core.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "clasp.core.mak" CFG="clasp.core - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "clasp.core - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "clasp.core - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "clasp.core - Win32 Debug pseudoUNIX" (based on "Win32 (x86) Static Library")
!MESSAGE "clasp.core - Win32 Debug NoRecls" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "clasp.core - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I ".." /I "../../../include" /I "$(RECLS_ROOT)/include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# SUBTRACT CPP /Fr
# ADD BASE RSC /l 0xc09 /d "NDEBUG"
# ADD RSC /l 0xc09 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../../../lib/systemtools.clasp.0.core.vc6.lib"

!ELSEIF  "$(CFG)" == "clasp.core - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I ".." /I "../../../include" /I "$(RECLS_ROOT)/include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /GZ /c
# SUBTRACT CPP /Fr
# ADD BASE RSC /l 0xc09 /d "_DEBUG"
# ADD RSC /l 0xc09 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../../../lib/systemtools.clasp.0.core.vc6.debug.lib"

!ELSEIF  "$(CFG)" == "clasp.core - Win32 Debug pseudoUNIX"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DebugUNIX"
# PROP BASE Intermediate_Dir "DebugUNIX"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugUNIX"
# PROP Intermediate_Dir "DebugUNIX"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /I ".." /I "../../../include" /I "$(RECLS_ROOT)/include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I ".." /I "../../../include" /I "$(RECLS_ROOT)/include" /I "$(UNIXEM)/include" /D "UNIX" /D "_DEBUG" /D "_WINDOWS" /YX /FD /GZ /c
# SUBTRACT CPP /Fr
# ADD BASE RSC /l 0xc09 /d "_DEBUG"
# ADD RSC /l 0xc09 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"../../../lib/systemtools.clasp.0.core.debug.lib"
# ADD LIB32 /nologo /out:"../../../lib/systemtools.clasp.0.core.vc6.unix.debug.lib"

!ELSEIF  "$(CFG)" == "clasp.core - Win32 Debug NoRecls"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DebugNoRecls"
# PROP BASE Intermediate_Dir "DebugNoRecls"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugNoRecls"
# PROP Intermediate_Dir "DebugNoRecls"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /I ".." /I "../../../include" /I "$(RECLS_ROOT)/include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I ".." /I "../../../include" /I "$(RECLS_ROOT)/include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /GZ /c
# SUBTRACT CPP /Fr
# ADD BASE RSC /l 0xc09 /d "_DEBUG"
# ADD RSC /l 0xc09 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"../../../lib/systemtools.clasp.0.core.vc6.debug.lib"
# ADD LIB32 /nologo /out:"../../../lib/systemtools.clasp.0.core.norecls.vc6.debug.lib"

!ENDIF 

# Begin Target

# Name "clasp.core - Win32 Release"
# Name "clasp.core - Win32 Debug"
# Name "clasp.core - Win32 Debug pseudoUNIX"
# Name "clasp.core - Win32 Debug NoRecls"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\..\src\clasp.api.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\clasp.core.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\clasp.diagnostics.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\clasp.memory.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\clasp.string.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\clasp.usage.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\clasp.usage.FILE.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "recls Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE="$(RECLS_ROOT)\include\recls\internal\compiler.h"
# End Source File
# Begin Source File

SOURCE="$(RECLS_ROOT)\include\recls\internal\compiler_msvc.h"
# End Source File
# Begin Source File

SOURCE="$(RECLS_ROOT)\include\recls\internal\language.h"
# End Source File
# Begin Source File

SOURCE="$(RECLS_ROOT)\include\recls\internal\platform.h"
# End Source File
# Begin Source File

SOURCE="$(RECLS_ROOT)\include\recls\internal\platform_types.h"
# End Source File
# Begin Source File

SOURCE="$(RECLS_ROOT)\include\recls\recls.h"
# End Source File
# Begin Source File

SOURCE="$(RECLS_ROOT)\include\recls\internal\recls_filesize.h"
# End Source File
# Begin Source File

SOURCE="$(RECLS_ROOT)\include\recls\internal\recls_time.h"
# End Source File
# Begin Source File

SOURCE="$(RECLS_ROOT)\include\recls\internal\retcodes.h"
# End Source File
# Begin Source File

SOURCE="$(RECLS_ROOT)\include\recls\unix.h"
# End Source File
# End Group
# Begin Group "SystemTools::CLASP Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\include\clasp\clasp.h
# End Source File
# End Group
# Begin Group "UNIXem Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE="$(UNIXEM)\include\unistd.h"
# End Source File
# Begin Source File

SOURCE="$(UNIXEM)\include\unixem\unistd.h"
# End Source File
# Begin Source File

SOURCE="$(UNIXEM)\include\unixem\unixem.h"
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\..\src\clasp.internal.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\..\src\CLASP.Split.Notes.txt
# End Source File
# End Target
# End Project
