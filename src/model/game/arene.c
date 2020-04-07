#include "arene.h"

Arene create_arene(){
    Arene a = malloc(sizeof(Arene));
    a->list_missile = malloc(sizeof(Missile)*missile_by_robot*number_of_robots);
    a->list_robots = malloc(sizeof(Robot)*number_of_robots);
    a->nb_missiles = 0;
    return a;
}
//Robot 3 
// -> List_missile[4] et [5]
int add_missile(Arene arene,Missile missile){
    arene->list_missile[arene->nb_missiles] = missile;
    arene->nb_missiles +=1;
    return arene->nb_missiles - 1;
}
int remove_missile(Arene arene,Missile missile){
    for(int i = 0; i  < arene->nb_missiles;++i){
        if(arene->list_missile[i]==missile){
            arene->list_missile[i] = arene->list_missile[arene->nb_missiles];
            arene->nb_missiles -= 1;
            return 0;
        }
    }
    return -1;
}
int add_robot(Arene arene,Robot rob){
    arene->list_robots[arene->nb_robots] = rob;
    arene->nb_robots+=1;
    return arene->nb_robots - 1;
}
int remove_robot(Arene arene,Robot rob){
    for(int i = 0; i  < arene->nb_robots;++i){
        if(arene->list_robots[i]==rob){
            arene->list_robots[i] = arene->list_robots[arene->nb_robots];
            arene->nb_robots -= 1;
            return 0;
        }
    }
    return -1;
}
