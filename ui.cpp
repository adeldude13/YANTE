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

void Interface::write_buffer(std::vector<std::string> buffer) {
	curr_y = -1;
	for(uint64_t i=0; i<buffer.size();i++) {
		curr_y++;
		curr_x = 0;
		for(uint64_t j = 0; j<buffer[i].size();j++) {
			this->write(curr_x, curr_y, buffer[i][j]);
			curr_x++;
		}
	}
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
	addch(c);
}

void Interface::del(int x, int y) {
	std::cout << x << " " << y << std::endl;
	// TODO
}
