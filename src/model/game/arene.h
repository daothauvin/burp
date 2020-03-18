#ifndef ARENE_H
#define ARENE_H

#include "robot.h"
#include "missile.h"

typedef struct{
	Robot* list_robots;
	Missile* list_missile;
	int nb_missiles;
	int nb_robots;
}*Arene;

Arene create_arene();
int add_missile(Arene arene,Missile missile);
int remove_missile(Arene arene,Missile missile);
int add_robot(Arene arene,Robot rob);
int remove_robot(Arene arene,Robot rob);

#endif 