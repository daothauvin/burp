#ifndef robot_H
#define robot_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../../define.h"
#include <stdbool.h>
#include <assert.h>

/**
 * take a radius [x] in degree
 * and return its value in radian
 */
double degree_to_radians(double x);

typedef struct point_impl
{
	double x;
	double y;
} point;

typedef struct robot_impl robot;

/**
 * Allocate a robot in memory and assign [x_1] and [y_1] to its
 * coordinate, [angle] as its angle, [speed] as the speed and
 * [id] as the robot number.
 */ 
robot *create_robot(double x_1, double y_1, double angle, int speed, int id);

/**
 * Update the position of a robot [rob] to its next iteration,
 * if he is percuting a wall, it will inflict him [Collision_damage] as defined in define.
 * If there is a waiting time, it'll do nothing and only decrease the current waiting
 * time.
 */
void update_pos_robot(robot *rob);

/**
 * Take the position of an explosion [p] and a robot [rob],
 * and will inflict damage relative to his position to the
 * explosion point.
 */
void inflict_damage_from_missile(robot *rob, point p);

/**
 * It'll inflict [collision damage] to [rob1] and [rob2] and reduce
 * their speed to 0. Else it'll do nothing.
 */
void inflict_damage_from_collision(robot *rob1, robot *rob2);

/**
 * Take 2 robots [rob1] and [rob2] and will check
 * if there is a collision between them.
 * Return true if there is one, false if there is none.
 */
bool check_collision_robots(robot *rob1, robot *rob2);

/**
 * Return the robot's string name.
 */
char *get_robot_name(robot *robot);

/**
 * Return number of health points of the robot [rob].
 */
unsigned int get_robot_health_points(robot *rob);

/**
 * Return the angle of the robot [rob].
 */
double get_robot_angle(robot *rob);

/**
 * Return the speed of the robot [rob].
 */
int get_robot_speed(robot *rob);

/**
 * Put the coordinate as a point of a robot [rob]
 * into a point [pos].
 */
void get_robot_pos(robot *rob, point *pos);

/**
 * Return the identifier of the robot [rob].
 */
int get_robot_id(robot *rob);

/**
 * Return the waiting time of the robot [rob].
 */
int get_waiting_time_robot(robot *rob);

/**
 * Return the number of missiles active
 * of the robot [rob].
 */
int get_robot_nb_missiles(robot *rob);

/**
 * Return the value stocked at the indice i
 * of the robot [rob]'s memory.
 * If an indice is invalid, it'll return -1.
 */
int peek_memory_at(robot *rob, int i);

/**
 * Set the robot [rob]'s angle to [angle].
 * If the angle is invalid (i.e, not contained between 0 and 359),
 * the operation will fail and it'll return false.
 * If the operation succeed, it'll return true.
 */
bool set_robot_angle(robot *rob, double angle);

/**
 * Set the robot [rob]'s speed to [speed].
 * If the speed is invalid (i.e, not contained between 0 and MAX_SPEED),
 * the operation will fail and it'll return false.
 * If the operation succeed, it'll return true.
 */
bool set_robot_speed(robot *rob, int speed);

/**
 * Set the integer [data] to the indice [pos]
 * in the robot [rob]'s memory.
 * If the indice given is invalid (i.e, not contained between 0 and robot_memory),
 * the operation will fail and it'll return false.
 * If the operation succeed, it'll return true.
 */ 
bool poke_memory_at(robot *rob, int data, int pos);

/**
 * Increment the number of missile of the robot [rob]
 * by 1.
 */
void increment_nb_missile(robot *rob);

/**
 * Decrement the number of missile of the robot [rob]
 * by 1.
 */
void decrement_nb_missile(robot *rob);

/**
 * set the waiting_time of a robot [rob] to the value of
 * [waiting_time]. 
 */
void set_waiting_time_robot(robot *rob, unsigned int waiting_time);

/**
 * Free a robot allocate in memory.
 */
void destroy_robot(robot **rob);
#endif