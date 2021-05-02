#include <curses.h>

void clear_board(char** board) {
    int i, j;
    int lines, cols;
    getmaxyx(stdscr, lines, cols);
    for (i = 0; i < lines; i++) {
        for (j = 0; j < cols; j++) {
            board[i][j] = ' ';
          //if(i == 1 || i+1 == lines || j == 0 || j+1 == cols) {
	      //	board[i][j] = '#';
    	  //}
        }
    }
}
