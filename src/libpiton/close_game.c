#include <curses.h>
#include <stdlib.h>
// функция закрытия игры
// возвращает все настройки консоли
// к исходным
void close_game() {
    curs_set(1);
    clear();
    refresh();
    resetty();
    endwin();
    exit(0);
}
