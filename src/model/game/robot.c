#include "robot.h"
Robot create_robot(){
    Robot p = malloc(sizeof(struct robot_impl));
    Point p0 = malloc(sizeof(struct point));
    p->robot_id = malloc(sizeof(char)*robot_name_length);
    p->health_points = 100;
    p->pos = p0;
    p->pos->x = 0.0;
    p->pos->y = 0.0;
    p->angle = 0.0;
    p->speed = 0.0;
    p->missiles = 0;
    p->waiting_time = 0;
    p->robot_hitbox = robot_radius;
    p->memory = malloc(robot_memory*(sizeof(int)));
    return p;
}

void initialize_robot(Robot rob,double x_1,double y_1,double angle,double speed,int id){
    Robot rb = rob;
    rb->pos->x = x_1;
    rb->pos->y = y_1;
    rb->angle = angle;
    rb->speed = speed;
    rb->id = id;
}

void update_pos_robot(Robot rob){
    float x2 =  rob->pos->x + (rob->speed * cos(rob->angle));
    float y2 =  rob->pos->y + (rob->speed * sin(rob->angle));
    if(x2 > size_arena_x){
        rob->pos->x = size_arena_x;
        rob->speed = 0.0;
        rob->health_points -= collision_damage;
    } else rob->pos->x = x2;
    if(y2 > size_arena_y){
        rob->pos->y = size_arena_y;
        rob->speed = 0.0;
        rob->health_points -= collision_damage;
    } else rob->pos->y = y2;
}

void modify_speed(Robot rob,double speed){
    rob->speed = speed;
}
void modify_angle(Robot rob,double angle){
    rob->angle = angle;
}
void inflict_damage_from_missile(Robot rob,Point p){
    double dx = rob->pos->x - p->x;
    double dy = rob->pos->y - p->y;
    double d = sqrt((dx*dx) + (dy*dy));
    if(d<low_range) rob->health_points-=damage_explosion_low_range;
    else if (d<middle_range) rob->health_points-=damage_explosion_middle_range;
    else if (d<high_range) rob->health_points-=damage_explosion_high_range;
}
void inflict_damage_from_collision(Robot rob1,Robot rob2){
    rob1->health_points-=collision_damage;
    rob2->health_points-=collision_damage;
    rob1->speed = 0;
    rob2->speed = 0;
}
short check_collision_robots(Robot rob1,Robot rob2){
    double dx = rob1->pos->x - rob2->pos->x;
    double dy = rob1->pos->y - rob2->pos->x;
    double d = sqrt((dx*dx) + (dy*dy));
    return rob1->robot_hitbox + rob2->robot_hitbox > d ? 1 : 0;
}
