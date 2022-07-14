#include "editor.hpp"
#include <ncurses.h>
#include <string>
#include <iostream>
#include <math.h>

#define DEBUG

Editor::Editor() {
	this->init();
}

Editor::Editor(std::string data) {
	this->init();
	int curr = 0;
	for(std::size_t i = 0; i<data.size();i++) {
		if(buffer.lines.size() == (unsigned int)curr) {
			Line l;
			buffer.lines.push_back(l);
		}
		if(data[i] == '\n') {
			curr++;
		} else {
			buffer.lines[curr].value += data[i];
		}
	}
	this->render();
	move(0, 0);
}

void Editor::init() {
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	getmaxyx(stdscr, height, width);
	global_y = 0;
}


void Editor::exit() {
	endwin();
}

void Editor::render() {
	int curr_y = 0;
	int curr_x = 0;
	for(std::size_t i = 0; i<buffer.lines.size();i++) {
		curr_x = 0;
		for(int j = 0; j<buffer.lines[i].size();j++) {
			if(curr_x >= width) {
				buffer.lines[i].row++;
				curr_y++;
				curr_x = 0;
			}
			mvaddch(curr_y, curr_x, buffer.lines[i].value[j]);	
			curr_x++;
		}
		curr_y++;
		buffer.lines[i].row++;
	}
}

void Editor::update() {
#define C_MOVE(a, b) this->move_cursor(a, b); break;
	int ch = getch();
	switch(ch) {
		case KEY_DOWN:// move one step down
			C_MOVE(0, 1);
		case KEY_UP: // move one step up
			C_MOVE(0, -1);
		case KEY_RIGHT:// move one step right
			C_MOVE(1, 0);
		case KEY_LEFT: // move one step left
			C_MOVE(-1, 0);
	}
}
// pos = right, down
// neg = left, up
void Editor::move_cursor(int x, int y) {
	if(y == -1 && global_y == 0) return;
	if(y == 1 && global_y >= (int)buffer.lines.size()-1) return;
	int curr_y, curr_x;
	getyx(stdscr, curr_y, curr_x);
	if(y != 0) {
		if(y == -1) {
			global_y--;
			curr_y += -(buffer.lines[global_y].row);
		} else {
			curr_y += buffer.lines[global_y].row;
			global_y++;
		}
	} 
	move(curr_y, curr_x);
}
