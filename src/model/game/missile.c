#include "missile.h"
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

missile* create(double pos_x, double pos_y, double angle, robot *rob, double explo_dist)
{
    missile *m = malloc(sizeof(missile));
    m->pos.x = pos_x;
    m->pos.y = pos_y;
    m->speed = missile_speed;
    m->angle = angle;
    m->owner = rob;
    m->parcouru_distant = 0;
    m->explosion_distant = explo_dist;
    m->will_explode = 0;
    return m;
}
void update_pos_missile(missile *m)
{
    assert(m);
    double speed = (m->parcouru_distant + m->speed >= m->explosion_distant) ? m->explosion_distant - (m->speed + m->parcouru_distant) : m->speed;
    double x = m->pos.x + (speed * cos(degree_to_radians(m->angle)));
    double y = m->pos.y + (speed * sin(degree_to_radians(m->angle)));
    if (x >= size_arena_x) {
        x = size_arena_x;
        m->will_explode = 1;
    }
    if (y >= size_arena_y) {
        x = size_arena_y;
        m->will_explode = 1;
    }
    m->parcouru_distant += speed;
    m->pos.x = x;
    m->pos.y = y;
    m->will_explode = (m->parcouru_distant >= m->explosion_distant) ? true : false;
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
    if (robot_radius> d)
        m->will_explode = true;
}
double get_missile_angle(missile *m);
double get_missile_speed(missile *m);
void get_missile_pos(missile *m, point *p);
double get_parcouru_distant(missile *m);
bool get_missile_owner(missile *m, robot **res_rob);