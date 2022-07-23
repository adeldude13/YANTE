#include "lines.hpp"
#include "editor.hpp"
#include <ncurses.h>

int main() {
	Editor editor("lmao");
	getch();
	editor.cleanup();
	return 0;
}
