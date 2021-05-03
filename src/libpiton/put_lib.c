#include <curses.h>

void put(int line, int col, char symbol) {
    //board[line][col] = symbol;
    move(line, col);
    addch(symbol);
}

void put_border() {
	#define BORDER '#'
	int lines, cols; 
    getmaxyx(stdscr, lines, cols); 
	for(int i = 0; i < cols; i++) {
    	put(0, i, BORDER);
    	put(lines-1, i, BORDER);
    }
    for(int i = 0; i < lines; i++) {
    	put(i, 0, BORDER);
    	put(i, cols-1, BORDER);
    }
}

void put_pit() {
	const char *mesg1 = " _ _ _   _   _   _ _ _   _ _ _   _   _ ";
	const char *mesg2 =	"|  _  | | | | | |_   _| |  _  | | | | |";
	const char *mesg3 =	"| | | | | |/  |   | |   | | | | | |_| |";
	const char *mesg4 =	"| | | | |  /| |   | |   | |_| | |  _  |";
	const char *mesg5 = "|_| |_| |_| |_|   |_|   |_ _ _| |_| |_|";
	//initscr();
	int lines, cols;
    getmaxyx(stdscr, lines, cols);
	attron(A_BOLD);
    mvwprintw(stdscr, (lines/2)-6, (cols/2)-19, "%s", mesg1);
    mvwprintw(stdscr, (lines/2)-5, (cols/2)-19, "%s", mesg2);
    mvwprintw(stdscr, (lines/2)-4, (cols/2)-19, "%s", mesg3);
    mvwprintw(stdscr, (lines/2)-3, (cols/2)-19, "%s", mesg4);
    mvwprintw(stdscr, (lines/2)-2, (cols/2)-19, "%s", mesg5);
    attroff(A_BOLD);
}
