/*
	robot management

	TODO: How to detect a missile close to a robot?
		  
*/
/* Robot's hitbox, the hitbox of a robot is represented
   by a moving square of size 10 by 10 centred on the 
   robot's actual position
   It might affect the robot's collision to missile 
   or others robots
   the representation would look like that
   p1 * * * p2
   *		*
   *    x   *
   * 		*
   p3 * * * p4
   Where x is the robot
*/

#include "missile.h"

typedef struct{
	float x;
	float y;
}*Point;
typedef struct{
	Point p1;
	Point p2;
	Point p3;
	Point p4;
}*Hitbox;

typedef struct
{
	int id;
	float health_points;// Represented as a percentage
	Point pos; 
	float angle;
	float speed;// Represented as a percentage
	int missiles;//Number of missile in the area currently
	Hitbox robot_hitbox;//robot hitbox size
	int waiting_time;//cycle delay
}*Robot;

//Functions prototypes
// Allocate a robot at a time
Robot create_robot();
//Allocate multiple robots at the same time
Robot *create_robots();
//allocate a robot with the script's contents
void initialize_robot(Robot rob,float x_1,float y_1,float angle,float speed);
void update_hitbox(Robot rob);
void update_pos_robot(Robot rob); // Fixed depending on angle and speed every cycle
void modify_speed(Robot rob,float speed);
void modify_angle(Robot rob,float angle);
void inflict_damage_from_missile(Robot rob,int explotion_damage);
void inflict_damage_from_collision(Robot rob1,Robot rob2);
short collision_robots(Robot rob1,Robot rob2);
short collision_with_missiles(Robot rob,Missile m);


