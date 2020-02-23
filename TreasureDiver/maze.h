//
//  maze.h
//  TreasureDiver
//
//  Created by Jethro on 2/22/20.
//  Copyright © 2020 Finley. All rights reserved.
//

#ifndef maze_h
#define maze_h

#include <wchar.h>

typedef struct
{
    int x, y; //Node position - little waste of memory, but it allows faster generation
    void *parent; //Pointer to parent node
    int color;  // Color of the character to be displayed;
    wchar_t c; //Character to be displayed
    char dirs; //Directions that still haven't been explored
} Node;

wchar_t maze_wall;
wchar_t maze_empty;
wchar_t maze_money;
wchar_t maze_snake;

unsigned int maze_wall_color;
unsigned int maze_empty_color;
unsigned int maze_money_color;
unsigned int maze_snake_color;

Node *nodes; //Nodes array
int width, height; //Maze dimensions

int maze_init(void);
Node *maze_link( Node *n );

#endif /* maze_h */
