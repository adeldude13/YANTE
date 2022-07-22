#ifndef LINES_HPP
#define LINES_HPP

#include <string>

class Line {
	public:
		std::string content = "";
		Line *prev = nullptr;
		Line *next = nullptr;
		std::size_t size();
		char operator[](unsigned int i);
};

class Lines {
	public:
		Line *head = nullptr;
		void addLine(std::string);
		void deleteLine(Line *);
		void freeall();
		void printall();
	private:
		bool clean = false;
};

#endif
