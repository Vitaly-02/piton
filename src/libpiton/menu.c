#include <curses.h>
#include "init_board.h"
#include "close_game.h"
#include "gameloop.h"
#include "put_lib.h"
// функция главного меню
void menu() {
    initscr();
    int lines, cols; 
    getmaxyx(stdscr, lines, cols); 
    // двумерный массив символов, в котором будут
    // храниться границы - #, еда - @ и тело змеи - O
    char **board;
    board = init_board();
    // функция, которая выводит надпись ПИТОН
    put_pit();
    const char *mesg1 = "PRESS 'S' TO START";
	const char *mesg2 = "PRESS 'Q' TO EXIT ";
    attron(A_STANDOUT);
    mvwprintw(stdscr, lines/2, (cols/2)-9, "%s", mesg1);
    mvwprintw(stdscr, (lines/2)+1, (cols/2)-9, "%s", mesg2);
    attroff(A_STANDOUT);
    put_border(board);
    // обработка нажатых клавиш
	int keypress;
    keypress = wgetch(stdscr);
    if (keypress == ERR) {
        return;
    }
    if (keypress == 'q'||keypress == 'Q') {
    	clear();
        refresh();
        close_game();
    }
    if (keypress == 's'||keypress == 'S') {
    	clear();
        refresh();
    	gameloop(board);
    }
	endwin();
}
