#ifndef ARENE_H
#define ARENE_H

#include "robot.h"
#include "missile.h"
#include "../../define.h"
/// \cond
#include <string.h>
/// \endcond

typedef struct arena_impl arena;

/**
 * Allocate an arena in memory and return it
 */
arena *create_arena();

/**
 * Add a missile [m] to the arena [arena].
 * If there is already NB_ROBOT * NB_MISSILES_ROBOT
 * present in the arena [arena], it'll not add [m] to the arena
 * and return -1.
 * If the operation succeed, it'll return the index of 
 * the missile [m] in the list of missiles present
 * in the arena [arena]
 */
int add_missile(arena *arena, missile *m);

/**
 * Add a robot [rob] to the arena [arena].
 * If there is already NB_ROBOT present in the arena,
 * it'll not add [rob] to the arena and return -1.
 * If the operation succeed, it'll return the index of 
 * the robot [rob] in the list of robot present in the arena [arena]
 */
int add_robot(arena *arena, robot *rob);

/**
 * Remove a missile [mis] from the arena [arena].
 * The operation will fail and return false if the missile [mis]
 * is not present in the arena.
 * If the missile [mis] is in the arena [arena], it'll free the missile
 * and return true.
 */
bool remove_missile(arena *arena, missile *mis);

/**
 * Remove a missile [mis] from the arena [arena].
 * The operation will fail and return false if the missile [mis]
 * is not present in the arena.
 * If the missile [mis] is in the arena [arena], it'll free the missile
 * and return true.
 */
bool remove_robot(arena *arena, robot *rob);

/**
 * Free an arena [arena] and all its robot/missile still present in it.
 */
void freeArena(arena **arena);

/**
 * Return the number of missiles present in the arena [arena].
 */
int get_nb_missiles_arena(arena *arena);

/**
 * Return the number of robots present in the arena [arena].
 */
int get_nb_robot_arena(arena *arena);

/**
 * Return the robot present in the arena [arena]
 * which has the id [id].
 * If [id] is not present it'll return NULL,
 * else it'll return the robot corresponding to the
 * given id.
 */
robot *get_robot_per_id(arena *arena, int id);

/**
 * Return the robot present in the arena [arena]
 * which has the index [indx].
 * If the given index is invalid, it'll return NULL,
 * else it'll return the robot at the indx [index].
 */
robot *get_robot_index(arena *arena, int indx);

/**
 * Return the missile present in the arena [arena]
 * which has the index [indx].
 * If the given index is invalid, it'll return NULL,
 * else it'll return the missile at the indx [index].
 */
missile *get_missile_index(arena *arena, int indx);

#endif