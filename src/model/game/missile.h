/*
	missile management
*/
#ifndef MISSILE_H
#define MISSILE_H

#include "robot.h"
#include "../../define.h"
/// \cond
#include <assert.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
/// \endcond

typedef struct missile_impl missile;

/**
 * Allocate a missile in memory and assign [pos_x] and [pos_y]
 * as its coordinate, [angle] as the angle trajectory, [rob] as the 
 * owner of the missle and [explo_dist] as the distance limit
 * the missile can navigate before exploding.
 * The speed value is equal to [MISSILE_SPEED]
 */
missile* create_missile(double pos_x, double pos_y, double angle, robot* rob, double explo_dist);

/**
 * Update the missile is position and will also check if the missile
 * will explode this turn which include : hitting a wall and
 * going over [explo_dist].
 */
void update_pos_missile(missile* m);

/**
 * If the missile is ready to explode, it'll set [explode_point] 
 * to the value of the missile at the moment of the 
 * explosion and return true.
 * If he isn't ready to explode, it'll return false 
 */
bool explode(missile* mis,point *explode_point);

/**
 * Return true if the missile [m] is ready to explode,
 * false otherwise.
 */
bool will_explode(missile* m);

/**
 * Check if the missile [m] has a collision with
 * the robot [rob]. if there is one, it'll set [will_explode] to true
 * else it'll do nothing.
 */
void collision_with_missiles(robot* rob, missile* m);

/**
 * Return the angle of the missile [m].
 */
double get_missile_angle(missile *m);

/**
 * Return the speed of the missile [m].
 */
double get_missile_speed(missile *m);

/**
 * Return the explosion distance of the missile [m].
 */
double get_explosion_distant(missile *m);

/**
 * Return the travelled distance of the missile [m].
 */
double get_parcouru_distant(missile *m);

/**
 * Put the coordinate as a point of a missile [m]
 * into a point [p].
 */
void get_missile_pos(missile *m,point *p);

/**
 * return a pointer to the owner of the missile [m].
 */
robot* get_missile_owner(missile *m);

/**
 * Free a missile allocated in memory.
 */
bool destroy_missile(missile **m);
#endif