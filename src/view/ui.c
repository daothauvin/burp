#include "ui.h"

/**
 *  Draw a rectangle.
 */

static void drawRectangle(int x, int y, int length, int height) {
	WINDOW* rect = subwin(stdscr, height, length, y, x);
    box(rect, ACS_VLINE, ACS_HLINE);
	free(rect);
}

/**
 *  Blocking functions that wait for user input to interact.
 * 	The different beheviours are :
 * 		Q - Quit
 * 		More to be added...
 */

static void waitForInput() {
	while (1) {
		int c = getch();
		switch (c) {
			case 'q':
			case 'Q':
				return;
			default:
			// Test Input (will be removed)
				if (isalpha(c)) {
					mvprintw(2, 2, "You typed [%c]...      ", c);
				} else {
					mvprintw(2, 2, "You typed something... ");
				}
				break;
		}
	}
}

/**
 *  Draw the arena
 */

static void drawArena() {
	drawRectangle(0, 0, COLS, LINES);
	mvprintw(1, 2, "COLS = %d, LINES = %d", COLS, LINES);	
	refresh();
}

/**
 * Is called when the signal SIGWINCH is called :
 * Resize the terminal when the user try to resize it
 */

static void resizeHandler() {
	clear();
	system("printf '\e[3;10;10t\e[8;40;150t'");
	drawArena();
	sleep(1);
}

void init() {
	// Setting the terminal window on top-left of the screen and maximizing the size of it
	system("printf '\e[3;10;10t\e[8;40;150t'");
	sleep(1);

	// Initialisation of ncurses
	initscr();
	resize_term(40, 150);
	noecho();
	signal(SIGWINCH, resizeHandler);

	// Drawing the arena
	drawArena();
	
	// Waiting user behaviour
	waitForInput();
	endwin();
}

int main(int argc, char** argv) {
	init();
	return 0;
}
