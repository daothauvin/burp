#include "commands.h"
#include "../../view/ui.h"
int wait_robot(robot *rob, unsigned int delay)
{
    set_waiting_time_robot(rob, delay);
    return get_waiting_time_robot(rob);
}
bool poke(robot *rob, int addr, int value)
{
    return poke_memory_at(rob, value, addr);
}
int peek(robot *rob, int addr)
{
    return peek_memory_at(rob, addr);
}
int go_to(int num)
{
    return num;
}
int randoms(int num)
{
    return rand() % num;
}
int cardinal(arena *arena)
{
    return get_nb_robot_arena(arena);
}
int self(robot *rob)
{
    return get_robot_id(rob);
}
int speed(robot *rob)
{
    return get_robot_speed(rob);
}
int state(arena *arena, int num)
{
    for (int i = 0; i < cardinal(arena); ++i) {
        if (get_robot_id(get_robot_index(arena, i)) == num)
            return get_robot_health_points(get_robot_index(arena,i));
    }
    return 0;
}
double gpsx(arena *arena, int num)
{
    for (int i = 0; i < cardinal(arena); ++i) {
        if (get_robot_id(get_robot_index(arena, i)) == num) {
            point rob_point;
            get_robot_pos(get_robot_index(arena, i), &rob_point);
            return rob_point.x;
        }
    }
    return -1;
}
double gpsy(arena *arena, int num)
{
    for (int i = 0; i < cardinal(arena); ++i) {
        if (get_robot_id(get_robot_index(arena, i)) == num) {
            point rob_point;
            get_robot_pos(get_robot_index(arena, i), &rob_point);
            return rob_point.y;
        }
    }
    return -1;
}
void engine(robot *rob, double angle, double speed)
{
    if (!rob)
        return;
    set_robot_angle(rob, angle);
    set_robot_speed(rob, speed);
}
bool shoot(robot *rob, arena *arena, double angle, double explo_dist)
{
    if (rob && arena && get_robot_nb_missiles(rob) != missile_by_robot) {
        point rob_point;
        get_robot_pos(rob, &rob_point);
        missile *m = create_missile(rob_point.x,rob_point.y, angle, rob, explo_dist);
        add_missile(arena, m);
        increment_nb_missile(rob);
        return true;
    }
    else
        return false;
}
double angle(double x1, double y1, double x2, double y2)
{
    double zero = 0;
    double dist = distance(x1,y1,x2,y2);
    if(dist == zero)
        return 0.0;
    double delta_x = x2 - x1;
    double delta_y = y2 - y1;
    //double x = delta_y / delta_x;
    double result = atan2(delta_y,delta_x);
    double result_degree = result * (180 / M_PI);
    fprintf(stderr,"angle %f\n",result_degree);
    return result_degree;
}
double targetx(double x1, double angle, double length)
{
    return x1 + (length * (cos(degree_to_radians(angle))));
}
double targety(double y1, double angle, double length)
{
    return y1 + (length * (sin(degree_to_radians(angle))));
}
double distance(double x1, double y1, double x2, double y2)
{
    double d = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
	fprintf(stderr,"dist between me (%f,%f) and target (%f,%f) : %f\n",x1,y1,x2,y2,d);		
    return d;
}