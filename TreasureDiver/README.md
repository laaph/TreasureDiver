
Hello! This is the source code for the game "Treasure Diver".

Despite coming with an XCode project, this does not compile cleanly under XCode. To
fix this, set the options such that it copies libBearLibTerminal.dylib and Symbola613.ttf
to the Product destination.

For compiling on Linux or Windows, you will likely need the appropriate version of 
libBearLibTerminal from http://foo.wyrd.name/en:bearlibterminal . The Mac version is
included with the source code here.

I didn't make a Makefile, the way I compiled it was 

gcc -o TreasureDiver  -L. -lBearLibTerminal *.h *.c
