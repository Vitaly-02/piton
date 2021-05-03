#include <curses.h>

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
