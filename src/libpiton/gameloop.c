#include <curses.h>
#include <time.h>
#include <stdlib.h>
#include "init_settings.h"
#include "init_board.h"
#include "close_game.h"
#include "put_lib.h"

typedef struct position {
	int line;
	int col;
} position;

struct position random_position(char** board) {
	srand(time(NULL));
	int lines, cols;
	getmaxyx(stdscr, lines, cols);
	struct position pos;
	do {
		pos.col = rand()%cols;
		pos.line = rand()%lines;
	} while (board[pos.line][pos.col] != ' ');
	return pos;
}

#define FOOD '@'
void put_food(char** board) {
	struct position food;
	food = random_position(board);
	attron(COLOR_PAIR(COLOR_RED));
	put(food.line, food.col, FOOD, board);
	attroff(COLOR_PAIR(COLOR_RED));
}



#define MINPITON 3
#define MAXPITON 103
void gameloop(char **board) {
	init_settings();  //its nessesary here
	init_board(board);
	put_border(board);
	int score = 0;
	//score vizual
	attron(A_STANDOUT);
	mvwprintw(stdscr, 0, 0, "SCORE: %d", score);
	attroff(A_STANDOUT);
	//init piton
	//struct position piton[MAXPITON];
	//int piton_size = 3;
	//piton[0] = random_position(board);
	//logic
	put_food(board);
	refresh();
	napms(2000);
	close_game();
}
