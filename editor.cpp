#include "editor.hpp"
#include <sstream>
#include <iostream>
#include <fstream>

Editor::Editor() {
	this->interface = new Interface;
	buffer.push_back("");
}

Editor::Editor(std::string filename) {
	this->interface = new Interface;
	std::ifstream file(filename);
	std::stringstream buffer_str;
	buffer_str << file.rdbuf();
	std::string content = buffer_str.str();
	int b_c = 0;
	buffer.push_back("");
	for(uint64_t i=0; i<content.size();i++) {
		if(content[i] == '\n') {
			buffer.push_back("");
			b_c++;
		} else {
			buffer[b_c] += content[i];
		}
	}
	interface->write_buffer(buffer);
}

void Editor::exit() {
	interface->close();
}

void Editor::input() {
	char c = interface->input();
	// TOOD, make it work with arrow chars
	if(c == 'j') {
		interface->cursor_move_curr(0, 1);
	} else if(c == 'k') {
		interface->cursor_move_curr(0, -1);
	} else if(c == 'h') {
		interface->cursor_move_curr(-1, 0);
	} else if(c == 'l') {
		interface->cursor_move_curr(1, 0);
	}
}
