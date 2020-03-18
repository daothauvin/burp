#include "commands.h"
#include "math.h"
int wait(Robot rob,int delay) {
    rob->waiting_time = delay;
    return delay;
}
void poke(Robot rob,int addr,int value){
    rob->memory[addr] = value;
}
void peek(Robot rob,int addr){
    return rob->memory[addr];
}
int go_to(int num){
    return num;
}
int random(int num){
    //Definir la ssrand(TIme(NULL));
    return rand() % num;
}
int cardinal(Arene arene){
    return sizeof(arene->list_robots) / sizeof(Robot);
}
int self(Robot rob){
    return rob->id;
}
double speed(Robot rob){
    rob->speed;
}
double state(Arene arene,int num){
    for(int i = 0 ; i < cardinal(arene);++i){
        if(arene->list_robots[i]->id == num) return arene->list_robots[i]->health_points;
    }
    return -1;
}
double gpsx(Arene arene,int num){
    for(int i = 0 ; i < cardinal(arene);++i){
        if(arene->list_robots[i]->id == num) return arene->list_robots[i]->pos->x;
    }
    return -1;
}
double gpsy(Arene arene,int num){
    for(int i = 0 ; i < cardinal(arene);++i){
        if(arene->list_robots[i]->id == num) return arene->list_robots[i]->pos->y;
    }
    return -1;
}
void engine(Robot rob,double angle,double speed){
        rob->angle = angle;
        rob->speed = speed;
}
int shoot(Robot rob,Arene arene,double angle){
    return 0;
}
double angle(double x1,double y1,double x2,double y2){
    double x = (x1 - x2);
    double y = (y1 - y2);
    double result = toDegrees(atan2(y, x));
    return result;//A verifier
    }
double targetx(double x1,double angle,double length){
    return x1 + (length * cos(angle));
}
double targety(double y1,double angle,double length){
    return y1 + (length * sin(angle));
}
double distance(double x1,double y1,double x2,double y2){
    return sqrt(pow(x1-x2,2) + pow(y1-y2,2));
}