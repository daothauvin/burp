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
	char spaces[length + 1]; 
	memset(spaces, ' ', length + 1);
	spaces[length] = '\0';
	for (int i = 0; i < height; i++) {
		mvprintw(y + i, x, spaces);
	}
}

/**
 *  Erase the arena
 */

static void eraseArena() {
	eraseArea(3, 2, 80, 40);
}

/**
 *  Launch the begin animation
 */

static void anim_begin() {
	mvprintw(16, 36, " .d8888b. ");
	mvprintw(17, 36, "d88P  Y88b");
	mvprintw(18, 36, "     .d88P");
	mvprintw(19, 36, "     8888\"");
	mvprintw(20, 36, "     \"Y8b.");
	mvprintw(21, 36, "888    888");
	mvprintw(22, 36, "Y88b  d88P");
	mvprintw(23, 36, " \"Y8888P\" ");
	
	refresh();
	sleep(1);
	mvprintw(16, 36, " .d8888b. ");
	mvprintw(17, 36, "d88P  Y88b");
	mvprintw(18, 36, "       888");
	mvprintw(19, 36, "     .d88P");
	mvprintw(20, 36, " .od888P\" ");
	mvprintw(21, 36, "d88P\"     ");
	mvprintw(22, 36, "888\"      ");
	mvprintw(23, 36, "8888888888");
	refresh();
	sleep(1);

	mvprintw(16, 36, "   d888   ");
	mvprintw(17, 36, "  d8888   ");
	mvprintw(18, 36, "    888   ");
	mvprintw(19, 36, "    888   ");
	mvprintw(20, 36, "    888   ");
	mvprintw(21, 36, "    888   ");
	mvprintw(22, 36, "    888   ");
	mvprintw(23, 36, "  8888888 ");
	refresh();
	sleep(1);

	mvprintw(16, 19, "8888888888 d8b          888      888         888");
	mvprintw(17, 19, "888        Y8P          888      888         888");
	mvprintw(18, 19, "888                     888      888         888");
	mvprintw(19, 19, "8888888    888  .d88b.  88888b.  888888      888");
	mvprintw(20, 19, "888        888 d88P\"88b 888 \"88b 888         888");
	mvprintw(21, 19, "888        888 d88P\"88b 888 \"88b 888         888");
	mvprintw(22, 19, "888        888 Y88b 888 888  888 Y88b.        \"");
	mvprintw(23, 19, "888        888  \"Y88888 888  888  \"Y888      888");
	mvprintw(24, 39, "888 ");
	mvprintw(25, 34, "Y8b d88P");
	mvprintw(26, 35, "\"Y88P\"");
	refresh();
	sleep(1);
	eraseArea(19, 16, 48, 11);
} 

/**
 *  Blur the info of a robot when he's dead.
 */

static void killRobotNb(int nbBot) {
	int x;
	int y = 16;

	switch(nbBot) {
		case 0:
			x = 87;
			break;
		case 1:
			x = 103;
			break;
		case 2:
			x = 119;
			break;
		case 3:
			x = 135;
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
	mvprintw(3, 93, "oooooooooo.        Basic Used for Robots Programming");
	mvprintw(4, 93, "`888'   `Y8b");
	mvprintw(5, 94, "888     888 oooo  oooo  oooo d8b oo.ooooo.");
	mvprintw(6, 94, "888oooo888' `888  `888  `888""8P    888' `88b      ;");
	mvprintw(7, 94, "888    `88b  888   888   888      888   888     [\"]/");
	mvprintw(8, 94, "888    .88P  888   888   888      888   888    /[_]");
	mvprintw(9, 93, "o888bood8P'   `V88V\"V8P' d888b     888bod8P'     ] [");
	mvprintw(10, 127, "888");
	mvprintw(11, 126, "o888o");
}
/**
 *  Print the log
 */

static void print_log() {
	eraseArea(87, 36, 60, 5);
	mvprintw(36, 87, logs[0]);
	mvprintw(37, 87, logs[1]);
	mvprintw(38, 87, logs[2]);
	mvprintw(39, 87, logs[3]); 
	mvprintw(40, 87, logs[4]);
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
	drawRectangle(2, 1, 82, 42, "Arena");
	drawRectangle(84, 14, 67, 20, "Robot Info");
	drawRectangle(86, 15, 15, 18, "0");
	drawRectangle(102, 15, 15, 18, "1");
	drawRectangle(118, 15, 15, 18, "2");
	drawRectangle(134, 15, 15, 18, "3");
	drawRectangle(84, 34, 67, 9, "Log");
	print_log();
	drawTitle();
	refresh();
}

/**
 *  Blocking functions that wait for user input to interact.
 * 	The different beheviours are :
 * 		Q - Quit
 * 		More to be added...
 */

static void waitForInput() {
	char msg[40];
	while (1) {
		int c = getch();
		switch (c) {
			case 'q':
			case 'Q':
				return;
			// Tests
			case '0':
			case '1':
			case '2':
			case '3':
				killRobotNb(c - '0');
				break;
			case 'p':
				sprintf(msg, "Message log #%d", cmpt);
				cmpt++;
				add_log(msg);
				break;
			case 'a':
				anim_begin();
				break;
			case 'e':
				eraseArena();
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
	system("printf '\e[3;10;10t\e[8;44;152t'");
	drawArena();
	sleep(1);
}

/**
 *  Init function that launch ui
 */

void init() {
	// Setting the terminal window on top-left of the screen and maximizing the size of it
	system("printf '\e[3;10;10t\e[8;44;152t'");
	sleep(1);

	// Initialisation of ncurses
	initscr();
	curs_set(0);
	resize_term(44, 152);
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
