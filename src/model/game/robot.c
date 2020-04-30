#include "robot.h"
#include <string.h>
#include <stdbool.h>

double degree_to_radians(double x)
{
    return x * (M_PI/180);
}

struct robot_impl
{
    char robot_name[robot_name_length];
    int health_points; // Represented as a percentage
    double angle;
    int speed; // Represented as a percentage
    point pos;
    int id;
    int missiles; //Number of missile in the area currently
    int memory[robot_memory];
    unsigned int waiting_time; //cycle delay
};

robot *create_robot(double x_1, double y_1, double angle, int speed, int id)
{
    robot *rob = malloc(sizeof(struct robot_impl));
    memset(rob, 0, sizeof(struct robot_impl));
    rob->health_points = 100;
    rob->pos.x = x_1;
    rob->pos.y = y_1;
    rob->angle = angle;
    rob->speed = speed;
    rob->id = id;
    return rob;
}
void update_pos_robot(robot *rob)
{
    float zero = 0;
    if (rob->waiting_time > 0) {
        rob->waiting_time--;
        return;
    }
    float x2 = rob->pos.x - (rob->speed * cos(degree_to_radians(rob->angle)));
    float y2 = rob->pos.y + (rob->speed * sin(degree_to_radians(rob->angle)));
    int collision_radius = robot_radius/2;
    if (x2 > size_arena_x - collision_radius || x2 < collision_radius) {
        rob->pos.y = x2 < collision_radius ? collision_radius : size_arena_x - collision_radius;
        rob->speed = zero;
        rob->health_points = rob->health_points - collision_damage > 0 ? rob->health_points - collision_damage : 0;
    }
    else
        rob->pos.x = x2;

    if (y2 > size_arena_y - collision_radius || y2 < collision_radius) {
        rob->pos.y = y2 < collision_radius ? collision_radius : size_arena_y - collision_radius;
        rob->speed = zero;
        rob->health_points = rob->health_points - collision_damage > 0 ? rob->health_points - collision_damage : 0;
    }
    else
        rob->pos.y = y2;

}

void modify_speed(robot *rob, int speed)
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
        rob->health_points = rob->health_points - damage_explosion_low_range > 0 ? rob->health_points - damage_explosion_low_range: 0;
    else if (d < middle_range)
        rob->health_points = rob->health_points - damage_explosion_middle_range > 0 ? rob->health_points - damage_explosion_middle_range: 0;
    else if (d < high_range)
        rob->health_points = rob->health_points - damage_explosion_high_range > 0 ? rob->health_points - damage_explosion_high_range: 0;
}
void inflict_damage_from_collision(robot *rob1, robot *rob2)
{
    float zero = 0;
    rob1->health_points = rob1->health_points - collision_damage > 0 ? rob1->health_points - collision_damage : 0;;
    rob2->health_points = rob2->health_points - collision_damage > 0 ? rob2->health_points - collision_damage : 0;;
    rob1->speed = zero;
    rob2->speed = zero;
}
bool check_collision_robots(robot *rob1, robot *rob2)
{
    double dx = rob1->pos.x - rob2->pos.x;
    double dy = rob1->pos.y - rob2->pos.y;
    double d = sqrt((dx * dx) + (dy * dy));
    return 2 * robot_radius > d ? true : false;
}
int get_robot_id(robot *rob)
{
    return rob->id;
}
char *get_robot_name(robot *rob)
{
    return rob->robot_name;
}
unsigned int get_robot_health_points(robot *rob)
{
    return rob->health_points;
}
double get_robot_angle(robot *rob)
{
    return rob->angle;
}
bool set_robot_angle(robot *rob, double angle)
{
    rob->angle = angle;
    return true;
}
int get_robot_speed(robot *rob)
{
    return rob->speed;
}
bool set_robot_speed(robot *rob, int speed)
{
    float zero = 0;
    if (speed < zero && speed > max_speed) {
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
void increment_nb_missile(robot *rob){
    rob->missiles++;
}
int get_waiting_time_robot(robot *rob)
{
    return rob->waiting_time;
}
void set_waiting_time_robot(robot *rob, unsigned int waiting_time)
{
    rob->waiting_time = waiting_time;
}
bool poke_memory_at(robot *rob, int data, int pos)
{
    if (pos >= robot_memory)
        return false;
    rob->memory[pos] = data;
    return true;
}
int peek_memory_at(robot *rob, int i)
{
    if (i > robot_memory)
        return -1;
    return rob->memory[i];
}
void decrement_nb_missile(robot *rob)
{
    if(rob->missiles > 0)
        rob->missiles--;
}
void destroy_robot(robot **rob){
    if(!rob || !*rob)
        return ;
    free(*rob);
    *rob = NULL;
}