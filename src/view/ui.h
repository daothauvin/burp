/** 
 *         - ui.c & ui.h supply functions to use the textual interface -
 */

#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include "../model/game/robot.h"
#include "../model/game/missile.h"
#include "../define.h"

void init();
void add_log(char* message);