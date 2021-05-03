#include <curses.h>
#include "init_settings.h"
#include "init_board.h"
#include "close_game.h"
#include "put_lib.h"

void gameloop(char **board) {
	init_settings();  //its nessesary here
	init_board(board);
	put_border();
	put(5, 5, 's');
	refresh();
	napms(2000);
	close_game();
}
