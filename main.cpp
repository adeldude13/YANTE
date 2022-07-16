#include "editor.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

int main(/* int argc, char **argv*/ ) {
	/* if(argc != 2) {
		std::cout << argv[0] << " {file name}";
		return 1;
	} */
	// std::ifstream file(argv[1]);
	std::ifstream file("file.txt");
	std::stringstream str;
	str << file.rdbuf();
	Editor editor(str.str());
	while(1) editor.update();
	editor.exit();
	return 0;
}
