#include "missile.h"
#include "math.h"
#include "../../define.h"
#include <assert.h>
#include <string.h>

struct missile_impl
{
    double angle;
    point pos;
    double speed;
    double parcouru_distant;
    double explosion_distant;
    bool will_explode;
    robot *owner;
};

missile* create_missile(double pos_x, double pos_y, double angle, robot *rob, double explo_dist)
{
    assert((pos_x >= 0 && pos_x <= size_arena_x));
    assert((pos_y >= 0 && pos_y <= size_arena_y));
    assert(angle >= 0 && angle <=359);
    missile *m = malloc(sizeof(struct missile_impl));
    memset(m,0,sizeof(struct missile_impl));
    m->pos.x = pos_x;
    m->pos.y = pos_y;
    m->speed = missile_speed;
    m->angle = angle;
    m->owner = rob;
    m->parcouru_distant = 0;
    if(explo_dist >= max_range_explosion)
        m->explosion_distant = 7000;
    else 
        m->explosion_distant = explo_dist;
    m->will_explode = false;
    return m;
}
void update_pos_missile(missile *m)
{
    assert(m);
    double speed;
    if(m->parcouru_distant + m->speed >= m->explosion_distant){
        m->will_explode = true;
    } else {
        speed = m->speed;
    }
    double x = m->pos.x + (speed * cos(degree_to_radians(m->angle)));
    double y = m->pos.y + (speed * sin(degree_to_radians(m->angle)));
    if (x > size_arena_x || x < 0) {
        x = x < 0 ? 0 : size_arena_x - 1;
        m->will_explode = true;
    }
    if (y > size_arena_y || y < 0) {
        y = y < 0 ? 0 : size_arena_y - 1;
        m->will_explode = true;
    }
    m->parcouru_distant += speed;
    m->pos.x = x;
    m->pos.y = y;
}
bool will_explode(missile *m)
{
    assert(m);
    return m->will_explode;
}
bool explode(missile* mis,point *explode_point)
{
    if(!mis || !explode_point || mis->will_explode == false)
        return false;
    memmove(explode_point,(void*)&mis->pos,sizeof(point));
    return true;
}
void collision_with_missiles(robot *rob, missile *m)
{
    point rob_pos;
    get_robot_pos(rob,&rob_pos);
    double dx = rob_pos.x- m->pos.x;
    double dy = rob_pos.y - m->pos.y;
    double d = sqrt((dx * dx) + (dy * dy));
    if (robot_radius >= d)
        m->will_explode = true;
}
double get_missile_angle(missile *m){
    return m->angle;
}
double get_missile_speed(missile *m){
    return m->speed;
}
void get_missile_pos(missile *m, point *p){
    assert(m);
    memmove(p, &m->pos, sizeof(point));

}
double get_parcouru_distant(missile *m){
    return m->parcouru_distant;
}
robot* get_missile_owner(missile *m){
    assert(m);
    return m->owner;
}
double get_explosion_distant(missile *m){
    assert(m);
    return m->explosion_distant;
}
bool destroy_missile(missile **m){
    if(!m || !*m)
        return false;
    if((*m)->owner)
        decrement_nb_missile((*m)->owner);
    free(*m);
    *m = NULL;
    return true;
}