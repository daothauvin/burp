#include "controller.h"


// Pause var
static short paused = 0;
//Time between each turn
static int time_between = 1000000;

/**
 *  -Normally not- blocking functions that wait for user input to interact.
 * 	The different beheviours are :
 * 		Q - Quit
 */


short waitForInput() {
	
	cbreak();
	int diff = 0;
	nodelay(stdscr, TRUE);
	struct timeval start, cur;
	gettimeofday(&start, NULL);
    while (diff < time_between || paused) {
		int c = getch();
		switch (c) {
			case 'q':
			case 'Q':
				return 0;
			case '+':
				if(time_between > 100000) {
					time_between -= 100000;
					add_log("[+] Speeded up.");
				}
				else {
					add_log("[!] Max speed reached.");
				}
				break;
			case '-':
				if(time_between < 10000000) {
					time_between += 100000; 
					add_log("[-] Slowed down.");
				} 
				else {
					add_log("[!] Lowest speed reached.");
				}
				break;
			case 'p':
			case 'P':
				paused = !paused;
				if (paused) {
					add_log("[o] Game paused.");
				} else {
					add_log("[o] Game resumed.");
				}
				break;
			default:
				break;
		}
		gettimeofday(&cur, NULL);
		diff = (cur.tv_sec - start.tv_sec) * 1000000 + (cur.tv_usec - start.tv_usec);
	}
	return 1;
}
