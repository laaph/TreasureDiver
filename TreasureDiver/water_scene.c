//
//  enter_water_scene.c
//  TreasureDiver
//
//  Created by Jethro on 2/22/20.
//  Copyright © 2020 Finley. All rights reserved.
//

#include <time.h>

#include "water_scene.h"
#include "BearLibTerminal.h"
#include "maze_scene.h"
#include "maze.h"
#include "player_data.h"
#include "store_scene.h"


void water_scene(void) {

    player_x = 34;
    player_y = 21;

    player_wounded = 0;

    int store_x = 38;
    int water_x = 30;

    int wave_toggle = 1;

    terminal_clear();
    terminal_color(0xFFDEB887);
    terminal_wprint( 0, 22, L"█████████");
    terminal_wprint(31, 22, L"█████████");

    terminal_wprint( 0, 23, L"        █");
    terminal_wprint( 0, 24, L"        █");

    terminal_wprint(31, 23, L"█");
    terminal_wprint(31, 24, L"█");

    terminal_wprint(store_x, 21, L"[color=red]🔆");

    wave_toggle = 500;
    int move_time = 100 - (player_speed * 3);
    int dir = 0;
    
    while(1){
    
        player_speed = player_max_speed;

        terminal_color(0xFFFFFFFF);
        terminal_printf(0, 0, "Speed: %i", player_speed);
        terminal_printf(0, 1, "Air:   %i/%i", player_air, player_max_air);
        terminal_printf(0, 2, "Money: %i", player_money);
        terminal_printf(0, 3, "Score: %i", player_score);

        if(player_has_gun){
            terminal_printf(0, 4, "Ammo:  %i", player_ammo);
        }

        terminal_color(0xFFFFFF00);
        terminal_print(5,  7, "⟍  |  ⟋");
        terminal_print(5,  8, " ⟍ | ⟋ ");
        terminal_print(5,  9, "  ⟍|⟋  ");
        terminal_print(5, 10, "---☼----");
        terminal_print(5, 11, "  ⟋|⟍  ");
        terminal_print(5, 12, " ⟋ | ⟍ ");
        terminal_print(5, 13, "⟋  |  ⟍");

        terminal_wprint(player_x, player_y, L"[color=yellow]🙂");  // 😷
    
        if(wave_toggle == 500){
            terminal_wprint(9, 23, L"[color=#FFADD8E6] ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^");
            terminal_wprint(9, 24, L"[color=#FFADD8E6]^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ");
        }
        if(wave_toggle == 1000) {
            terminal_wprint(9, 23, L"[color=#FFADD8E6]^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ");
            terminal_wprint(9, 24, L"[color=#FFADD8E6] ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^");
            wave_toggle = 0;
        }
        terminal_refresh();
        
        wave_toggle = wave_toggle + 1;
        
        while(terminal_has_input()){
            int key = terminal_read();
            if(key == TK_ESCAPE || key == TK_Q){
                terminal_wprint(2, 10, L"Are you sure you want to quit? (Y/N)");
                terminal_refresh();
                int key2 = terminal_read();
                if(key2 == TK_Y) {
                    terminal_close();
                    exit(0);
                }
                terminal_wprint(2, 10, L"                                    ");
                terminal_refresh();
            }
            if(key == TK_CLOSE){
                terminal_close();
                exit(0);
            }
            if(key == TK_RIGHT){
                dir = TK_RIGHT;
            }
            if(key == TK_LEFT){
                dir = TK_LEFT;
            }
        }
        
        // We aren't changing this at the moment since it does not matter how fast the waves
        // go.
        
        // But it does still affect movement.  🤔
        nanosleep((const struct timespec[]){{0, 100L}}, NULL);
        
        move_time--;
        if(move_time < 1){
            if(dir == TK_RIGHT) {
                terminal_wprint(player_x, player_y, L" "); // delete the player
                player_x++;
                if(player_x == store_x){
                    store_scene();
                }
            }
            if(dir == TK_LEFT){
                terminal_wprint(player_x, player_y, L" ");
                player_x--;
                if(player_x == water_x){
                    while(player_y <= 24){
                        clock_t loop_began = clock();
                        
                        terminal_wprint(player_x, player_y, L"[color=yellow]🙂");
                        terminal_refresh();
                        
                        // loop management goes here
                        while(clock() - loop_began < (CLOCKS_PER_SEC / 60)) {
                            nanosleep((const struct timespec[]){{0, 100L}}, NULL);
                        }
                        
                        terminal_wprint(player_x, player_y, L" ");
                        player_y++;
                        terminal_refresh();
                    }
                    player_x = width - 2;
                    player_y = 1;
                    maze_scene(1);
                }
            }
            move_time = 100 - (player_speed * 3);
        }
    }
}
