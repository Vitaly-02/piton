#include <curses.h>
#include "gameloop.h"
#include "menu.h"
// меню проигрыша
void gameover_menu(int score, char** board) {
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
// обработка нажатой клавиши
	int keypress;
    keypress = wgetch(stdscr);
    if (keypress == ERR) {
        return;
    }
    if (keypress == 'q'||keypress == 'Q') {
    	clear();
        refresh();
        while(true) {
        	menu();
        }
    }
    if (keypress == 'r'||keypress == 'R') {
    	clear();
        refresh();
    	gameloop(board);
    }
	return;
}
