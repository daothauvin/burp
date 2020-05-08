/*
	differents commande usable in a script
*/
#ifndef COMMANDS_H
#define COMMANDS_H
#include "robot.h"
#include "missile.h"
#include "arene.h"
/// \cond
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
/// \endcond
#include "../../define.h"


/**
 * set the robot [rob] is waiting time to [delay]
 * and return its value.
 */
int wait_robot(robot *rob,unsigned int delay);

/**
 * Set the integer [value] to the indice [addr]
 * in the robot [rob]'s memory.
 * if the indice given is invalid (i.e, not contained between 0 and robot_memory)
 * the operation will fail and it'll return false.
 * if the operation succeed, it'll return true.
 */ 
bool poke(robot *rob, int addr, int value);

/**
 * return the value stocked at the indice i
 * of the robot [rob]'s memory.
 * if an indice is invalid, it'll return -1.
 */
int peek(robot *rob, int addr);

/**
 * return num.
 */
int go_to(int num);

/**
 * Return a random number between 0 and [num].
 */
int randoms(int num);

/**
 * return the number of active robot in the arena [arena].
 */
int cardinal(arena *arena);

/**
 * return the id of the robot [rob].
 */
int self(robot *rob);

/**
 * return the number of health_points of the robot
 * contained the id [num] in the arena [arena].
 * Return -1 if no robot has the id [num].
 */
int state(arena *arena, int num);

/**
 * return the speed of the robot [rob].
 */
int speed(robot *rob);

/**
 * return the x coordinate of the robot
 * contained the id [num] in the arena [arena].
 * Return -1 if no robot has the id [num].
 */
double gpsx(arena *arena, int num);

/**
 * return the y coordinate of the robot
 * contained the id [num] in the arena [arena].
 * Return -1 if no robot has the id [num].
 */
double gpsy(arena *arena, int num);

/**
 * Start a robot [rob]'s engine and set his angle to
 * [angle] and speed to [speed].
 */
void engine(robot *rob, double angle, double speed);

/**
 * Shoot a missile from rob and add it to arena while assigning the angle
 * [angle] and the explosion_distant [explo_dist] to the missile.
 * If the robot has already NB_ROBOT_MISSILES active in the arena,
 * the operation will fail and return false.
 * If the operation succeed, it'll return true.
 */
bool shoot(robot *rob, arena *arena, double angle, double explo_dist);

/**
 * Calculate the angle corresponding to the line 
 * from [x1,y2] to [x2,y2].
 * If [x1,y1] == [x2,y2] it'll for now return an angle of 90°c.
 */
double angle(double x1, double y1, double x2, double y2);

/**
 * Return the next coordinate X considering a x [x1] looking
 * at [angle] which move at the speed [length].
 */
double targetx(double x1, double angle, double length);

/**
 * Return the next coordinate Y considering a y [y1] looking
 * at [angle] which move at the speed [length].
 */
double targety(double y1, double angle, double length);

/**
 * Return the distance between [x1,y1] and [x2,y2].
 */
double distance(double x1, double y1, double x2, double y2);
#endif