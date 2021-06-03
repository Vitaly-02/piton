#include <curses.h>
#include <time.h>
#include <stdlib.h>
#include <string.h> 
#include "init_settings.h"
#include "init_board.h"
#include "close_game.h"
#include "put_lib.h"
#include "gameover_menu.h"
#include "win_menu.h"
// структура с координатами
typedef struct position {
	int line;
	int col;
} position;

///////////
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
// функция возвращает рандомные координаты
// это нужно для появления еды и начального
// положения питона
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
// функция, которая ставит еду в случайном месте
#define FOOD '@'
void put_food(char** board) {
	struct position food;
	food = random_position(board);
	attron(COLOR_PAIR(COLOR_RED));
	put(food.line, food.col, FOOD, board);
	attroff(COLOR_PAIR(COLOR_RED));
}
// проверка на столкновение с границей или с телом питона
void check_head(char** board) {
    if (board[piton[0].line][piton[0].col] != ' '
        && board[piton[0].line][piton[0].col] != FOOD) {
        direction = STOP;
        while(true) {
        gameover_menu(score, board);
        }
        return;
    }
// проверка на победу
    if (piton_length == MAXPITON) {
    	direction = STOP;
        while(true) {
        win_menu(score, board);
        }
        return;
    }
}
// смена направления движения питона
void change_direction() {
	char keypress;
	keypress = wgetch(stdscr);
	if(keypress == ERR) {
		return;
	}
	    
	if((keypress == 'w' || keypress == 'W') && direction != DOWN) { 
		direction = UP;
	} else if((keypress == 'a' || keypress == 'A') && direction != RIGHT) { 
		direction = LEFT;
	} else if((keypress == 's' || keypress == 'S') && direction != UP) { 
		direction = DOWN;
	} else if((keypress == 'd' || keypress == 'D') && direction != LEFT) { 
		direction = RIGHT;
	}
}
// движение питона
void change_head() {
    if (direction == RIGHT) {
        piton[0].col++;
    } else if (direction == LEFT) {
        piton[0].col--;
    } else if (direction == UP) {
        piton[0].line--;
    } else if (direction == DOWN) {
        piton[0].line++;
    } else if (direction == STOP) {
    	return;
    }
}
// логика
void logic(char** board) {
	memmove(&piton[1], &piton[0], sizeof(position) * piton_size);
	change_head();
	check_head(board);
// если питон наткнулся на еду, увеличивается его длина и счет игрока
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
	score = 0;
	piton_size = 1;
	piton_length = MINPITON;
	// настройки для консоли
	init_settings();
	board = init_board();
	put_border(board);
	attron(A_STANDOUT);
	mvwprintw(stdscr, 0, 0, "SCORE: %d", score);
	attroff(A_STANDOUT);
	// первоначальная позция питона
	piton[0] = random_position(board);
	attron(COLOR_PAIR(COLOR_GREEN));
	put(piton[0].line, piton[0].col, 'O', board);
	attroff(COLOR_PAIR(COLOR_GREEN));
	// первая еда
	put_food(board);
	// запускается логика, как только нажата любая клавиша
    // управления питоном 
	while(true) {
        if(direction != STOP) {
        	logic(board);
        }
        change_direction();
        napms(80);
        change_direction();
    }
	// если что-то пойдет не так - игра закрывается
	close_game();
}
