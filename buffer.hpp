#ifndef BUFFER_HPP
#define BUFFER_HPP

#include <vector>
#include <string>

class Line {
	public:
		Line() {
			row = 0;
			value = "";
		}
		std::string value;
		int row;
		int size() {
			return (int)value.size();
		}
};

class Buffer { 
	public:
		std::vector<Line> lines;
};


#endif
