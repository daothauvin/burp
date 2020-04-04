/*
	robot management

	TODO: How to detect a missile close to a robot?
		  
*/
/* Robot's hitbox, the hitbox of a robot is represented
   by a moving square of size 10 by 10 centred on the 
   robot's actual position
   It might affect the robot's collision to missile 
   or others robots
   the representation would look like that
   p1 * * * p2
   *		*
   *    x   *
   * 		*
   p3 * * * p4
   Where x is the robot
*/
#ifndef ROBOT_H
#define ROBOT_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../../define.h"

typedef struct point{
	double x;
	double y;
}*Point;

typedef struct hitbox{
	Point p1;
	Point p2;
	Point p3;
	Point p4;
}*Hitbox;

typedef struct robot
{
	int id;
	double health_points;// Represented as a percentage
	Point pos; 
	double angle;
	double speed;// Represented as a percentage
	int missiles;//Number of missile in the area currently
	Hitbox robot_hitbox;//robot hitbox size
	int waiting_time;//cycle delay
	int* memory;
}*Robot;

//Functions prototypes
// Allocate a robot at a time
Robot create_robot();
//allocate a robot with the script's contents
void initialize_robot(Robot rob,double x_1,double y_1,double angle,double speed,int id);
void update_hitbox(Robot rob);
void update_pos_robot(Robot rob); // Fixed depending on angle and speed every cycle
void modify_speed(Robot rob,double speed);
void modify_angle(Robot rob,double angle);
void inflict_damage_from_missile(Robot rob,int explotion_damage);
void inflict_damage_from_collision(Robot rob1,Robot rob2);
short collision_robots(Robot rob1,Robot rob2);
short check_collision_robots(Robot rob1,Robot rob2);
short collision_robots_with_walls(Robot rob);
#endif
