#include "commands.h"

int wait(Robot rob,int delay) {
    rob->waiting_time = delay;
    return delay;
}
void poke(Robot rob,void* addr,int value){
    //To-do
}
void peek(Robot rob,void* addr){
    //To-do
}
int go_to(int num){
    //To-do
    return num;
}
int random(int num){
    //To-do
    //On déclare la seed ou ?
    return rand() % num;
}
int cardinal(Robot robots){
    return sizeof robots / sizeof(Robot);
}
int self(Robot rob){
    return rob->id;
}
float speed(Robot rob){
    rob->speed;
}
float state(Robot* rob,int num){
    for(int i = 0 ; i < cardinal(rob);++i){
        if(rob[i]->id == num) return rob[i]->health_points;
    }
    return -1;
}
float gpsx(Robot* rob,int num){
    for(int i = 0 ; i < cardinal(rob);++i){
        if(rob[i]->id == num) return rob[i]->pos->x;
    }
    return -1;
}
float gpsy(Robot* rob,int num){
    for(int i = 0 ; i < cardinal(rob);++i){
        if(rob[i]->id == num) return rob[i]->pos->y;
    }
    return -1;
}
void engine(Robot rob,float angle,float speed){
        rob->angle = angle;
        rob->speed = speed;
}
int shoot(Robot rob,Arene arene,double angle,double explo_dist){
    if(rob->missiles!=missile_by_robot){
        Missile m = create(rob->pos->x,rob->pos->y,missile_speed,angle,rob,explo_dist);
        add_missile(arene,m);
        rob->missiles +=1;
        return 0;
    } else return -1;
}
double angle(double x1,double y1,double x2,double y2){
    double x = (x1 - x2);
    double y = (y1 - y2);
    double result = (atan2(y, x)*(180/M_PI)); 
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
