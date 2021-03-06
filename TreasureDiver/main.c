//
//  main.c
//  TreasureDiver
//
//  Created by Jethro on 2/22/20.
//  Copyright © 2020 Finley. All rights reserved.
//
#include <string.h>
#include <stdio.h>

#include "BearLibTerminal.h"
#include "water_scene.h"
#include "player_data.h"
#include "attract_screen.h"


#if defined(_WIN32)
  #include <windows.h>
#elif defined(__APPLE__)
  #include <mach-o/dyld.h>
#endif

int main(int argc, const char * argv[]) {

#if defined(__APPLE__)
    char path[1024];
    uint32_t size = sizeof(path);
    if (_NSGetExecutablePath(path, &size) == 0) {
        char *lastsep = strrchr(path, '/');
        path[strlen(path) - strlen(lastsep)] = '\0';
        
        char options1[1024] = "window.size=39x25; font:";
        char options2[] = "/Symbola613.ttf, size=18; window.title='Treasure Diver'";

        strcat(options1, path);
        strcat(options1, options2);

        terminal_open();
        terminal_set(options1);
    }
    else {
        fprintf(stderr, "buffer too small; need size %u\n", size);
        exit(1);
    }

#else
    terminal_open();
    terminal_set("window.size=39x25; font:Symbola613.ttf, size=24; window.title='Treasure Diver'");
#endif


    main_setup();
}
