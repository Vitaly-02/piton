//#include <curses.h>
#include <time.h>
#include "libpiton/init_console.h"
#include "libpiton/menu.h"

int main() {
	init_console();
	menu();
	return 0;
}
