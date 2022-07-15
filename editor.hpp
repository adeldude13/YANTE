#ifndef EDITOR_HPP
#define EDITOR_HPP

#include <string>
#include "buffer.hpp"

class Editor {
	public:
		Editor();
		Editor(std::string);
		void init(), exit();
		void render(), update();
		void move_cursor(int, int);
		int moveToLine(bool);
		void loop();
	private:
		Buffer buffer;
		int width, height;
		int h, v = 0;
		int posx=0, posy = 0;
};


#endif
