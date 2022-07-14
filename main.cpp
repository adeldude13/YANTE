#include "editor.hpp"
#include <ncurses.h>

int main() {
	Editor editor("Some Text Im Writing Because I want to Test My stupid text editor that nobody will ever use haha this is cool very cool very amazing i love it so much fuck windows Linux FTWWW!!Some Text Im Writing Because I want to Test My stupid text editor that nobody will ever use haha this is cool very cool very amazing i love it so much fuck windows Linux FTWWW!!\nnewline this ;alksdfj;ljkjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjj\nas;dfasdf");
	while(1) { editor.update();	}
	editor.exit();
}
