#include "ui.h"

/**
 *  Draw a rectangle.
 */

static void drawRectangle(int x, int y, int length, int height, char* title) {
	WINDOW* win = subwin(stdscr, height, length, y, x);
	box(win, ACS_VLINE, ACS_HLINE);
	mvprintw(y, x + 2, "%s", title);
	wrefresh(win);
	delwin(win);
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
				break;
		}
	}
}

/**
 *  Draw the arena
 */

static void drawArena() {
	drawRectangle(0, 0, COLS, LINES, "BURP");
	drawRectangle(2, 1, 80, 40, "Arena");
	drawRectangle(82, 1, 67, 11, "Title Burp");
	drawRectangle(82, 12, 67, 20, "Robot Info");
	drawRectangle(84, 13, 15, 18, "1");
	drawRectangle(100, 13, 15, 18, "2");
	drawRectangle(116, 13, 15, 18, "3");
	drawRectangle(132, 13, 15, 18, "4");
	drawRectangle(82, 32, 67, 9, "Log");
	refresh();
}

/**
 * Is called when the signal SIGWINCH is called :
 * Resize the terminal when the user try to resize it
 */

static void resizeHandler() {
	clear();
	system("printf '\e[3;10;10t\e[8;42;150t'");
	drawArena();
	sleep(1);
}

void init() {
	// Setting the terminal window on top-left of the screen and maximizing the size of it
	system("printf '\e[3;10;10t\e[8;42;150t'");
	sleep(1);

	// Initialisation of ncurses
	initscr();
	resize_term(42, 150);
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
