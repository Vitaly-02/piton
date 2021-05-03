#include <curses.h>
#include <time.h>
#include <stdlib.h>

void init_settings() {
    initscr();
    savetty();
    nonl();
    cbreak();
    noecho();
    timeout(0);
    leaveok(stdscr, TRUE);
    curs_set(0);
}

void close_game() {
    curs_set(1);
    clear();
    refresh();
    resetty();
    endwin();
    exit(0);
}

void clear_board(char** board) {
    int i, j;
    int lines, cols;
    getmaxyx(stdscr, lines, cols);
    for (i = 0; i < lines; i++) {
        for (j = 0; j < cols; j++) {
        	board[i][j] = ' ';
        }
    }
}

char** init_board() {
	char** board;
    int i;
    int lines, cols;
    getmaxyx(stdscr, lines, cols);
    board = (char**) malloc(lines * sizeof(char*));
    if (!board) {
        close_game();
    }
    for (i = 0; i < lines; i++) {
        board[i] = (char*) malloc(cols * sizeof(char));
        if (!board[i]) {
            close_game();
        }
    }
    clear_board(board);
    return board;
}

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

void gameloop(char **board);

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
    put_border();
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

void gameloop(char **board) {
	init_settings();  //its nessesary here
	init_board(board);
	put_border();
	put(5, 5, 's');
	refresh();
	napms(2000);
	close_game();
}

int main() {
	menu();
	return 0;
}
