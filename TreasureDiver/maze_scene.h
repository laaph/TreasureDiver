//
//  maze_scene.h
//  TreasureDiver
//
//  Created by Jethro on 2/22/20.
//  Copyright © 2020 Finley. All rights reserved.
//

#ifndef maze_scene_h
#define maze_scene_h

void maze_scene(int level);
void draw_maze(void);
void move_player(int x, int y);   // Only because I want to define it after I use it, not because I want to
                            // make it global
int snake_move(int snake_id, int start_x, int start_y, int dest_x, int dest_y, int moved);
int snake_x[100];
int snake_y[100];
int snake_num;
#endif /* maze_scene_h */
