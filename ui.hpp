#ifndef UI_HPP
#define UI_HPP

#include <ncurses.h>
#include <vector>
#include <string>

class Interface {
	public:
		Interface();
		void write(int, int, char);
		void add(char);
		void del(int, int);
		void close();
		void cursor_move(int, int);
		void cursor_move_curr(int, int);
		void write_buffer(std::vector<std::string>);
		char input();
	private:
		std::vector<std::string> strbuf = {""};
		unsigned int width, height;
		int	curr_x, curr_y;
};


#endif
