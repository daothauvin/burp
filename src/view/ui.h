/** 
 *         - ui.c & ui.h vont fournir les fonctions à utiliser pour la gestion de l'affichage -
 *
 *  Schéma de l'interface :
 * 
 * +------------------------------------------------------------------------------------+
 * | +-----------------------------------+   Robot_1  |  Robot_2  |  Robot_3  | Robot_4 |
 * | |                       #           |            |           |           |         |
 * | |                     # + #         |            |           |           |         |
 * | |                    3  #           |          [Informations sur les robots]       |
 * | |                                   |            |           |           |         |
 * | |            [Arène]                |            |           |           |         |
 * | |                                   |                                              |
 * | |                 1                 |  +-----------------------------------------+ |
 * | |        4                          |  |  > #1 has inflicted 35 dmg to #3.       | |
 * | |                     +             |  |  >                                      | |
 * | |                                   |  |                [Log]                    | |
 * | |                        2          |  |                                         | |
 * | +-----------------------------------+  +-----------------------------------------+ |
 * +------------------------------------------------------------------------------------+
 * 
 * 
 * ╭───╮  +---+
 * │   │  |   |
 * ╰───╯  +---+
 * 
 */

#include <ncurses.h>
#include <stdlib.h>

// #include "../game/missile.h"
// #include "../game/robot.h"


void init();                        // Construit l'affichage avec l'arène, les informations et le log vide
void add_log(char* message);        // Ajoute une information à afficher dans le log
void update();                      // Supprime puis reécrit les informations ainsi que les éléments dans l'arène, 
                                    //  en les cherchant dans le modèle (robots, missiles, explosions.. etc)

