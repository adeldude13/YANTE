#include "lines.hpp"

int main() {
	Lines lines;
	lines.addLine("test1");
	lines.addLine("test2");
	lines.printall();
	lines.freeall();
	lines.printall();
	return 0;
}
