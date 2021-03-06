#include "lines.hpp"
#include <iostream>
#include <string>

std::size_t Line::size() {
	return content.size();
}

char &Line::operator[](unsigned int i) {
	return content[i];
}

Lines::Lines() {
	this->addLine("");
}


void Lines::fill(std::string str) {
	if(head == nullptr) {
		this->addLine("");
	}
	Line *currLine = head;
	for(std::size_t i=0; i<str.size();i++) {
		if(str[i] == '\n') {
			this->addLine("");
			currLine = this->getNext(currLine);
		} else {
			currLine->content += str[i];
		}
	}
}

Line *Lines::getNext(Line *ptr) {
	if(ptr == nullptr || ptr->next == nullptr) {
		return nullptr;
	}
	return ptr->next;
}

Line *Lines::getPrev(Line *ptr) {
	if(ptr == nullptr || ptr->prev == nullptr) {
		return nullptr;
	}
	return ptr->prev;
}

void Lines::addLine(std::string v) {
	if(head == nullptr) {
		head = new Line;
		head->content = v;
		return;
	}
	Line *curr = head;
	while(curr->next != nullptr) {
		curr = curr->next;
	}
	curr->next = new Line;
	curr->next->content = v;
	curr->next->prev = curr;
}

void Lines::deleteLine(Line *ptr) {
	if(ptr == head) {
		Line *temp = head;
		head = head->next;
		head->prev = nullptr;
		delete temp;
		return;
	}
	if(ptr->prev != nullptr) {
		ptr->prev->next = ptr->next;
	}
	if(ptr->next != nullptr) {
		ptr->next->prev = ptr->prev;
	}
	delete ptr;
}

void Lines::freeall() {
	if(clean) return;
	Line *ptr = head;		
	while(ptr != nullptr) {
		Line *temp = ptr;
		ptr = ptr->next;
		delete temp;
	}
	clean = true;
}

void Lines::printall() {
	if(clean) return;
	Line *ptr = head;	
	std::cout << "NULL -> ";
	while(ptr != nullptr) {
		std::cout << ptr->content << " -> ";
		ptr = ptr->next;
	}
	std::cout << "NULL" << std::endl;
}

