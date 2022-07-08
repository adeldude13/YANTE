#include "editor.hpp"
#include <ncurses.h>

int main() {
	Editor editor("file.txt");
	while(1) editor.input();	
	editor.exit();
	return 0;
}
