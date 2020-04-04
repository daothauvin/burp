/*
	missile management
*/
#ifndef MISSILE_H
#define MISSILE_H

#include "robot.h"
#include "math.h"
typedef struct
{
	double angle;
	double pos_x;
	double pos_y;
	double speed;
	double parcouru_distant;
	double explosion_distant;
	short will_explode;	
	Robot owner;
}*Missile;

//prototypes
Missile create(double pos_x,double pos_y,double speed,double angle,Robot rob,double explo_dist);//Angle will be calculated
void update_pos_missile(Missile m);
Point explode(Missile mis); // Might trigger an event in the view
void check_distant(Missile m);
short will_explode(Missile m);
short collision_with_missiles(Robot rob,Missile m);
short collision_with_walls_missiles(Missile m);

#endif