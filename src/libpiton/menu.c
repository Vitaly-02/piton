#include <curses.h>
#include "init_console.h" //to delete
#include "init_board.h"
#include "close_game.h"
#include "clear_board.h" //to delete
//#include <string.h>

//puts
void put(int line, int col, char ch, char** board) {
    board[line][col] = ch;
    move(line, col);
    addch(ch);
}
#define BORDER '#'
#define COLOR_WHITE	7
void put_border(char** board) {
	//Coord pos;
	int lines, cols;
    getmaxyx(stdscr, lines, cols);
	//up and down
	for(int i = 0; i < cols; i++) {
    	attron(COLOR_PAIR(COLOR_WHITE));
    	put(1, i, BORDER, board);        //todo smth with upper border
    	put(lines-1, i, BORDER, board);  //line 0 dont exist?
    }
    for(int i = 0; i < lines; i++) {
    	attron(COLOR_PAIR(COLOR_WHITE));
    	put(i, 0, BORDER, board);
    	put(i, cols-1, BORDER, board);
    }
}
///
void put_pit() {
const char *mesg = "\t\t _ _ _   _   _   _ _ _   _ _ _   _   _\n\t\t|  _  | | | | | |_   _| |  _  | | | | |\n\t\t| | | | | |/  |   | |   | | | | | |_| |\n\t\t| | | | |  /| |   | |   | |_| | |  _  |\n\t\t|_| |_| |_| |_|   |_|   |_ _ _| |_| |_|";
	//initscr();
	//int lines, cols;
    //getmaxyx(stdscr, lines, cols);
	//attron(COLOR_PAIR(COLOR_RED));
	attron(A_BOLD);
    mvwprintw(stdscr, 10, 0, "%s", mesg);
    attroff(A_BOLD);
    
}
///end of puts///

void menu() {
	//char** board;
	initscr();
	init_console();
	char** board = init_board();
	put_pit();
	
	const char *mesg = "\t\t\tPRESS 'S' TO START\t\t\t\n\t\t\tPRESS 'Q' TO EXIT\t\t\t";
	attron(A_STANDOUT);
    mvwprintw(stdscr, 16, 0, "%s", mesg);
    attroff(A_STANDOUT);
    put_border(board);
    //processing of pressed keys 
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
    	close_game();
    }
    
	endwin();
///	clear_board(board); //to delete
}
