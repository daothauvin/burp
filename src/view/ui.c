#include "ui.h"

/**
 *  Global variable
 */

// Log 
char logs[5][60];
int full_log;
int cursor;
// Test
int cmpt = 0;

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
 *  Erase an area
 */

static void eraseArea(int x, int y, int length, int height) {
	char spaces[length]; 
	memset(spaces, ' ', length);
	spaces[length - 1] = '\0';
	for (int i = 0; i < height; i++) {
		mvprintw(y + i, x, spaces);
	}
}

/**
 *  Blur the info of a robot when he's dead.
 */

static void killRobotNb(int nbBot) {
	int x;
	int y = 14;

	switch(nbBot) {
		case 0:
			x = 85;
			break;
		case 1:
			x = 101;
			break;
		case 2:
			x = 117;
			break;
		case 3:
			x = 133;
			break;
		default:
			return;
	}
	attron(COLOR_PAIR(1));
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 13; j++) {
			mvprintw(i + y, j + x, " ");
		}
	}
	mvprintw(y + 7, x + 3, "[DEAD]");
	attroff(COLOR_PAIR(1));
}

/**
 *  Draw the Title
 */

static void drawTitle() {
	mvprintw(2, 89, "oooooooooo.        Basic Used for Robots Programming");
	mvprintw(3, 89, "`888'   `Y8b");
	mvprintw(4, 90, "888     888 oooo  oooo  oooo d8b oo.ooooo.       ;");
	mvprintw(5, 90, "888oooo888' `888  `888  `888""8P    888' `88b     [\"]/");
	mvprintw(6, 90, "888    `88b  888   888   888      888   888    /[_]");
	mvprintw(7, 90, "888    .88P  888   888   888      888   888     ] [");
	mvprintw(8, 89, "o888bood8P'   `V88V\"V8P' d888b     888bod8P'");
	mvprintw(9, 124, "888");
	mvprintw(10, 123, "o888o");
}

/**
 *  Print the log
 */

static void print_log() {
	eraseArea(84, 33, 60, 7);
	mvprintw(34, 85, logs[0]);
	mvprintw(35, 85, logs[1]);
	mvprintw(36, 85, logs[2]);
	mvprintw(37, 85, logs[3]); 
	mvprintw(38, 85, logs[4]);
}

/**
 *  Draw the log
 */

static void initLog() {
	sprintf(logs[0], "%s", "");
	sprintf(logs[1], "%s", "");
	sprintf(logs[2], "%s", "");
	sprintf(logs[3], "%s", "");
	sprintf(logs[4], "%s", "");
	full_log = 0;
	cursor = 0;
	print_log();
}

/**
 *  Add a message to the log
 */

void add_log(char* message) {
	if (full_log) {
		sprintf(logs[0], "%s", logs[1]);
		sprintf(logs[1], "%s", logs[2]);
		sprintf(logs[2], "%s", logs[3]);
		sprintf(logs[3], "%s", logs[4]);
		sprintf(logs[4], "%s", message);
	} else {
		sprintf(logs[cursor], "%s", message);
		cursor++;
		if (cursor == 5) {
			full_log = 1;
		}
	}
	print_log();
}

/**
 *  Draw the arena
 */

static void drawArena() {
	drawRectangle(2, 1, 80, 40, "Arena");
	drawRectangle(82, 12, 67, 20, "Robot Info");
	drawRectangle(84, 13, 15, 18, "0");
	drawRectangle(100, 13, 15, 18, "1");
	drawRectangle(116, 13, 15, 18, "2");
	drawRectangle(132, 13, 15, 18, "3");
	drawRectangle(82, 32, 67, 9, "Log");
	print_log();
	drawTitle();
	refresh();
}

/**
 *  Blocking functions that wait for user input to interact.
 * 	The different beheviours are :
 * 		Q - Quit
 * 		More to be added...
 * 		The test input will obviously be removed at the end...
 */

static void waitForInput() {
	char msg[40];
	while (1) {
		int c = getch();
		switch (c) {
			case 'q':
			case 'Q':
				return;
			case 't':
				drawRectangle(0, 0, COLS, LINES, "BURP");
				break;
			case '0':
			case '1':
			case '2':
			case '3':
				killRobotNb(c - '0');
				break;
			case 'd':
				eraseArea(2, 1, 80, 40);
				break;
			case 'p':
				sprintf(msg, "Message log #%d", cmpt);
				cmpt++;
				add_log(msg);
				break;
			default:
				break;
		}
	}
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

/**
 *  Init function that launch ui
 */

void init() {
	// Setting the terminal window on top-left of the screen and maximizing the size of it
	system("printf '\e[3;10;10t\e[8;42;150t'");
	sleep(1);

	// Initialisation of ncurses
	initscr();
	resize_term(42, 150);
	noecho();
	signal(SIGWINCH, resizeHandler);
	start_color();
	init_pair(1, COLOR_BLACK, COLOR_WHITE);

	// Drawing the arena
	initLog();
	drawArena();

	// Waiting user behaviour
	waitForInput();
	endwin();
}

int main(int argc, char** argv) {
	init();
	return 0;
}

