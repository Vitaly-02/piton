#include <curses.h>
#include "init_board.h"
#include "close_game.h"
#include "gameloop.h"
#include "put_lib.h"

void menu() {
    initscr();
    int lines, cols; 
    getmaxyx(stdscr, lines, cols); //to get res
    char **board;
    board = init_board();
    put_pit();
    const char *mesg1 = "PRESS 'S' TO START";
	const char *mesg2 = "PRESS 'Q' TO EXIT ";
    attron(A_STANDOUT);
    mvwprintw(stdscr, lines/2, (cols/2)-9, "%s", mesg1);
    mvwprintw(stdscr, (lines/2)+1, (cols/2)-9, "%s", mesg2);
    attroff(A_STANDOUT);
    put_border(board);
    //resolution (delete in future)
    mvwprintw(stdscr, lines - 2, 1, "Resolution: lines = %d columns = %d", lines, cols);
    //processing of pressed key
    //ERR - nothing pressed
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
