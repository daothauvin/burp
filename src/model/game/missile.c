#include "missile.h"
#include "../../define.h"
Missile create(double pos_x,double pos_y,double speed,double angle,Robot rob,double explo_dist){
    Missile m = malloc(sizeof(Missile));
    m->pos_x = pos_x;
    m->pos_y = pos_y;
    m->speed = speed;
    m->angle = angle;
    m->owner = rob;
    m->parcouru_distant = 0;
    m->explosion_distant = explo_dist;
    return m;
}
void update_pos_missile(Missile m){
    double x = m->pos_x + (m->speed * cos(m->angle));
    double y = m->pos_y + (m->speed * sin(m->angle));
    m->parcouru_distant += m->speed;
    m->pos_x = x;
    m->pos_y = y;
}
short check_distant(Missile m){
    if(m->parcouru_distant<m->explosion_distant){
        return 0;
    } else return -1;
}
Point explode(Missile mis){
    Point p = malloc(sizeof(Point));
    p->x = mis->pos_x;
    p->y = mis->pos_y;
    return p;
}