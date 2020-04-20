#ifndef robot_H
#define robot_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../../define.h"
#include <stdbool.h>
#include <assert.h>
typedef struct point_impl
{
	double x;
	double y;
} point;

typedef struct robot_impl robot;

//Functions prototypes
// Allocate a robot at a time
double degree_to_radians(double x);
robot *create_robot(double x_1, double y_1, double angle, double speed, int id);
void update_pos_robot(robot *rob); // Fixed depending on angle and speed every cycle
void inflict_damage_from_missile(robot *rob, point p);
void inflict_damage_from_collision(robot *rob1, robot *rob2);
short collision_robots(robot *rob1, robot *rob2);
short check_collision_robots(robot *rob1, robot *rob2);
char *get_robot_name(robot *robot);
double get_robot_health_points(robot *rob);
double get_robot_angle(robot *rob);
bool set_robot_angle(robot *rob, double angle);
double get_robot_speed(robot *rob);
bool set_robot_speed(robot *rob, double speed);
void get_robot_pos(robot *rob, point *pos);
int get_robot_id(robot *rob);
int get_robot_nb_missiles(robot *rob);
void set_robot_nb_missiles(robot *rob,int nb_missiles);
int get_waiting_time_robot(robot *rob);
void set_waiting_time_robot(robot *rob, unsigned int waiting_time);
int get_memory_at_i(robot *rob, int i);
bool add_memory_to_robot(robot *rob, int *data, int pos);
void destroy_robot(robot **rob);
#endif