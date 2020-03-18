/*
	missile management
*/
#ifndef MISSILE_H
#define MISSILE_H

#include "robot.h"
typedef struct
{
	double angle;
	double pos_x;
	double pos_y;
	double speed;
	double parcouru_distant;
	Robot owner;
}*Missile;

//prototypes
Missile create(double pos_x,double pos_y,double speed,double angle);//Angle will be calculated
Missile update_pos_missile(Missile m);
void explode(Missile mis); // Might trigger an event in the view

#endif