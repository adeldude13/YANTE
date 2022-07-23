CC := g++
cfiles := main.cpp lines.cpp editor.cpp
hfiles :=	lines.hpp editor.hpp
files := $(cfiles) $(hfiles) Makefile
out := main
args := -lncurses -O0 -ggdb3 -Wall -Wextra -o $(out)

main: $(files)
	- $(CC) $(args) $(cfiles) 
	- ./$(out)

clean:
	rm $(out)
