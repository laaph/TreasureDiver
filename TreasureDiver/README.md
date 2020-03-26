
Hello! This is the source code for the game "Treasure Diver".

Despite coming with an XCode project, this does not compile cleanly under XCode. To
fix this, set the options such that it copies libBearLibTerminal.dylib and Symbola613.ttf
to the Product destination.

For compiling on Windows, you will need the appropriate version of 
libBearLibTerminal from http://foo.wyrd.name/en:bearlibterminal .  The version I used 
is also included in the source code.

The Mac  and Linux versions of BearLibTerminal is included with the source code here.

I didn't make a Makefile, the way I compiled it on my mac

gcc *.c -o TreasureDiver  -L. -lBearLibTerminal 

When I compiled it on Linux, I found this not working. After much hair pulling, I found this to work.

gcc *.c -L. -l:libBearLibTerminal.so  -Wl,-rpath=.

The -l:libBearLibTerminal.so specifies the library by exact name. For some reason I could not 
get it to find the library otherwise. The -Wl,rpath=. specifies where the dynamic library lives.
BearLibTerminal is distributed as a shared library, however, I don't want to clog my /usr/lib 
directory with even more libraries.
