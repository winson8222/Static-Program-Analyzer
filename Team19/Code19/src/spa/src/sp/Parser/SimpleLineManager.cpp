#include "SimpleLineManager.h"

// Default constructor definition
SimpleLineManager::SimpleLineManager() {
	this->line = 0;
}

// Function to get the current line number
int SimpleLineManager::getLine() {
	return line;
}

// Function to move to the next line
void SimpleLineManager::nextLine() {
	line++;
}

int SimpleLineManager::getProgramLineNumber() {
	return SimpleLineManager::PROGRAM_LINE_NUMBER;
}