/** 
 *         - ui.c & ui.h supply functions to use the textual interface -
 */

#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <time.h>
#include "../model/game/robot.h"
#include "../model/game/missile.h"
#include "../model/game/arene.h"
#include "../define.h"


void init();
void anim_begin();
void waitForInput();
int  quit();

void add_log(char* message);
void add_action(char* action, int id);

void updateArena(arena* arena);
