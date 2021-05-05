#include <curses.h>

#include "init_board.h"
#include "close_game.h"
#include "put_lib.h"

void gameover_menu(int score) {
	int lines, cols; 
    getmaxyx(stdscr, lines, cols);
    attron(A_STANDOUT|COLOR_PAIR(COLOR_RED));
    mvwprintw(stdscr, (lines/2)-2, (cols/2)-9,     "     GAME OVER      ");
    attroff(COLOR_PAIR(COLOR_RED));
    mvwprintw(stdscr, (lines/2)-1, (cols/2)-9, "    YOUR SCORE: %d ", score);
    if(score < 10) {
    	mvwprintw(stdscr, (lines/2)-1, (cols/2)+8, "   ");
    } else if (score < 100) {
    	mvwprintw(stdscr, (lines/2)-1, (cols/2)+9, "  ");
    }
    mvwprintw(stdscr, (lines/2), (cols/2)-9, "PRESS 'R' TO RESTART");
    mvwprintw(stdscr, (lines/2)+1, (cols/2)-9, "PRESS 'Q' TO GO MENU");
    attroff(A_STANDOUT);
    refresh();
	napms(3000);
	close_game();
	
}
