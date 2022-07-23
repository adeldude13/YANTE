#ifndef EDITOR_HPP
#define EDITOR_HPP

#include "lines.hpp"

class Editor {
	public:
		Editor();
		Editor(std::string);
		void init(), cleanup();

		/* --------------------- */ 		
		void update(), render(), input();
		void cursor_move(int, int);
		
	private:
		int cursor_x, cursor_y;
		int width, height;
		Lines lines;
};


#endif
