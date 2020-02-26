#include "ui.h"

static void drawRectangle(int x, int y, int length, int height) {
	WINDOW* rect = subwin(stdscr, height, length, y, x);
    box(rect, ACS_VLINE, ACS_HLINE);
	free(rect);
}

void init() {
	// Initialisation
	initscr();
	
	// Drawing the arena
	drawRectangle(0, 0, COLS, LINES);
	mvprintw(1, 2, "COLS = %d, LINES = %d", COLS, LINES);	
	refresh();

	// Waiting user behaviour
	getch();
	endwin();
}

int main(int argc, char** argv) {
	init();
	return 0;
}

// gcc ui.c -Wall -g -o ui_test -lncurses