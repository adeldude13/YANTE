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
	private:
		Buffer buffer;
		int width, height;
		int global_y, global_x = 0;
};


#endif
