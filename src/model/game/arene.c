#include "arene.h"

Arene create_arene()
{
    Arene a = malloc(sizeof(struct arene_impl));
    a->list_missile = malloc(sizeof(struct missile_impl) * missile_by_robot * number_of_robots);
    a->list_robots = malloc(sizeof(struct robot_impl) * number_of_robots);
    a->nb_missiles = 0;
    a->nb_robots = 0;
    return a;
}
int add_missile(Arene arene, Missile missile)
{
    if (arene->nb_missiles == missile_by_robot * number_of_robots)
        return -1;
    arene->list_missile[arene->nb_missiles] = missile;
    arene->nb_missiles += 1;
    return arene->nb_missiles - 1;
}
int remove_missile(Arene arene, Missile missile)
{
    for (int i = 0; i < arene->nb_missiles; ++i)
    {
        if (arene->list_missile[i] == missile)
        {
            arene->list_missile[i] = arene->list_missile[arene->nb_missiles];
            free(missile);
            missile = NULL;
            arene->nb_missiles -= 1;
            return 0;
        }
    }
    return -1;
}
int add_robot(Arene arene, Robot rob)
{
    if (arene->nb_robots == number_of_robots)
        return -1;
    arene->list_robots[arene->nb_robots] = rob;
    arene->nb_robots += 1;
    return arene->nb_robots - 1;
}
int remove_robot(Arene arene, Robot rob)
{
    for (int i = 0; i < arene->nb_robots; ++i)
    {
        if (arene->list_robots[i] == rob)
        {
            arene->list_robots[i] = arene->list_robots[arene->nb_robots];
            arene->nb_robots -= 1;
            return 0;
        }
    }
    return -1;
}

void free_arena(Arene arene)
{
    free(arene);
}
