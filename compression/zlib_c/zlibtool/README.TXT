The source code subdirectories that accompany this article are:

  o  ZlibTool   The source code for the Zlib OCX.  To build the
                OCX from scratch, just open the MAK file as a project
                and build either the debug or release version of
                the OCX.  Note that I deleted some of the project
                files to save space, such as the CLW database, but
                they can all be created if needed.

  o  Ocx        This file contains the OCX, support DLLs, and the
                registration program.  Programs like Delphi and
                VB can register the DLL on their own, but if you
                want to, you can register it from the command line
                like this: REGSVR32 ZLIBTOOL.OCX.  If you don't have
                up to date versions of the DLLs, you can copy them
                to your WIN95\SYSTEM directory.

  o  Delphi     A 32 bit Delphi 2.0 test program that uses the OCX.
                The executable is included.

  o  ZlibEngn   The source code and header file for the Zlib engine
                wrapper class.

  o  Zlib       The Source code for Zlib 1.0.  This is exactly the
                same source code I downloaded from the Zlib distribution
                site.  I don't include the make files, documentation,
                etc.  They are available at the sites discussed in the
                article.

  o  ZlibTest   The console test program that uses the wrapper class
                to compress files.

Mark Nelson
Tiny Software
markn@tiny.com
http://web2.airmail.net/markn

