#include "ui.hpp"
#include <iostream>
#include <ncurses.h>
#include <inttypes.h>

#define CTRL(x) ((char)(x & 0x1f))

Interface::Interface() {
	initscr();
	noecho();
	cbreak();
	keypad(stdscr, 1);
	getmaxyx(stdscr, height, width);
	for(unsigned int i=0; i<height;i++) {
		this->write(0, i, '~');
	}
	move(0, 0);
	refresh();
}

char Interface::input() {
	return (char)getch();
}

void Interface::renderbuf() {
	for(uint64_t i=0; i<strbuf.size();i++) {
		curr_y++;
		curr_x = 0;
		for(uint64_t j = 0; j<strbuf[i].size();j++) {
			this->write(curr_x, curr_y, strbuf[i][j]);
			curr_x++;
		}
	}
	refresh();
	curr_y = -1;
	curr_x = 0;
}

void Interface::write_buffer(std::vector<std::string> buffer) {
	curr_y = -1;
	strbuf = buffer;
	this->renderbuf();
	this->cursor_move(0, 0);
	refresh();
}

void Interface::cursor_move(int x, int y) {
	move(y, x);
}


void Interface::close() {
	endwin();
}

void Interface::write(int x, int y, char c) {
	mvaddch(y, x, c);
}
 
void Interface::add(char c) {
	int c_x, c_y;
	getyx(stdscr, c_y, c_x);
	std::string add = "";
	add += c;
	strbuf[c_y].insert(c_x, add);
	this->renderbuf();
	move(c_y, c_x+1);
}

void Interface::del(int x, int y) {
	std::cout << x << " " << y << std::endl;
	// TODO
}

void Interface::cursor_move_curr(int x, int y) {
	int c_x, c_y;
	getyx(stdscr, c_y, c_x);
	if(x == 0) {
		if((int)strbuf[c_y + y].size() <= c_x) {
			move(((c_y + y) <= (int)strbuf.size()-1 ? (c_y + y) : 0), strbuf[c_y+y].size()-1);
		} else {
			move(((c_y + y) <= (int)strbuf.size()-1 ? (c_y + y) : 0), c_x);
		}
	} else if(y == 0) {
		if(c_x + x <= (int)strbuf[c_y].size()-1) {
			move(c_y, c_x + x);
		}
	}
}
