#include "ui.h"
#include <ctype.h>

/**
 *  Global variable
 */

// Log 
char logs[5][60];
int full_log;
int cursor;

// Info robot
char actions[12][7];

// Test
int cmpt = 0;
int cmpt_1 = 0;

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

void eraseArena() {
	eraseArea(3, 2, 80, 40);
}

/**
 *	Print a char using coordonates from arena (not screen)
 */

static void printCharArena(int x, int y, char c) {
	if (x >= size_arena_x || y >= size_arena_y) return;
	
	int fx = x * 80 / size_arena_x + 3;
	int fy = y * 40 / size_arena_y + 2;

	char* cc = malloc(sizeof(char) * 2);
	cc[0] = c;
	cc[1] = '\0';

	mvprintw(fy, fx, cc);
	free(cc);
}

/**
 *  Test if a coordonate is empty or not on the screen
 * 	Use the arena coordonates, and read on the position coresponding in the term
 */

static int isEmpty(int x, int y) {
	int fx = x * 80 / size_arena_x + 3;
	int fy = y * 40 / size_arena_y + 2;
	return ((mvinch(fy, fx) & A_CHARTEXT) == ' ');
}

/**
 *  Blur the info of a robot when he's dead.
 */

static void killRobotNb(int id) {
	int x;
	int y = 16;

	switch(id) {
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
 *	Print a robot in the arena
 *  If the case is already used, then write on another case following this order :
 *  	5
 *     4#2
 * 		3
 */

void printRobot(robot* rob) {
	if (get_robot_health_points(rob) == 0) {
		killRobotNb(get_robot_id(rob));
		return;
	}
	point rob_pos;
	get_robot_pos(rob,&rob_pos);
	int x = rob_pos.x;
	int y = rob_pos.y;
	int ux = size_arena_x / 80;
	int uy = size_arena_y / 40;
    char c = '#';
	int robot_id = get_robot_id(rob);
	if (isEmpty(x, y)) {
		attron(COLOR_PAIR(2 + robot_id));
		printCharArena(x, y, c);
		attroff(COLOR_PAIR(2 + robot_id));
		return;
	}
	if (isEmpty(x + ux, y)) {
		attron(COLOR_PAIR(2 + robot_id));
		printCharArena(x + ux, y, c);
		attroff(COLOR_PAIR(2 + robot_id));
		return;
	}
	if (isEmpty(x, y + uy)) {
		attron(COLOR_PAIR(2 + robot_id));
		printCharArena(x, y + uy, c);
		attroff(COLOR_PAIR(2 + robot_id));
		return;
	}
	if (isEmpty(x - ux, y)) {
		attron(COLOR_PAIR(2 + robot_id));
		printCharArena(x - ux, y, c);
		attroff(COLOR_PAIR(2 + robot_id));
		return;
	}
	if (isEmpty(x, y - uy)) {
		attron(COLOR_PAIR(2 + robot_id));
		printCharArena(x, y - uy, c);
		attroff(COLOR_PAIR(2 + robot_id));
		return;
	}
}

/**
 *	Print a rocket in the arena
 *  Works the same as printRobot()
 */

void printRocket(missile *rocket) { 
	point pos_mis;
	get_missile_pos(rocket,&pos_mis);
	int x = pos_mis.x;
	int y = pos_mis.y;
	int ux = size_arena_x / 80;
	int uy = size_arena_y / 40;
    char c = '+';

	if (isEmpty(x, y)) {
		printCharArena(x, y, c);
		return;
	}
	if (isEmpty(x + ux, y)) {
		printCharArena(x + ux, y, c);
		return;
	}
	if (isEmpty(x, y + uy)) {
		printCharArena(x, y + uy, c);
		return;
	}
	if (isEmpty(x - ux, y)) {
		printCharArena(x - ux, y, c);
		return;
	}
	if (isEmpty(x, y - uy)) {
		printCharArena(x, y - uy, c);
		return;
	}
}


/**
 *  Print a robot information
 */

void printInfoRobot(robot* rob) {

	if (get_robot_health_points(rob) == 0) {
		killRobotNb(get_robot_id(rob));
		return;
	}

	int x;
	int y = 16;
	int robot_id = get_robot_id(rob);
	switch(robot_id) {
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

	char buff[11];
	memset(buff, '\0', 11);

	attron(COLOR_PAIR(12 + robot_id));
	mvprintw(y + 1, x + 2, " ");
	attroff(COLOR_PAIR(12 + robot_id));

	snprintf(buff, 11, "RBT_%d", robot_id);
	mvprintw(y + 1, x + 4, buff);
	memset(buff, '\0', 11);

	attron(COLOR_PAIR(12 + robot_id));
	mvprintw(y + 1, x + 10, " ");
	attroff(COLOR_PAIR(12 + robot_id));

	drawRectangle(x + 1, y + 3, 11, 3, "Hp");
	if (get_robot_health_points(rob) == 100) {
		snprintf(buff, 11, "%d %s", get_robot_health_points(rob), "%%");
	} else if (get_robot_health_points(rob)> 9) {
		snprintf(buff, 11, " %d %s", get_robot_health_points(rob), "%%");
	} else {
		snprintf(buff, 11, "  %d %s", get_robot_health_points(rob), "%%");
	}
	
	mvprintw(y + 4, x + 4, buff);
	memset(buff, '\0', 11);

	drawRectangle(x + 1, y + 7, 11, 3, "Spd");
	int speed_robot = (int)get_robot_speed(rob);
	if (speed_robot == 100) {
		snprintf(buff, 11, "%d %s",speed_robot, "%%");
	} else if (speed_robot > 9) {
		snprintf(buff, 11, " %d %s",speed_robot, "%%");
	} else {
		snprintf(buff, 11, "  %d %s",speed_robot, "%%");
	}
	mvprintw(y + 8, x + 4, buff);

	drawRectangle(x + 1, y + 11, 11, 5, "Action");
	mvprintw(y + 12, x + 3, actions[3 * robot_id]);
	attron(COLOR_PAIR(1));
	mvprintw(y + 13, x + 3, actions[3 * robot_id + 1]);
	attroff(COLOR_PAIR(1));
	mvprintw(y + 14, x + 3, actions[3 * robot_id + 2]);
     
}

/**
 * 	Init the print of robot info
 */

static void init_info() {
	for (size_t i = 0; i < 12; i++) {
		sprintf(actions[i], "%s", "");
	}
}


/**
 * 	Add an action
 */

void add_action(char* action, int id) {
	sprintf(actions[id * 3 + 2], "%s", actions[id * 3 + 1]);
	sprintf(actions[id * 3 + 1], "%s", actions[id * 3]);
	sprintf(actions[id * 3], "%s", action);
}

/**
 *  Launch the begin animation
 */

void anim_begin() {
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
	mvprintw(10, 128, "888");
	mvprintw(11, 127, "o888o");
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
 *  Init the log
 */

static void init_log() {
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
 *  Update the arena, and the info with data in the arena
 */

void updateArena(arena* arena) {
	eraseArena();
	for (int i = 0; i < get_nb_robot_arena(arena); i++) {
		printRobot(get_robot_index(arena,i));
		printInfoRobot(get_robot_index(arena,i));
	}
	for (int i = 0; i < get_nb_missiles_arena(arena); i++) {
		printRocket(get_missile_index(arena,i));
	}
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
 *  -Normally not- blocking functions that wait for user input to interact.
 * 	The different beheviours are :
 * 		Q - Quit
 */

static int time_between = 1000000;
short waitForInput() {
	/*
	char msg[40];
	robot* bob = create_robot(0.0, 0.0, 0.0, 0.0, 0);

	robot* rob = create_robot(0.0, 9999.0, 0.0, 0.0, 1);

	robot* tob = create_robot(9999.0, 0.0, 0.0, 0.0, 2);

	robot* zob = create_robot(9999.0, 9999.0, 0.0, 0.0, 3);

	char act[7];
	*/

	cbreak();
	int diff;
	nodelay(stdscr, TRUE);
	struct timeval start, cur;
	gettimeofday(&start, NULL);
    while (diff < time_between) {
		int c = getch();
		switch (c) {
			case 'q':
			case 'Q':
				return 0;
			case '+':
				if(time_between > 100000) {
					time_between -= 100000;
					add_log("Speed up");
				}
				else {
					add_log("Max speed reached");
				}
				break;
			case '-':
				if(time_between < 10000000) {
					time_between += 100000; 
					add_log("Speed down");
				} 
				else {
					add_log("Lower speed reached");
				}
				break;
			/*
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
			case 'r':
				printRobot(bob);
				printRobot(rob);
				printRobot(tob);
				printRobot(zob);
				break;
			case 'e':
				eraseArena();
				break;
			case 'y':
				printInfoRobot(bob);
				printInfoRobot(rob);
				printInfoRobot(tob);
				printInfoRobot(zob);
				break;
			case 'x':
				memset(act, '\0', 7);
				snprintf(act, 7, "A_%d_%d", cmpt_1, 0);
				add_action(act, 0);

				memset(act, '\0', 7);
				snprintf(act, 7, "A_%d_%d", cmpt_1, 1);
				add_action(act, 1);

				memset(act, '\0', 7);
				snprintf(act, 7, "A_%d_%d", cmpt_1, 2);
				add_action(act, 2);

				memset(act, '\0', 7);
				snprintf(act, 7, "A_%d_%d", cmpt_1, 3);
				add_action(act, 3);
				
				cmpt_1++;
				break;
				*/
			default:
				break;
		}
		gettimeofday(&cur, NULL);
		diff = (cur.tv_sec - start.tv_sec) * 1000000 + (cur.tv_usec - start.tv_usec);

	}
	return 1;
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

	// Creation of color pairs
	init_pair(1, COLOR_BLACK, COLOR_WHITE);
	init_pair(2, COLOR_YELLOW, COLOR_BLACK);
	init_pair(3, COLOR_RED, COLOR_BLACK);
	init_pair(4, COLOR_GREEN, COLOR_BLACK);
	init_pair(5, COLOR_BLUE, COLOR_BLACK);
	init_pair(12, COLOR_BLACK, COLOR_YELLOW);
	init_pair(13, COLOR_BLACK, COLOR_RED);
	init_pair(14, COLOR_BLACK, COLOR_GREEN);
	init_pair(15, COLOR_BLACK, COLOR_BLUE);

	// Drawing the arena
	init_log();
	init_info();
	drawArena();
}

/**
 * 	Quit Ncurses
 */

int quit() {
	return endwin();
}

/*

int main(int argc, char** argv) {
	init();
	return 0;
}

*/

