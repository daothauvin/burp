/** 
 *         - ui.c & ui.h supply functions to use the textual interface -
 */

#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include "../model/game/robot.h"
#include "../define.h"

void init();                        // Init the interface and NCurses and build the arena
void add_log(char* message);        // Add a message to the log

    // More to come
