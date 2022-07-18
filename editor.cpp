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
	isClosed = false;
}


void Editor::exit() {
	endwin();
}

void Editor::status() {
	int size = std::to_string(posy+1).size() + std::to_string(posx+1).size() + 22;
#define CLEAR() do { \
		for(int i=0; i<size;i++) { \
			printw(" "); \
		} \
	} while(false)
	move(height, width-size);
	CLEAR();	
	move(height, width-size);
	printw("X:%i Y:%i", posx+1, posy+1);
	printw(" || mode: %s", (mode == INSERT ? "insert" : "normal"));
	move(posy, posx);
}

void Editor::set_mode(MODE m) {
	mode = m;
	if(posx > 0 && m == NORMAL) {
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

void Editor::DELETE(bool isNormal=false) {
	if(posx == 0 && !isNormal) {
		return;
	}
	if(posx < buffer.lines[posy].size()) {
		buffer.lines[posy].value.erase(posx-(isNormal ? 0 : 1) , 1);
	} else if(buffer.lines[posy].size() != 0) {
		buffer.lines[posy].value.erase(posx-1, 1);	
	}

	posx--;
	posx += (posx == -1 ? 1 : 0);
	this->render();
}

void Editor::DELETE_CURR() {
	if(buffer.lines.size() == 0) {
		return;
	}
	buffer.lines.erase(buffer.lines.begin()+posy);
	if(posy >= (int)buffer.lines.size()) {
		posy--;
	}
	this->render();
}

void Editor::command() {
	std::string line = "";
	char c;
	move(height, 0);
	addch(':');
	while((c = getch()) != '\n') {
		if(c == 27) {
			move(height, 0);
			for(int i=0; i<(int)line.size()+1;i++) {
				printw(" ");
			}
			return;
		}
		addch(c);
		line += c;
	}
	this->execommand(line);
	move(height, 0);
	for(int i=0; i<(int)line.size()+1;i++) {
		printw(" ");	
	}
	move(posy, posx);
}

void Editor::execommand(std::string cmd) {
	if(cmd == "w") {
		// TODO : save the current content to the file
	} else if(cmd == "q") {
		isClosed = true;
	}
}

void Editor::update() {
	this->status();
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
	// 27 == ESC
	if(mode == NORMAL) {
		if(ch == 'i') { set_mode(INSERT); goto END;} 
		switch(ch) {
			case 'j':// move one step down
				C_MOVE(0, 1);
			case 'k': // move one step up
				C_MOVE(0, -1);
			case 'l':// move one step right
				C_MOVE(1, 0);
			case 'h': // move one step left
				C_MOVE(-1, 0);
		}
		if(ch == 'x') DELETE(true);
		if(ch == ':') command();
		if(ch=='d') {
			ch = getch(); // wait till you get another char
			if(ch == 'd') {
				DELETE_CURR();
				goto END;
			}
		}
	} else if(mode == INSERT) {
		if(ch == 27) {
			set_mode(NORMAL); goto END; 
		} else if(ch == KEY_BACKSPACE) {
			DELETE();
		} else { 
			INSERT(ch); 
		}
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
