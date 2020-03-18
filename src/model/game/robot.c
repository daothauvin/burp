#include "robot.h"
#include <stdio.h>
#include <stdlib.h>
#include "../../define.h"

void update_hitbox(Robot rob){
    double p1_x = rob->pos->x - (double)size_robot_x;
    double p1_y = rob->pos->y + (double)size_robot_y;
    double p2_x = rob->pos->x + (double)size_robot_x;
    double p2_y = rob->pos->y + (double)size_robot_y;
    double p3_x = rob->pos->x - (double)size_robot_x;
    double p3_y = rob->pos->y - (double)size_robot_y;
    double p4_x = rob->pos->x + (double)size_robot_x;
    double p4_y = rob->pos->y - (double)size_robot_y;
    Hitbox h = rob->robot_hitbox;
    if(p1_x >= 0){
        h->p1->x = p1_x;
    } else h->p1->x = 0.0;
    if(p1_y <= (double)size_arena_y){
        h->p1->y = p1_y;
    } else h->p1->y = (double)size_arena_y;
    if(p2_x <= (double)size_arena_x){
        h->p2->x = p2_x;
    } else h->p2->x = (double)size_arena_x;
    if(p2_y <= (double)size_arena_y){
        h->p2->y = p1_y;
    } else h->p2->y = (double)size_arena_y;
    if(p3_x >= 0){
        h->p3->x = p3_x;
    } else h->p3->x = 0.0;
    if(p3_y >= 0){
        h->p3->y = p3_y;
    } else h->p3->y = 0.0;
    if(p4_x <= (double)size_arena_x){
        h->p4->x = p4_x;
    } else h->p4->x = (double)size_arena_x;
    if(p4_y >= 0){
        h->p4->y= p4_y;
    } else h->p4->y = 0.0;
}
Robot create_robot(){
    Robot p = malloc(sizeof(Robot));
    p->health_points = 100;
    p->pos = malloc(sizeof(Point));
    p->angle = 0.0;
    p->speed = 0.0;
    p->missiles = 0;
    p->robot_hitbox = malloc(sizeof(Hitbox));
    p->waiting_time;
    p->memory = malloc(robot_memory*(sizeof(int)));
    return p;
}

void initialize_robot(Robot rob,double x_1,double y_1,double angle,double speed){
    Robot rb = rob;
    rb->pos->x = x_1;
    rb->pos->y = y_1;
    rb->angle = angle;
    rb->speed = speed;
    update_hitbox(rb);
}

void update_pos_robot(Robot rob){
    float x2 =  rob->pos->x + (rob->speed * cos(rob->angle));
    float y2 =  rob->pos->y + (rob->speed * sin(rob->angle));
    rob->pos->x = x2;
    rob->pos->y = y2;
}
void modify_speed(Robot rob,double speed){
    rob->speed = speed;
}
void modify_angle(Robot rob,double angle){
    rob->angle = angle;
}
void inflict_damage_from_missile(Robot rob,int explotion_damage){
    rob->health_points -= explotion_damage;
}
void inflict_damage_from_collision(Robot rob1,Robot rob2){
    rob1->health_points-=collision_damage;
    rob2->health_points-=collision_damage;
    rob1->speed = 0;
    rob2->speed = 0;
}
short collision_robots(Robot rob1,Robot rob2){

}
short collision_with_missiles(Robot rob,Missile m){
    
}