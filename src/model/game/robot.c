#include "robot.h"
Robot create_robot(){
    Robot p = malloc(sizeof(struct robot));
    Point p0 = malloc(sizeof(struct point));
    Point p1 = malloc(sizeof(struct point));
    Point p2 = malloc(sizeof(struct point));
    Point p3 = malloc(sizeof(struct point));
    Point p4 = malloc(sizeof(struct point));
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
    if(!rob1 || !rob2) return -1;
    rob1->health_points -= collision_damage;
    rob2->health_points -= collision_damage;
    return 1;
}
short check_collision_robots(Robot rob1,Robot rob2){
    return 1;
}
short collision_robots_with_walls(Robot rob){
    return 1;
}
/*

int main(){
    Robot rob = create_robot();
    initialize_robot(rob,12.0,12.0,32.1,33.4,0);
    printf("%d %f %f %f %f\n",rob->id,rob->pos->x,rob->pos->y,rob->angle,rob->speed);
    printf("%ld",sizeof(rob));
}
*/
