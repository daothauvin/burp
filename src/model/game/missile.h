/*
	missile management
*/
#ifndef MISSILE_H
#define MISSILE_H
#include "robot.h"
#include "math.h"
#include <stdbool.h>

typedef struct missile_impl missile;

//prototypes
missile* create(double pos_x, double pos_y, double angle, robot* rob, double explo_dist); //Angle will be calculated

void update_pos_missile(missile* m);
bool explode(missile* mis,point *explode_point); // Might trigger an event in the view
void check_distant(missile* m);
bool will_explode(missile* m);
void collision_with_missiles(robot* rob, missile* m);
double get_missile_angle(missile *m);
double get_missile_speed(missile *m);
void get_missile_pos(missile *m,point *p);
double get_parcouru_distant(missile *m);
bool get_missile_owner(missile *m, robot **res_rob);
#endif