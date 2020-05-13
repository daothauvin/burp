/** 
 *         - controler.c & controler.h supply functions to interact with the textual interface -
 */

#include "../view/ui.h"
/// \cond
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/time.h>
/// \endcond

/** 
* Check for user keyboard input.
* Return 0 if the user asked to stop the program.
* If not return 1.
*/
short waitForInput();                   

