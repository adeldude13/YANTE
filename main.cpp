#include "editor.hpp"
#include <ncurses.h>

int main() {
	Editor editor("Lmao Im Too Good\n+ratio");
	getch();	
	editor.exit();
}
