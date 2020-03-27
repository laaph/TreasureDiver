//
//  attract_screen.c
//  TreasureDiver
//
//  Created by Jethro on 2/22/20.
//  Copyright © 2020 Finley. All rights reserved.
//

#include "attract_screen.h"
#include "player_data.h"
#include "water_scene.h"

#ifndef DEBUG
#define DEBUG 0
#endif

void attract_screen(void){

    terminal_clear();

    terminal_wprint( 0,  1, L"Welcome To Treasure Diver v1.1!");
    terminal_wprint( 0,  3, L"Starring [color=yellow]🙂[/color] and [color=yellow]😷[/color] as the player!");
    terminal_wprint(25,  4, L"(that's you!)");
    terminal_wprint( 0,  6, L"Starring 💰 as the things you collect!");
    terminal_wprint(25,  7, L"(ooh money!)");
    terminal_wprint( 0,  9, L"Starring 🐍 as the bad guys!");
    terminal_wprint(25, 10, L"(boo, hiss!)");
    terminal_wprint( 0, 12, L"Starring [color=red]🔆[/color] as the store!");
    terminal_wprint(10, 13, L"(where you spend your money)");
    
    terminal_wprint( 0, 16, L"Use the arrow keys to move around!");
    terminal_wprint( 0, 18, L"Press any key to start!");
    
    terminal_refresh();
    terminal_read();
}

void main_setup(void){
    // We set a ton of constants and initialize variables here
    // We put it different from main() so that we can call it again.
    
    player_max_speed = 10;
    player_speed = 10;
    player_has_gun = 0;
    player_ammo = 0;
    player_max_air = 10;
    player_air = 10;
    player_max_level = 0;
    player_score = 0;
    player_collected_money = 0;
    player_money = 0;

    // Maze dimensions
    height = 19;
    width = 39;
    
    maze_wall  = L'█'; // Due to buggerness, these get redefined, so we set them once here.
    maze_empty = L'░'; // I should get around to learning how to set constants in C. Without #defines.
    maze_money = L'💰';
    maze_snake = L'🐍';
    
    maze_wall_color  = 0xFFDEB887;
    maze_empty_color = 0xFFADD8E6;
    maze_money_color = 0xFFFFD700;
    maze_snake_color = 0xFFFFFFFF;
    
    if(!DEBUG){
        attract_screen();
        water_scene();
    } else {

        terminal_wprint(1, 2, L"Test symbols: 💰-💲 $ 😃  🐍");
        terminal_wprint(1, 3, L"Test symbols: █████████");
        terminal_wprint(1, 4, L"Test symbols: 🀫🀫🀫🀫🀫🀫🀫🀫🀫🀫");
        terminal_wprint(1, 5, L"Test symbols: abcdefghijklm");

        terminal_refresh();
        while(1){
            int key = terminal_read();
            if(key == TK_ESCAPE || key == TK_Q || key == TK_CLOSE){
                terminal_close();
                exit(0);
            }
        }
    }
}
