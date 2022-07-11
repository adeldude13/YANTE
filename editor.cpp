#include "editor.hpp"
#include <ncurses.h>
#include <string>
#include <iostream>

Editor::Editor() {
	this->init();
}

Editor::Editor(std::string data) {
	this->init();
	int curr = 0;
	for(std::size_t i = 0; i<data.size();i++) {
		if(buffer.values.size() == (unsigned int)curr) {
			buffer.values.push_back("");
		}
		if(data[i] == '\n') {
			curr++;
		} else {
			buffer.values[curr] += data[i];
		}
	}
	this->render();
}

void Editor::init() {
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, 0);
	getmaxyx(stdscr, height, width);
}

void Editor::exit() {
	endwin();
}

void Editor::render() {
	int curr_y = 0;
	int curr_x = 0;
	int times = 0;
	for(std::size_t i = 0; i<buffer.values.size();i++) {
		curr_x = 0;
		for(std::size_t j = 0; j<buffer.values[i].size();j++) {
			if(curr_x >= width) {
				times++;
				curr_y++;
				curr_x = 0;
			}
			mvaddch(curr_y, curr_x, buffer.values[i][j]);	
			curr_x++;
		}
		curr_y++;
	}
END:
	return;
}

void Editor::update() {
#define C_MOVE(a, b) this->move_cursor(a, b); break;
	char ch = (char)getch();
	switch(ch) {
		case 'j': // move one step down
			C_MOVE(0, 1);
		case 'k': // move one step up
			C_MOVE(0, -1);
		case 'l': // move one step right
			C_MOVE(1, 0);
		case 'h': // move one step left
			C_MOVE(-1, 0);
	}

}

void Editor::move_cursor(int x, int y) {

}
