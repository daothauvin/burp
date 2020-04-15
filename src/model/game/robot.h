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

typedef struct robot_impl
{
	char *robot_id;
	int id;
	double health_points;// Represented as a percentage
	Point pos; 
	double angle;
	double speed;// Represented as a percentage
	int missiles;//Number of missile in the area currently
	double robot_hitbox;//robot hitbox size
	int waiting_time;//cycle delay
	int* memory;
}*Robot;

//Functions prototypes
// Allocate a robot at a time
Robot create_robot();
//allocate a robot with the script's contents
void initialize_robot(Robot rob,double x_1,double y_1,double angle,double speed,int id);
void update_pos_robot(Robot rob); // Fixed depending on angle and speed every cycle
void modify_speed(Robot rob,double speed);
void modify_angle(Robot rob,double angle);
void inflict_damage_from_missile(Robot rob,Point p);
void inflict_damage_from_collision(Robot rob1,Robot rob2);
short collision_robots(Robot rob1,Robot rob2);
short check_collision_robots(Robot rob1,Robot rob2);
#endif
