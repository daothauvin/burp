#include "arene.h"
#include <string.h>

struct arena_impl
{
    robot **list_robots;
    missile **list_missile;
    unsigned int nb_missiles;
    unsigned int nb_robots;
};

arena *create_arena()
{
    arena *a = malloc(sizeof(struct arena_impl));
    a->list_missile = malloc(sizeof(missile*) * missile_by_robot * number_of_robots);
    a->list_robots = malloc(sizeof(robot*) * number_of_robots);
    a->nb_missiles = 0;
    a->nb_robots = 0;
    return a;
}
int add_missile(arena *arena, missile *m)
{
    if (arena->nb_missiles == missile_by_robot * number_of_robots)
        return -1;
    arena->list_missile[arena->nb_missiles] = m;
    return arena->nb_missiles++;
}
bool remove_missile(arena *arena, missile *m)
{
    if (!arena || !m)
        return false;
    for (int i = 0; i < arena->nb_missiles; ++i) {
        if (arena->list_missile[i] == m) {
            arena->nb_missiles -= 1;
            arena->list_missile[i] = arena->list_missile[arena->nb_missiles];
            free(m);
            m = NULL;
            return true;
        }
    }
    return false;
}
int add_robot(arena *arena, robot *rob)
{
    if (arena->nb_robots == number_of_robots)
        return -1;
    arena->list_robots[arena->nb_robots] = rob;
    return arena->nb_robots++;
}
bool remove_robot(arena *arena, robot* rob)
{
    for (int i = 0; i < arena->nb_robots; ++i) {
        if (arena->list_robots[i] == rob) {
            arena->nb_robots -= 1;
            arena->list_robots[i] = arena->list_robots[arena->nb_robots];
            return 0;
        }
    }
    return -1;
}

void freeArena(arena **arena)
{
    if (!arena || !*arena)
        return;
    for (size_t i = 0; i < (*arena)->nb_missiles; i++)
    {
        destroy_missile(&(*arena)->list_missile[i]);
    }
    for (size_t i = 0; i < (*arena)->nb_robots; i++)
    {
        destroy_robot(&(*arena)->list_robots[i]);
    }
    free((*arena)->list_missile);
    free((*arena)->list_robots);
    free(*arena);
    *arena = NULL;
}
int get_nb_missiles_arena(arena *arena)
{
    if(!arena)
        return -1;
    return arena->nb_missiles;
}
int get_nb_robot_arena(arena *arena)
{
    if(!arena)
        return -1;
    return arena->nb_robots;
}
robot *get_robot_per_id(arena *arena, int id)
{
    if (!arena)
        return NULL;
    for (int i = 0; i < arena->nb_robots; ++i) {
        if (get_robot_id(arena->list_robots[i]) == id) {
            return arena->list_robots[i];
        }
    }
    return NULL;
}
robot *get_robot_index(arena *arena, int indx)
{
    if (!arena || indx >= arena->nb_robots)
        return NULL;
    return arena->list_robots[indx];
}
missile *get_missile_index(arena *arena, int indx)
{
    if (!arena || indx >= arena->nb_missiles)
        return NULL;
    return arena->list_missile[indx];
}
