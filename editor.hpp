#ifndef EDITOR_HPP
#define EDITOR_HPP

#include <vector>
#include "ui.hpp"

class Editor {
	public:
		Editor();
		Editor(std::string);
		void input();
		void exit();
	private:
		std::vector<std::string> buffer;
		Interface *interface;
};


#endif
