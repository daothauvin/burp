/*
	differents commande usable in a script
*/
#ifndef COMMANDS_H
#define COMMANDS_H
#include "robot.h"
int wait(Robot rob,int delay);
void poke(Robot rob,void* addr,int value);
void peek(Robot rob,void* addr);
int go_to(int num);
//A voir comment implementer int checkif()
int rand(int num);
int cardinal(Robot robots);
int self(Robot rob);
float speed(Robot rob);
float state(Robot rob);
float gpsx(Robot rob);
float gpsy(Robot rob);
void engine(Robot rob,float angle,float speed);
Missile shoot(Robot rob,float angle);
float angle(float x1,float y1,float x1,float x2);
float targetx(float x1,float angle,float length);
float targety(float y1,float angle,float length);
float distance(float x1,float y1,float x2,float y2);
#endif 