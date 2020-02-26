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
				return;
			case '\n':
				mvprintw(2, 2, "You typed [\\n]...", c);
				break;
			default:
				mvprintw(2, 2, "You typed [%c]...", c);
				break;
		}
	}
}

void init() {
	// Setting the terminal window on top-left of the screen and maximizing the size of it
	system("printf '\e[3;0;0t\e[9;1t'");
	sleep(1);

	// Initialisation of ncurses
	initscr();
	resize_term(47, 158);
	noecho();

	// Drawing the arena
	drawRectangle(0, 0, COLS, LINES);
	mvprintw(1, 2, "COLS = %d, LINES = %d", COLS, LINES);	
	refresh();
	
	// Waiting user behaviour
	waitForInput();
	endwin();
}

int main(int argc, char** argv) {
	init();
	return 0;
}

// gcc ui.c -Wall -g -o ui_test -lncurses
