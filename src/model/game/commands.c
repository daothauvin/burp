#include "commands.h"

int wait_robot(Robot rob,int delay) {
    rob->waiting_time = delay<0 ? 0 : delay;
    return delay;
}
void poke(Robot rob,int addr,int value){
    rob->memory[addr] = value;
}
int peek(Robot rob,int addr){
    return rob->memory[addr];
}
int go_to(int num){
    return num;
}
int randoms(int num){
    //Definir la ssrand(TIme(NULL));
    return rand() % num;
}
int cardinal(Arene arene){
    return number_of_robots;
}
int self(Robot rob){
    return rob->id;
}
double speed(Robot rob){
    return rob->speed;
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
int shoot(Robot rob,Arene arene,double angle,double explo_dist){
    if(rob->missiles!=missile_by_robot){
        Missile m = create(rob->pos->x,rob->pos->y,missile_speed,angle,rob,explo_dist);
        add_missile(arene,m);
        rob->missiles +=1;
        return 0;
    } else return -1;
}
double angle(double x1,double y1,double x2,double y2){
    double result = acos(abs(x1 - x2)/distance(x1,x2,y1,y2)); 
    double result_degree = result * (180/M_PI);
    return result_degree;//A verifier
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