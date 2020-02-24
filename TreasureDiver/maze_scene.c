//
//  maze_scene.c
//  TreasureDiver
//
//  Created by Jethro on 2/22/20.
//  Copyright © 2020 Finley. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "BearLibTerminal.h"
#include "maze_scene.h"
#include "maze.h"
#include "player_data.h"
#include "water_scene.h"
#include "attract_screen.h"

void maze_scene(int level) {
    player_level = level;
    
    if(level > player_max_level){
        while (level > player_max_level) {
            player_max_level++;
            Node *start, *last;
            
            //Seed random generator
            srand((unsigned int) time( NULL ) );
    
            //Initialize maze
            if ( maze_init() )
            {
                fprintf( stderr, "Error: out of memory!\n");
                terminal_close();
                exit( 1 );
            }
    
            //Setup start node
            start = nodes + 1 + width;
            start->parent = start;
            last = start;
    
            //Connect nodes until start node is reached and can't be left
            while ( ( last = maze_link( last ) ) != start );

            player_maze_nodes[player_max_level] = nodes;
//            fprintf(stderr, "Debug: Made maze level %i \n", level);

            // Set top and bottom to empty
            for (int i = 1; i < width - 1; i++){
                nodes[i].c = maze_empty;
                nodes[i].color = maze_empty_color;
                
                nodes[i + width].c = maze_empty;   // Blank out row 2 as well
                nodes[i + width].color = maze_empty_color;

                nodes[i + (height-2)*width].c = maze_empty;
                nodes[i + (height-2)*width].color = maze_empty_color;
                
                nodes[i + (height-1)*width].c = maze_empty;
                nodes[i + (height-1)*width].color = maze_empty_color;
            }
            
            // punch some holes in the walls
            for(int i = level * 4; i < 100; i++){
                int x = (int)(rand() % (width - 2) + 1);
                int y = (int)(rand() % (height - 2) +1);
                
                nodes[x + (y)*width].c = maze_empty;
                nodes[x + (y)*width].color = maze_empty_color;
//                fprintf(stderr, "Hole at %i %i \n", x, y);
            }
            
            // put some treasure all over the place
            for(int i = 0; i < 100; i++){
                int x = (int)(rand() % width);
                int y = (int)(rand() % height);
                
                if(nodes[x + (y * width)].c == maze_empty && y > 2 && y < height - 2){
                
                    nodes[x + (y)*width].c = maze_money;
                    nodes[x + (y)*width].color = maze_money_color;
//                fprintf(stderr, "Hole at %i %i \n", x, y);
                }
            }
            for(int i = 0; i < level - 1; i++){
                int snake_set = 0;
                while(!snake_set) {
                    int x = (int)(rand() % width);
                    int y = (int)(rand() % height);
                    if(nodes[x + (y * width)].c == maze_empty && y > 2 && y < height - 2){
                
                    nodes[x + (y)*width].c = maze_snake;
                    nodes[x + (y)*width].color = maze_snake_color;
                    snake_set = 1;
                }
                    
                }
            }
        }
    }

    // Set the nodes of the maze for this level
    nodes = player_maze_nodes[level];
    
    // Since we are lazy and not dynamically allocating anything except the
    // levels, we will make a 100 length array for the snakes.
    
    // There should be level-1 snakes.
    
    snake_num = 0;
    for (int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            if(nodes[i + j*width].c == maze_snake) {
//                fprintf(stderr, "snake finding time, found snake at %i %i \n", i, j);
                snake_x[snake_num] = i;
                snake_y[snake_num] = j;
                snake_num++;
            }
            if(nodes[i+ j*width].c == maze_empty){
                nodes[i+j*width].color = maze_empty_color; // So red trails don't linger
                // it would be better to fade out, but whatever
                
            }
        }
    }
    
    int air_counter = 0;
    int dir = 0;
    player_speed = player_max_speed - player_collected_money;
    if(player_wounded){
        player_speed = player_speed - 10;
    }
    int player_move_time = 100 - (player_speed * 3);
    int snake_move_time = 100 - (level * 3); // snake speed is equal to the level;

    while(1){
        terminal_clear();
        draw_maze();
        terminal_refresh();
        
        if(player_air < 0) {
            while(player_y < height){
                terminal_wprint(player_x, player_y, L"[color=blue]😷");
                terminal_refresh();
                nanosleep((const struct timespec[]){{0, 50000000L}}, NULL);
                terminal_color(nodes[player_x + player_y * width].color);
                terminal_wprint(player_x, player_y, &nodes[player_x + player_y * width].c);
                player_y++;
            }
            terminal_color(0xFFFFFFFF);
            terminal_wprint (1,  7, L"█████████████████████████████████████");
            terminal_wprint (1,  8, L"█ You have run out of air!          █");
            terminal_wprint (1,  9, L"█                                   █");
            terminal_wprintf(1,  9, L"█ Your score is: %i ", player_score);
            terminal_wprint (1, 10, L"█ Would you like to try again? (Y/N)█");
            terminal_wprint (1, 11, L"█████████████████████████████████████");
            terminal_refresh();
            while(1){
                int key2 = terminal_read();
                if(key2 == TK_N || key2 == TK_ESCAPE) {
                    // I don't bother to free memory, on most machines this is
                    // perfectly okay. I don't know any that it isn't.
                    terminal_close();
                    exit(0);
                }
                if(key2 == TK_Y || key2 == TK_RETURN){
                    for(int i = 0; i < player_max_level; i++) {
                        free(player_maze_nodes[i]);
                    }
                    main_setup();
                }
            }
        }
        
        air_counter++;
        player_move_time--;
        snake_move_time--;
        
        if(air_counter > 1000){
            player_air = player_air-1;
            air_counter = 0;
//            fprintf(stderr, "air %i, money %i \n", player_air, player_collected_money);
        }
        
        if(terminal_has_input()){
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
                draw_maze();
                terminal_refresh();
            }
            if(key == TK_CLOSE){
                terminal_close();
                exit(0);
            }
            if(key == TK_UP || key == TK_DOWN || key == TK_LEFT || key == TK_RIGHT){
                dir = key;
            }
        }

        if(snake_move_time < 1) {
            for (int s = 0; s < snake_num; s++){
                int i = snake_x[s]; int j = snake_y[s];
//                fprintf(stderr, "snake move time, found snake at %i %i \n", i, j);
                int moved = 0;
                if(rand() % 2 < 1) {
                    if(player_x < i) {
                        moved = snake_move(s, i, j, i - 1, j, moved);
                    }
                    if(player_x > i) {
                        moved = snake_move(s, i, j, i + 1, j, moved);
                    }
                    if(player_y < j) {
                        moved = snake_move(s, i, j, i, j - 1, moved);
                    }
                    if(player_y > j) {
                        moved = snake_move(s, i, j, i, j + 1, moved);
                    }
                } else {
                    // we do it in the other order just to mix it up
                    if(player_y < j) {
                        moved = snake_move(s, i, j, i, j - 1, moved);
                    }
                    if(player_y > j) {
                        moved = snake_move(s, i, j, i, j + 1, moved);
                    }
                    if(player_x < i) {
                        moved = snake_move(s, i, j, i - 1, j, moved);
                    }
                    if(player_x > i) {
                        moved = snake_move(s, i, j, i + 1, j, moved);
                    }
                }
                // Otherwise we pick a random direction
                int x_1 = (rand() % 3) - 1;
                int y_1 = (rand() % 3) - 1;
                snake_move(s, i, j, i + x_1, j + y_1, moved);
                
                
            }
            // for each snake
            snake_move_time = 100 - (level * 3);
        }
        if(player_move_time < 1) {
            if(dir == TK_LEFT) {
                move_player(player_x - 1, player_y);
            }
            if(dir == TK_RIGHT) {
                move_player(player_x + 1, player_y);
            }
            if(dir == TK_UP) {
                if(player_y == 0){
                    if(level == 1) {
                        player_money += player_collected_money;
                        player_score += player_collected_money;
                        player_collected_money = 0;
                        water_scene();
                    }
                    player_y = height -1;
                    maze_scene(level-1);
                }
                move_player(player_x, player_y - 1);
            }
            if(dir == TK_DOWN) {
                if(player_y == height - 1){
                    player_y = 1;
                    maze_scene(level + 1);
                }
                move_player(player_x, player_y + 1);
            }
            player_speed = player_max_speed - player_collected_money;
            if(player_wounded){
                player_speed = player_speed - 10;
            }
            player_move_time = 100 - (player_speed * 3);
        }
        nanosleep((const struct timespec[]){{0, 100L}}, NULL);
    }
}
// We will change player_x and player_y as needed
void move_player(int x, int y){
    if(nodes[(x) + (y) * width].c == maze_money){
        player_collected_money += player_level;

//        fprintf(stderr, "level %i, money %i \n", player_level, player_collected_money);

        nodes[(x) + (y) * width].c = maze_empty;
        nodes[(x) + (y) * width].color = maze_empty_color;
    }
    if(nodes[(x) + (y) * width].c == maze_empty){
        player_x = x;
        player_y = y;
    }
}
int snake_move(int snake_id, int start_x, int start_y, int dest_x, int dest_y, int moved){
    // if we have already moved, return moved as it is.
    if(moved > 0) {
        return moved;
    }
    
    // snake murder!
    if(dest_x == player_x && dest_y == player_y){
        player_air = player_air - 2;
        player_wounded = 1;
        
        // The x+1 and x-1 should have bounds checking :(
        // We never get to the y edge of the screen, so that should be okay.
        nodes[dest_x + dest_y * width].color = 0xFFFF0000;
        nodes[dest_x +1 + dest_y * width].color = 0xFFFF0000;
        if(dest_y < height) {
            nodes[dest_x + ((dest_y + 1) * width)].color = 0xFFFF0000;
        }
        nodes[dest_x -1 + dest_y * width].color = 0xFFFF0000;
        if(dest_y > 0) {
            nodes[dest_x + ((dest_y - 1) * width)].color = 0xFFFF0000;
        }
        
        nodes[start_x + start_y * width].c = maze_empty;

        // if snake_id == snake_num - 1, then we overwrite ourselves and nothing happens.
        snake_x[snake_id] = snake_x[snake_num-1];
        snake_y[snake_id] = snake_x[snake_num-1];
        snake_num--;
        return 1;
    
    }
    
    if(nodes[dest_x + dest_y * width].c == maze_empty){
        nodes[dest_x + dest_y * width].c = maze_snake;
        nodes[dest_x + dest_y * width].color = maze_snake_color;
        nodes[start_x + start_y * width].c = maze_empty;
        nodes[start_x + start_y * width].color = maze_empty_color;
        snake_x[snake_id] = dest_x;
        snake_y[snake_id] = dest_y;
//        fprintf(stderr, "Snake moved.\n");
        return 1;
    }
    
    return 0;
}

void draw_maze(void)
{
    int i, j;

    for ( i = 0; i < height; i++ )
    {
        for ( j = 0; j < width; j++ )
        {
            terminal_color(nodes[j + i*width].color);
            terminal_wprint(j, i, &nodes[j + i * width].c );
        }
    }
    if(player_wounded){
        terminal_wprint(player_x, player_y, L"[color=red]😷");
        nodes[player_x + player_y*width].color = 0xFFFF0000;
    } else {
        terminal_wprint(player_x, player_y, L"[color=yellow]😷");
    }
    terminal_color(0xFFFFFFFF);

    terminal_printf(0, 21, "Speed: %i/%i", player_speed, player_max_speed);
    terminal_printf(0, 22, "Air:   %i/%i", player_air, player_max_air);
    terminal_printf(0, 23, "Money: %i (At surface: %i )", player_collected_money, player_money);
    if(player_has_gun){
        terminal_printf(0, 24, "Ammo:  %i", player_ammo);
    }
}
