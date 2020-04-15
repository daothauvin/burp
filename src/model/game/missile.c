#include "missile.h"
#include "../../define.h"
Missile create(double pos_x,double pos_y,double speed,double angle,Robot rob,double explo_dist){
    Missile m = malloc(sizeof(struct missile_impl));
    m->pos_x = pos_x;
    m->pos_y = pos_y;
    m->speed = speed;
    m->angle = angle;
    m->owner = rob;
    m->parcouru_distant = 0;
    m->explosion_distant = explo_dist;
    m->will_explode = 0;    
    return m;
}
void update_pos_missile(Missile m){
    double speed = (m->parcouru_distant + m->speed >= m->explosion_distant)?
    m->explosion_distant - (m->speed + m->parcouru_distant):m->speed;
    double x = m->pos_x + (speed * cos(m->angle));
    double y = m->pos_y + (speed * sin(m->angle));
    if(x>=size_arena_x){
        x = size_arena_x;
        m->will_explode = 1;
    }
    if(y>=size_arena_y){
        x = size_arena_y;
        m->will_explode = 1;
    }
    m->parcouru_distant += speed;
    m->pos_x = x;
    m->pos_y = y;

}
void check_distant(Missile m){
    if(m->parcouru_distant>=m->explosion_distant) m->will_explode = 1;
}
short will_explode(Missile m){
    return m->will_explode;
}
Point explode(Missile mis){
    Point p = malloc(sizeof(struct point));
    p->x = mis->pos_x;
    p->y = mis->pos_y;
    return p;
}
void collision_with_missiles(Robot rob,Missile m){
    double dx = rob->pos->x - m->pos_x;
    double dy = rob->pos->y - m->pos_y;
    double d = sqrt((dx*dx) + (dy*dy));
    if(rob->robot_hitbox > d) m->will_explode = 1;
}