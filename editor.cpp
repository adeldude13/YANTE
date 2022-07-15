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
}


void Editor::exit() {
	endwin();
}

void Editor::render() {
	clear();
	for(int i=v; i<(int)buffer.lines.size();i++) {
		if(i >= height+v) {
			goto END;
		}
		for(int j=h; j<buffer.lines[i].size();j++) {
			if(j < width+h) {
				mvaddch(i-v, j-h, buffer.lines[i].value[j]);
			}
		}
	}
#ifdef DEBUG
	move(height-1, width/2);
	printw("														");
	move(height-1, width/2);
	printw("Y:%i X:%i", posy, posx);
#endif
END:
	move(posy, posx);
}

void Editor::update() {
#define C_MOVE(a, b) this->move_cursor(a, b); return;
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

	if(x != 0) {
		if(posx + x + h >= (int)buffer.lines[posy].size()) return;
		if(posx + x == -1 && h > 0) h--;
		if(posx + x == -1) return;
		if(posx+x >= width) {
			h++;
		} else {
			posx += x;
		}
	} else if(y != 0) {
		if(posy + y + v >= (int)buffer.lines.size()) return;
		if(posy + y == -1 && v > 0) v--;
		if(posy + y == -1) return;
		posy += y;
		if(posy >= height) {
			v++;
		}

		if(posx >= buffer.lines[posy].size()) {
			posx = buffer.lines[posy].size()-1;
			if(posx == -1) posx = 0;
		}
	}
	this->render();
}
