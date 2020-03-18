/** 
 *         - ui.c & ui.h supply functions to use the textual interface -
 *
 *  Interface :
 * 
 * +------------------------------------------------------------------------------------+
 * | +-----------------------------------+   Robot_1  |  Robot_2  |  Robot_3  | Robot_4 |
 * | |                       #           |            |           |           |         |
 * | |                     # + #         |            |           |           |         |
 * | |                    3  #           |            | [Information on robots]         |
 * | |                                   |            |           |           |         |
 * | |            [Arena]                |            |           |           |         |
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
#include <unistd.h>
#include <signal.h>
#include <string.h>

void init();                        // Init the interface and NCurses and build the arena
void add_log(char* message);        // Add a message to the log
void update();                      // Update the arena : delete the components and replace them by fetching info
                                    // in the model
                                   

