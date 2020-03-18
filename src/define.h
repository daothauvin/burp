/*

	global variables' definitions
	
*/
#define robot_memory 256
/*
	Sizes
*/
#define size_arena_x 10000 
#define size_arena_y 10000

#define size_robot_x 10
#define size_robot_y 10

/*
	Speeds
*/
//max speed in unities by cycle -> move of 10 unities max by cycle
#define max_speed 10 
#define missile_speed 500

/*
	Ranges
*/
//last range to be touched by an explosion (in unities)
#define high_range 400
//pourcent of damage from an explosion on high range
#define damage_explosion_high_range 3

//middle range to be touched by an explosion (in unities)
#define middle_range 200
//pourcent of damage from an explosion on middle range
#define damage_explosion_middle_range 5

//first range to be touched by an explosion (in unities)
#define low_range 50
//pourcent of damage from an explosion on low range
#define damage_explosion_low_range 10

/*
	Time
*/
//time between two loops in seconds [can change]
#define time_loop 5


/*
	Limits
*/
//maximum for the number of missile present in the arena for each robot
#define missile_by_robot 2

//maximum range a missile can go in unities
#define max_range_explosion 7000