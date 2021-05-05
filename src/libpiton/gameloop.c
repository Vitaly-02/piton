#include <curses.h>
#include <time.h>
#include <stdlib.h>
#include <string.h> //memmove
#include "init_settings.h"
#include "init_board.h"
#include "close_game.h"
#include "put_lib.h"

typedef struct position {
	int line;
	int col;
} position;

//globals//
int score = 0;
#define LEFT  0
#define RIGHT 1
#define UP    2
#define DOWN  3
#define STOP  4
int direction = STOP;
#define MINPITON 3
#define MAXPITON 103
int piton_size = 1;
int piton_length = MINPITON;
struct position piton[MAXPITON];
///////////

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

void check_head(char** board) {
    if (board[piton[0].line][piton[0].col] != ' '
        && board[piton[0].line][piton[0].col] != FOOD) {
        //gameover_menu(); //to do!
        close_game();
    }
}

void change_direction() {
	char keypress;
	keypress = wgetch(stdscr);
	if(keypress == ERR) {
		return;
	}
	    
	if(keypress == 'w' || keypress == 'W') { //up
		direction = UP;
	} else if(keypress == 'a' || keypress == 'A') { //left
		direction = LEFT;
	} else if(keypress == 's' || keypress == 'S') { //down
		direction = DOWN;
	} else if(keypress == 'd' || keypress == 'D') { //right
		direction = RIGHT;
	}
}

void change_head() {
    if (direction == RIGHT) {
        piton[0].col++;
    } else if (direction == LEFT) {
        piton[0].col--;
    } else if (direction == UP) {
        piton[0].line--;
    } else if (direction == DOWN) {
        piton[0].line++;
    } 
}

void logic(char** board) {
	memmove(&piton[1], &piton[0], sizeof(position) * piton_size);
	change_head();
	check_head(board);
	if (board[piton[0].line][piton[0].col] == FOOD) {
        piton_length++;
        score++;
        put_food(board);
        attron(A_STANDOUT);
		mvwprintw(stdscr, 0, 0, "SCORE: %d", score);
		attroff(A_STANDOUT);
    }
    attron(COLOR_PAIR(COLOR_GREEN));
    put(piton[0].line, piton[0].col, 'O', board);
    if (piton_size < piton_length) {
        piton_size++;
    } else {
        put(piton[piton_size].line, piton[piton_size].col, ' ', board);
    }
    attroff(COLOR_PAIR(COLOR_GREEN));
}

void gameloop(char **board) {
	//its nessesary here
	init_settings();
	board = init_board();
	put_border(board);
	//score vizual
	attron(A_STANDOUT);
	mvwprintw(stdscr, 0, 0, "SCORE: %d", score);
	attroff(A_STANDOUT);
	//init piton
	piton[0] = random_position(board);
	attron(COLOR_PAIR(COLOR_GREEN));
	put(piton[0].line, piton[0].col, 'O', board);
	attroff(COLOR_PAIR(COLOR_GREEN));
	//first food
	put_food(board);
	//logic
	while(true) {
        
        if(direction != STOP) {
        	logic(board);
        }
        change_direction();
        napms(80);
        change_direction();
    }
	//if any error
	close_game();
}
