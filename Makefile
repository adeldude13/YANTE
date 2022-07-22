CC := g++
cfiles := main.cpp lines.cpp
hfiles :=	lines.hpp
files := $(cfiles) $(hfiles) Makefile
out := main
args := -lncurses -O0 -ggdb3 -Wall -Wextra -o $(out)

main: $(files)
	$(CC) $(args) $(cfiles) 

clean:
	rm $(out)
