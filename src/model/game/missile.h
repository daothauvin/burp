/*
	missile management
*/
#ifndef MISSILE_H
#define MISSILE_H
#include "robot.h"
#include "math.h"		
typedef struct missile_impl missile;

//prototypes
missile* create(double pos_x, double pos_y, double speed, double angle, Robot rob, double explo_dist); //Angle will be calculated

void update_pos_missile(missile* m);
Point explode(missile* mis); // Might trigger an event in the view
void check_distant(missile* m);
short will_explode(missile* m);
void collision_with_missiles(robot* rob, missile* m);
#endif