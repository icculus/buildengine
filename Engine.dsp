# Microsoft Developer Studio Project File - Name="Engine" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=Engine - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Engine.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Engine.mak" CFG="Engine - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Engine - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "Engine - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Engine - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseVC6"
# PROP Intermediate_Dir "ReleaseVC6"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /GX /Ot /Ow /Oi /Op /Oy /Ob1 /I "SDL-1.2.5\include" /D "_LIB" /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "USE_I386_ASM" /D "PLATFORM_WIN32" /D "UDP_NETWORKING" /YX /J /FD /c
# SUBTRACT CPP /Oa /Og /Os
# ADD BASE RSC /l 0xc09 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "Engine - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugVC6"
# PROP Intermediate_Dir "DebugVC6"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /Gm /GX /ZI /Od /I "SDL-1.2.5\include" /D "_LIB" /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "USE_I386_ASM" /D "PLATFORM_WIN32" /D "UDP_NETWORKING" /FR /YX /J /FD /GZ /c
# ADD BASE RSC /l 0xc09 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "Engine - Win32 Release"
# Name "Engine - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=a_nasm.asm

!IF  "$(CFG)" == "Engine - Win32 Release"

# Begin Custom Build
TargetDir=.\ReleaseVC6
InputPath=a_nasm.asm

"$(TargetDir)\a_nasm.obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nasmw.exe -f win32 -DC_IDENTIFIERS_UNDERSCORED -o $(TargetDir)\a_nasm.obj $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "Engine - Win32 Debug"

# Begin Custom Build
TargetDir=.\DebugVC6
InputPath=a_nasm.asm

"$(TargetDir)\a_nasm.obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nasmw.exe -f win32 -DC_IDENTIFIERS_UNDERSCORED -o $(TargetDir)\a_nasm.obj $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\a_visualc.c
# End Source File
# Begin Source File

SOURCE=.\cache1d.c
# End Source File
# Begin Source File

SOURCE=.\engine.c
# End Source File
# Begin Source File

SOURCE=.\mmulti.c
# End Source File
# Begin Source File

SOURCE=.\pragmas.c
# End Source File
# Begin Source File

SOURCE=.\sdl_driver.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\a.h
# End Source File
# Begin Source File

SOURCE=.\bstub.h
# End Source File
# Begin Source File

SOURCE=.\build.h
# End Source File
# Begin Source File

SOURCE=.\buildgl.h
# End Source File
# Begin Source File

SOURCE=.\buildperl.h
# End Source File
# Begin Source File

SOURCE=.\cache1d.h
# End Source File
# Begin Source File

SOURCE=.\display.h
# End Source File
# Begin Source File

SOURCE=.\engine.h
# End Source File
# Begin Source File

SOURCE=.\names.h
# End Source File
# Begin Source File

SOURCE=.\platform.h
# End Source File
# Begin Source File

SOURCE=.\pragmas.h
# End Source File
# Begin Source File

SOURCE=.\ves2.h
# End Source File
# Begin Source File

SOURCE=.\win32_compat.h
# End Source File
# End Group
# End Target
# End Project
