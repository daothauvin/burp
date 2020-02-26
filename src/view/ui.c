#include "ui.h"

static void drawRectangle(int x, int y, int length, int height) {
	// Top
	for (size_t i = x; i < length + x; i++)
		mvaddch(y, i, '-');
	// Bottom
	for (size_t i = x; i < length + x; i++)
		mvaddch(y + height, i, '-');
	// Right
	for (size_t i = y; i < height + y; i++)
		mvaddch(i, x, '|');
	// Left
	for (size_t i = y; i < height + y; i++)
		mvaddch(i, x + length, '|');
	// Corners
	mvaddch(y, x, '+');
	mvaddch(y + height, x, '+');
	mvaddch(y, x + length, '+');
	mvaddch(y + height, x + length, '+');
}

int main(int argc, char** argv) {
	initscr();						/* Start curses mode 		  */
	signal(SIGWINCH, NULL);
	drawRectangle(0, 0, COLS - 1, LINES - 1);
	
	move(2, 2);
	printw("COLS = %d, LINES = %d", COLS, LINES);	/* Print Hello World		  */
	refresh();			        	/* Print it on to the real screen */
	getch();	        			/* Wait for user input */
	endwin();			        	/* End curses mode		  */
	return 0;
}

// gcc ui.c -Wall -g -o ui_test -lncurses