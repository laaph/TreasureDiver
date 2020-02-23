//
//  store_scene.c
//  TreasureDiver
//
//  Created by Jethro on 2/22/20.
//  Copyright © 2020 Finley. All rights reserved.
//

#include "store_scene.h"
#include "BearLibTerminal.h"
#include "player_data.h"
#include "water_scene.h"

void store_scene(void){
    
    while(1){
    
        terminal_clear();
        terminal_color(0xFFFFFFFF);
        terminal_printf(0, 0, "Speed: %i", player_max_speed);
        terminal_printf(0, 1, "Air:   %i/%i", player_air, player_max_air);
        terminal_printf(0, 2, "Money: %i", player_money);
        terminal_printf(0, 3, "Score: %i", player_score);

        if(player_has_gun){
            terminal_printf(0, 4, "Ammo:  %i", player_ammo);
        }

        terminal_wprint(0, 8, L"You may buy...");
        
        terminal_wprintf(0, 10, L"$%2i 1. Refill your air", player_max_air - player_air);
        terminal_wprint (0, 11, L"$10 2. Additional air");
        terminal_wprint (0, 12, L"$10 3. Additional max speed");
        
        //    if(player_has_gun){
    //        terminal_wprint(0, 10, L"$50 4. Snake gun");
    //    } else {
    //        terminal_wprint(0, 10, L"$5  4. Snake gun ammo");
    //    }
    //    terminal_wprint(0, 11, L"$11 5. Emergency speed pills");


        
        terminal_wprint(0, 22, L"    0. Leave the shop");
        
        terminal_refresh();
        int key = terminal_read();
        if(key == TK_1 || key == TK_KP_1){
            if(player_money >= player_max_air - player_air){
                player_money = player_money - (player_max_air - player_air);
                player_air = player_max_air;
            }
        }
        if(key == TK_2 || key == TK_KP_2){
            if(player_money >= 10){
                player_money -= 10;
                player_max_air++;
                player_air++;
            }
        }
        if(key == TK_3 || key == TK_KP_3){
            if(player_money >= 10){
                player_money -= 10;
                player_max_speed++;
            }
        }
        if(key == TK_0 || key == TK_KP_0 || key == TK_LEFT){
            water_scene();
        }
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
    }
}
