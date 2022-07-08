#include "editor.hpp"
#include <ncurses.h>

int main() {
	Editor editor("file.txt");
	getch();
	editor.exit();
	return 0;
}
