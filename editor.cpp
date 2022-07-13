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

void Editor::move_cursor(int x, int y) {

	int curr_x, curr_y;
	getyx(stdscr, curr_y, curr_x);
	if((std::size_t)(global_x + x) < buffer.values[global_y].size()) {
		
		if(curr_x + x >= width) 
		{
			move(curr_y+1, 0);
		} 
		else if(curr_x + x < 0 && global_x != 0) 
		{
			move(curr_y-1, width-1);
		} 
		else 
		{
			move(curr_y, curr_x + x);
		}
		global_x += x;
#ifdef DEBUG
		getyx(stdscr, curr_y, curr_x);
		move(height-1, width/2);
		printw("                                                           ");
		move(height-1, width/2);
		printw("gx: %i cx: %i", global_x, curr_x);
		move(curr_y, curr_x);
#endif

	} else {
		y++;
	}

}

int Editor::moveToLine() { 
	int USELESS, y;
	getyx(stdscr, USELESS, y);
	USELESS++;
	int jump = round(buffer.values[y].size() / width);
	return jump;
}
