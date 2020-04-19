#include "robot.h"
#include <string.h>
#include <stdbool.h>
struct robot_impl
{
    char *robot_name;
    double health_points; // Represented as a percentage
    double angle;
    double speed; // Represented as a percentage
    point pos;
    int id;
    int missiles; //Number of missile in the area currently
    int *memory;
    unsigned int waiting_time; //cycle delay
};

robot *create_robot()
{
    robot *rob = malloc(sizeof(struct robot_impl));
    rob->robot_name = malloc(sizeof(char) * robot_name_length);
    rob->memory = malloc(robot_memory * (sizeof(int)));
    memset(rob, 0, sizeof(struct robot_impl));
    rob->health_points = 100;
    return rob;
}

void initialize_robot(robot *rob, double x_1, double y_1, double angle, double speed, int id)
{
    rob->pos.x = x_1;
    rob->pos.y = y_1;
    rob->angle = angle;
    rob->speed = speed;
    rob->id = id;
}

void update_pos_robot(robot *rob)
{
    if (rob->waiting_time > 0)
    {
        rob->waiting_time--;
        return;
    }
    float x2 = rob->pos.x + (rob->speed * cos(rob->angle));
    float y2 = rob->pos.y + (rob->speed * sin(rob->angle));
    if (x2 > size_arena_x)
    {
        rob->pos.x = size_arena_x;
        rob->speed = 0.0;
        rob->health_points -= collision_damage;
    }
    else
        rob->pos.x = x2;
    if (y2 > size_arena_y)
    {
        rob->pos.y = size_arena_y;
        rob->speed = 0.0;
        rob->health_points -= collision_damage;
    }
    else
        rob->pos.y = y2;
}

void modify_speed(robot *rob, double speed)
{
    rob->speed = speed;
}
void modify_angle(robot *rob, double angle)
{
    rob->angle = angle;
}
void inflict_damage_from_missile(robot *rob, point p)
{
    double dx = rob->pos.x - p.x;
    double dy = rob->pos.y - p.y;
    double d = sqrt((dx * dx) + (dy * dy));
    if (d < low_range)
        rob->health_points -= damage_explosion_low_range;
    else if (d < middle_range)
        rob->health_points -= damage_explosion_middle_range;
    else if (d < high_range)
        rob->health_points -= damage_explosion_high_range;
}
void inflict_damage_from_collision(robot *rob1, robot *rob2)
{
    rob1->health_points -= collision_damage;
    rob2->health_points -= collision_damage;
    rob1->speed = 0;
    rob2->speed = 0;
}
short check_collision_robots(robot *rob1, robot *rob2)
{
    double dx = rob1->pos.x - rob2->pos.x;
    double dy = rob1->pos.y - rob2->pos.x;
    double d = sqrt((dx * dx) + (dy * dy));
    return 2 * robot_radius > d ? 1 : 0;
}
int get_robot_id(robot *rob)
{
    return rob->id;
}
char *get_robot_name(robot *rob)
{
    return rob->robot_name;
}
double get_robot_health_points(robot *rob)
{
    return rob->health_points;
}
double get_robot_angle(robot *rob)
{
    return rob->angle;
}
bool set_robot_angle(robot *rob, double angle)
{
    if (angle < 0 && angle > 359)
        return false;
    rob->angle = angle;
    return true;
}
double get_robot_speed(robot *rob)
{
    return rob->speed;
}
bool set_robot_speed(robot *rob, double speed)
{
    if (speed < 0 && speed > max_speed)
    {
        return false;
    }
    rob->speed = speed;
    return true;
}
void get_robot_pos(robot *rob, point *pos)
{
    assert(pos);
    memmove(pos, &rob->pos, sizeof(point));
}
int get_robot_nb_missiles(robot *rob)
{
    return rob->missiles;
}
int get_waiting_time_robot(robot *rob)
{
    return rob->waiting_time;
}
void set_waiting_time_robot(robot *rob, unsigned int waiting_time)
{
    rob->waiting_time = waiting_time;
}
bool add_memory_to_robot(robot *rob, int *data, int pos)
{
    if (pos > robot_memory)
        return false;
    memmove((void *)rob->memory + pos, data, sizeof(int));
    return true;
}
int get_memory_at_i(robot *rob, int i)
{
    if (i > robot_memory)
        return -1;
    return rob->memory[i];
}