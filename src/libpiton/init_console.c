#include <curses.h>
#include <signal.h>

void init_console() {
    initscr();
    savetty();
    nonl();
    cbreak();
    noecho();
    timeout(0);
    leaveok(stdscr, TRUE);
    curs_set(0);
    
}
