/*
	differents commande usable in a script
*/
#ifndef COMMANDS_H
#define COMMANDS_H
#include "robot.h"
#include "missile.h"
#include "arene.h"
#include <math.h>
#include "../../define.h"
#include <stdio.h>
#include <stdlib.h>

int wait_robot(robot *rob,unsigned int delay);
bool poke(robot *rob, int addr, int value);
int peek(robot *rob, int addr);
int go_to(int num);
//A voir comment implementer int checkif()
int randoms(int num);
int cardinal(arena *arena);
int self(robot *rob);
double speed(robot *rob);
double state(arena *arena, int num);
double gpsx(arena *arena, int num);
double gpsy(arena *arena, int num);
void engine(robot *rob, double angle, double speed);
bool shoot(robot *rob, arena *arena, double angle, double explo_dist);
double angle(double x1, double y1, double x2, double y2);
double targetx(double x1, double angle, double length);
double targety(double y1, double angle, double length);
double distance(double x1, double y1, double x2, double y2);
#endif