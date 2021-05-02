#include <curses.h>
#include <stdlib.h>

void close_game() {
    curs_set(1);
    clear();
    refresh();
    resetty();
    endwin();
    exit(0);
}
