#ifndef ARENE_H
#define ARENE_H

#include "robot.h"
#include "missile.h"
#include "../../define.h"

typedef struct arena_impl arena;

arena *create_arena();
int add_missile(arena *arena, missile *m);
int add_robot(arena *arena, robot *rob);
bool remove_missile(arena *arena, missile *mis);
bool remove_robot(arena *arena, robot *rob);
void freeArena(arena **arena);
int get_nb_missiles_arena(arena *arena);
int get_nb_robot_arena(arena *arena);
robot *get_robot_per_id(arena *arena, int id);
robot *get_robot_index(arena *arena, int indx);
missile *get_missile_index(arena *arena, int indx);

#endif