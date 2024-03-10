#include "SimpleLineTracker.h"

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

static int SimpleLineManager::getProgramLineNumber() {
	return PROGRAM_LINE_NUMBER;
}