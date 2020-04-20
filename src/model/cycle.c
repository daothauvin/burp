#include "cycle.h"

static char *current[4] = {"None"};
static char *previous[4] = {"None"};
static char *next[4] = {"None"};

char *getCurrentCommand(int idRobot)
{
	return current[idRobot];
}

char *getPreviousCommand(int idRobot)
{
	return previous[idRobot];
}

char *getNextCommand(int idRobot)
{
	return current[idRobot];
}

short cycle(arena *a, int line[4], void *syntax_tree[4])
{

	for (int i = 0; i < 4; i++)
	{
		previous[i] = current[i];
	}
	//lire script pour action suivante
	for (int i = 0; i < get_nb_robot_arena(a); i++)
	{
		current[get_robot_id(get_robot_index(a, i))] = getLine(syntax_tree[get_robot_id(get_robot_index(a, i))], line[get_robot_id(get_robot_index(a, i))]);
		line[get_robot_id(get_robot_index(a, i))] = interprete(line[get_robot_id(get_robot_index(a, i))], syntax_tree[i], a, get_robot_index(a, i));
		next[get_robot_id(get_robot_index(a, i))] = getLine(syntax_tree[get_robot_id(get_robot_index(a, i))], line[get_robot_id(get_robot_index(a, i))]);
	}

	for (int i = 0; i < 4; i++)
	{
		current[i] = current[i];
	}

	//modifie positions : robot + missile
	for (int i = 0; i < get_nb_robot_arena(a); i++)
	{
		update_pos_robot(get_robot_index(a, i));
	}
	for (int i = 0; i < get_nb_missiles_arena(a); i++)
	{
		update_pos_missile(get_missile_index(a, i));
	}

	//test collision
	for (int i = 0; i < get_nb_robot_arena(a); i++)
	{
		for (int j = i + 1; j < get_nb_robot_arena(a); j++)
		{
			if (check_collision_robots(get_robot_index(a, i), get_robot_index(a, j)))
			{
				inflict_damage_from_collision(get_robot_index(a, i), get_robot_index(a, j));
			}
		}
	}

	for (int i = 0; i < get_nb_robot_arena(a); i++)
	{
		for (int j = 0; j < get_nb_missiles_arena(a); j++)
		{
			collision_with_missiles(get_robot_index(a, i), get_missile_index(a, j));
		}
	}

	//tue les robots morts
	for (int i = 0; i < get_nb_robot_arena(a); i++)
	{
		if(get_robot_health_points(get_robot_index(a, i)) <= 0)
		{
			remove_robot(a, get_robot_index(a, i));
		}
	}

	for (int i = 0; i < get_nb_missiles_arena(a); i++)
	{
		if (will_explode(get_missile_index(a,i)) == true)
		{
			point p;
			if(!explode(get_missile_index(a,i),&p)){
				continue;
			}
			for (int i = 0; i < get_nb_robot_arena(a); i++)
			{
				inflict_damage_from_missile(get_robot_index(a, i), p);
			}
			remove_missile(a, get_missile_index(a,i));
		}
	}

	return get_nb_robot_arena(a) != 0;
}
