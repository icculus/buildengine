BUILD binaries for Win32 systems.

These binaries are BETA quality. Expect crashes.

The notable annoyances:
1) No sound.
2) No networking. Boohoo.   :)

Bug reports to Ryan C. Gordon (icculus@clutteredmind.org).

I've only tested this briefly on a Windows 98 (second edition) box, and even
 more briefly on WinNT 4.0 (Service Pack 6) under vmWare. YMMV.

Please feel free to report success and failure on different Windows platforms.
 This, obviously, will not work on a Windows 3.1 platform, for that one
 sadistic guy who's going to try it.  :)

This does not play Duke3D, Shadow Warrior, Blood, or any other game but Ken's
 test game ("KenBuild"). It can sort of edit Duke3D maps, but the DOS-based
 BUILD.EXE on your commercial Duke CD-ROM is better suited. You can also check
 out Mapster (http://mapster-rtcm.totalconversions.com).

Do NOT harrass Ken Silverman about these binaries. He did not compile them.
 He did not release them. He did not port this to Windows and he does NOT want
 to hear from YOU.

Here is his license text stuff:

// "Build Engine & Tools" Copyright (c) 1993-1997 Ken Silverman
// Ken Silverman's official web site: "http://www.advsys.net/ken"
// See the included license file "BUILDLIC.TXT" for license info.
// This file has been modified from Ken Silverman's original release


This code also relies on Simple Directmedia Layer (SDL) for graphics and input.
 This excellent cross-platform library was put together by Sam Lantinga, and
 is available to us under the LGPL license. That means that I can use it
 freely, but I have to point you to a place where you can get the source
 for yourself (the DLL is in this archive, though, so this is strictly FYI):

   http://www.libsdl.org/


The source code of the Build port (along with screenshots of it running) is
available from http://www.icculus.org/

Feel free to send me comments, complaints, suggestions, and donations.

Enjoy!

--ryan. (icculus@clutteredmind.org)


CHANGELOG of win32 binary releases:
02192001 - first binary release.
02202001 - Fixed rendering bug in 2D editor, enabled optimizations,
           disabled debugging. Disabled console window.
02212001 - Fixed too-slow gameplay (Thanks, Matt!).
02222001 - Ported back to DOS/386...since so much code got touched, it's
           worth putting out a new binary to make sure nothing broke.
02262001 - Fixed WinNT/Win2k problems. Should run now. YMMV. Automated
           packaging system, but not sure if everything is getting included.
           time will tell.
05272001 - Built with Watcom C 11.0, so the things work under WinNT and Win2000
           without editing the EXE. Updated to SDL 1.2.0. Can sorta edit Duke3D
           maps now (see README) Lots of other non-platform-specific fixes and
           updates. See the CHANGELOG.

// end of README-win32bins.txt ...


