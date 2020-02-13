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
typedef struct{
	float p1;
	float p2;
	float p3;
	float p4;
}hitbox;

typedef struct
{
	float health_points;// Represented as a percentage
	float x_pos; 
	float y_pos;
	float angle;
	float speed;// Represented as a percentage
	int missiles;//Number of missile in the area currently
	hitbox *robot_hitbox;//robot hitbox size
}robot;

//Functions prototypes
// Allocate a robot at a time
robot create_robot();
//Allocate multiple robots at the same time
robot * create_robots();
//allocate a robot with the script's contents
void initialize_robot(robot *rob,float x,float y,float angle,float speed);
void update_pos(robot *rob); // Fixed depending on angle and speed every cycle
void modify_speed(robot *rob,float speed);
void modify_angle(robot *rob,float angle);
void modify_angle(robot rob,float goto_x,float goto_y);
void inflict_damage_from_missile(robot rob,int explotion_damage);
void inflict_damage_from_collision(robot rob1,robot rob2);
short collision_robots(robot *rob,robot *rob);
short collision_robots(robot *rob,missile *m);


