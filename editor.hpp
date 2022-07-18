#ifndef EDITOR_HPP
#define EDITOR_HPP

#include <string>
#include "buffer.hpp"

typedef enum {
	INSERT,
	NORMAL,
} MODE;

class Editor {
	public:
		Editor();
		Editor(std::string);
		void init(), exit();
		void render(), update();
		void move_cursor(int, int);
		int moveToLine(bool);
		void status(), set_mode(MODE), DELETE(bool), DELETE_CURR();
		void command();
		void execommand(std::string);
		bool isClosed;
	private:
		Buffer buffer;
		int global_y = 0;
		int width, height;
		int h=0, v = 0;
		int posx=0, posy = 0;
		bool closed = 0;
		MODE mode = NORMAL;
};


#endif
