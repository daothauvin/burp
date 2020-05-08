#include "ui.h"
#include <ctype.h>

/**
 *  Global variable
 */

// Log 
char logs[5][LOG_SIZE];
int full_log;
int cursor;

// Info robot
char actions[12][7];

// Pause var
static short paused = 0;

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
	//fprintf(stderr,"health : %d\n",get_robot_health_points(rob));
	if (get_robot_health_points(rob) == 0) {
		char message [LOG_SIZE];
		memset(message, '\0', LOG_SIZE);
		snprintf(message, LOG_SIZE, "[X] Robot n°%d is dead.", get_robot_id(rob));
		add_log(message);
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

	snprintf(buff, 11, "%s_%d", get_robot_name(rob),robot_id);
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
	mvprintw(y + 12, x + 3, "       ");
	mvprintw(y + 12, x + 3, actions[3 * robot_id]);
	attron(COLOR_PAIR(1));
	mvprintw(y + 13, x + 3, "       ");
	mvprintw(y + 13, x + 3, actions[3 * robot_id + 1]);
	attroff(COLOR_PAIR(1));
	mvprintw(y + 14, x + 3, "       ");
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
	mvprintw(2, 94, "oooooooooo.        Basic Used for Robots Programming");
	mvprintw(3, 94, "`888'   `Y8b");
	mvprintw(4, 95, "888     888 oooo  oooo  oooo d8b oo.ooooo.");
	mvprintw(5, 95, "888oooo888' `888  `888  `888""8P    888' `88b      ;");
	mvprintw(6, 95, "888    `88b  888   888   888      888   888     [\"]/");
	mvprintw(7, 95, "888    .88P  888   888   888      888   888    /[_]");
	mvprintw(8, 94, "o888bood8P'   `V88V\"V8P' d888b     888bod8P'     ] [");
	mvprintw(9, 129, "888");
	mvprintw(10, 128, "o888o");
	mvprintw(11, 90, "[Q] Quit       [P] Pause");
	mvprintw(12, 90, "[+] Speed up   [-] Slow up");
}

/**
 *  Draw the end screen
 */

void end_screen(robot* robot) {
	nodelay(stdscr, FALSE);
	clear();
	mvprintw(2, 0, "  +        +        +        +        +        +        +        +        +        +        +        +        +        +        +        +        +");
	mvprintw(5, 0, "       +        +        +        +        +        +        +        +        +        +        +        +        +        +        +        +");
	mvprintw(8, 0, "   +        +        +        +        +        +        +        +        +        +        +        +        +        +        +        +        +");
	mvprintw(10, 0, "                                                    oooooooooo.        Basic Used for Robots Programming");
	mvprintw(11, 0, "       +        +        +        +        +        `888'   `Y8b                                                   +        +        +        +");
	mvprintw(12, 0, "                                                     888     888 oooo  oooo  oooo d8b oo.ooooo.");
	mvprintw(13, 0, "                                                     888oooo888' `888  `888  `8888P    888' `88b      ;");
	mvprintw(14, 0, "  +        +        +        +        +        +     888    `88b  888   888   888      888   888     [\"]/     +       +        +        +        +");
	mvprintw(15, 0, "                                                     888    .88P  888   888   888      888   888    /[_]");
	mvprintw(16, 0, "                                                    o888bood8P'   `V88V\"V8P' d888b     888bod8P'     ] [");
	mvprintw(17, 0, "       +        +        +        +        +        +       +         +        +       888       +       +        +        +        +        +");
	mvprintw(18, 0, "                                                                                      o888o");
	mvprintw(19, 0, "");
	mvprintw(20, 0, "  +        +        +        +        +        +        +        +        +        +        +        +        +        +        +        +        +");
	mvprintw(22, 0, "                                                            +-------------------------------+");
	mvprintw(23, 0, "       +        +        +        +         +       +            Congratulation, %s_%d.        +        +        +        +        +        +", get_robot_name(robot),get_robot_id(robot));
	mvprintw(24, 0, "                                                               You're the survivor Robot !");
	mvprintw(25, 0, "                                                            +-------------------------------+");
	mvprintw(26, 0, "  +         +        +        +        +        +        +        +        +        +        +        +        +        +        +        +        +");
	mvprintw(29, 0, "       +        +        +        +        +        +        +        +        +        +        +        +        +        +        +        +");
	mvprintw(32, 0, "  +        +        +        +        +        +         +        +        +        +        +        +        +        +        +        +        +");
	mvprintw(35, 0, "       +        +        +        +        +        +        +        +        +        +        +        +        +        +        +        +");
	mvprintw(38, 0, "  +        +        +        +        +        +        +        +        +        +        +        +        +        +        +        +        +");
	mvprintw(41, 0, "        +        +        +        +        +        +        +        +        +        +        +        +        +        +        +        +");
	getch();
}

/**
 *  Print the log
 */

static void print_log() {
	eraseArea(87, 36, LOG_SIZE, 5);
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
	refresh();
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

