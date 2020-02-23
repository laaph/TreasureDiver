//
//  player_data.h
//  TreasureDiver
//
//  Created by Jethro on 2/22/20.
//  Copyright © 2020 Finley. All rights reserved.
//

#ifndef player_data_h
#define player_data_h

#include "maze.h"

int player_speed;
int player_max_speed;
int player_has_gun;
int player_ammo;
int player_max_air;
int player_air;
int player_score;
int player_collected_money;
int player_money;
int player_max_level;
int player_wounded;

int player_x;
int player_y;

int player_level;
Node* player_maze_nodes[100];

#endif /* player_data_h */
