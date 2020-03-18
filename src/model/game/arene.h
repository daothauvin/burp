#ifndef ARENE_H
#define ARENE_H

#include "robot.h"


typedef struct{
	Robot* list_robots;
	Missile* list_missile;
}*Arene;

Arene create_arene();
int add_missiles(Arene arene,Missile missile);
int remove_missiles(Arene arene,Missile missile);
int add_robot(Arene arene,Robot rob);
int remove_robot(Arene arene,Robot rob);

#endif 