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
Missile shoot(Robot rob,float angle);
float angle(float x1,float y1,float x2,float y2);
float targetx(float x1,float angle,float length);
float targety(float y1,float angle,float length);
float distance(float x1,float y1,float x2,float y2);