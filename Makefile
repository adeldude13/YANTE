CC := clang++
cfiles := main.cpp ui.cpp editor.cpp
hfiles := ui.hpp editor.hpp
files := $(cfiles) $(hfiles) Makefile
out := main
args := -lncurses -O0 -ggdb3 -Wall -Wextra -o $(out)

main: $(files)
	$(CC) $(args) $(cfiles) && ./$(out)

clean:
	rm $(out)
