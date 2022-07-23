#include "editor.hpp"
#include <ncurses.h>

Editor::Editor() {
	this->init();
}

Editor::Editor(std::string file_content) {
	lines.fill(file_content);
	this->init();
}

void Editor::init() {
	initscr();
	noecho();
	getmaxyx(stdscr, height, width);
	getyx(stdscr, cursor_y, cursor_x);
	this->render();
}

void Editor::cleanup() {
	endwin();
}

void Editor::render() {
	Line *curr = lines.head;
	int i=0;
	int tempy = cursor_y, tempx = cursor_x;
	for(;i<height && cursor_y < height;i++) {
		while(curr != nullptr && cursor_y < height) {
			for(std::size_t j=0; j<width && j < curr->size();j++) {
				addch(curr->content[j]);
			}
			cursor_y++;
			cursor_x = 0;
			curr = curr->next;
			move(cursor_y, cursor_x);
			i++;
			if(i >= height) return;
		}
		addch('~');
		cursor_y++;
		cursor_x = 0;
		move(cursor_y, cursor_x);
	}
	cursor_y++;
	cursor_x = 0;
	move(tempy, tempx);
}
