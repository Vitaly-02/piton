#include <curses.h>
#include <stdlib.h>
#include "clear_board.h"
#include "close_game.h"

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
