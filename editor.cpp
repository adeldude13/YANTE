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
	this->status();
	this->render();
	move(0, 0);
}

void Editor::init() {
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	getmaxyx(stdscr, height, width);
	height-=1; // for the status
	set_escdelay(0);
}


void Editor::exit() {
	endwin();
}

void Editor::status() {
	move(height, width/2-10);
	printw("															");
	move(height, width/2-10);
	printw("X:%i Y:%i H:%i V:%i", posx, posy, h, v);
	printw(" || mode: %s", (mode == INSERT ? "insert" : "normal"));
	move(posy, posx);
}

void Editor::set_mode(MODE m) {
	mode = m;
	if(mode == NORMAL && posx >= buffer.lines[posy].size()) {
		posx--;
	}
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
END:
	move(posy, posx);
}

void Editor::update() {
#define C_MOVE(a, b) this->move_cursor(a, b); goto END;
#define INSERT(c) buffer.lines[posy].value.insert(h+posx, std::string(1, (char)c));C_MOVE(1, 0);this->render();goto END;
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
	if(ch == 'i' && mode == NORMAL) {
		set_mode(INSERT);
		goto END;
	} else if(mode == INSERT) {
		if(ch == 27) {
			set_mode(NORMAL);
			goto END;
		} 
		INSERT(ch);
	}
END:
	this->status();
}

// pos = right, down
// neg = left, up
void Editor::move_cursor(int x, int y) {

	if(x != 0) {
		
		if(posx + x + h > (int)buffer.lines[posy].size() && mode == INSERT) return;
		if(posx + x + h >= (int)buffer.lines[posy].size() && mode == NORMAL) return;
		if(posx + x == -1 && h == 0) return;
		if(posx+x >= width) {
			h++;
		} else if(posx == 0 && x == -1 && h >= 1) {
			h--;
		} else {
			posx += x;
		}

	} else if(y != 0) {
		
		if(global_y >= (int)buffer.lines.size()-1 && y == 1) return;
		if(global_y == 0 && y == -1) return;
		if(posy >= height-1 && y == 1) {
			v++;
			global_y += 1;
		} else if(posy == 0 && y == -1 && v > 0) {
			v--;	
			global_y -= 1;
		} else {
			posy += y;
			global_y += y;
		}
		while(h >= buffer.lines[posy].size() && h != 0) {
			h--;
		}
		if(posx+h >= buffer.lines[posy].size()) {
			posx = buffer.lines[posy].size()-h-1;
		}

	}
	this->render();
}
