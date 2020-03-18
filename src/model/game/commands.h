/*
	differents commande usable in a script
*/
#ifndef COMMANDS_H
#define COMMANDS_H
#include "robot.h"
#include "arene.h"
#include <stdio.h>
#include <stdlib.h>
int wait(Robot rob,int delay);
void poke(Robot rob,int addr,int value);
void peek(Robot rob,int addr);
int go_to(int num);
//A voir comment implementer int checkif()
int random(int num);
int cardinal(Arene arene);
int self(Robot rob);
double speed(Robot rob);
double state(Arene arene,int num);
double gpsx(Arene arene,int num);
double gpsy(Arene arene,int num);
void engine(Robot rob,double angle,double speed);
int shoot(Robot rob,Arene arene,double angle);
double angle(double x1,double y1,double x2,double y2);
double targetx(double x1,double angle,double length);
double targety(double y1,double angle,double length);
double distance(double x1,double y1,double x2,double y2);
#endif 