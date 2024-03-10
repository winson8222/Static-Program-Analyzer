#include "SimpleLineManager.h"

// Default constructor definition
SimpleLineManager::SimpleLineManager() {
	this->lineNumber = 0;
}

// Function to get the current line number
int SimpleLineManager::getLine() {
	return this->lineNumber;
}

// Function to move to the next line
void SimpleLineManager::nextLine() {
	this->lineNumber++;
}

int SimpleLineManager::getProgramLineNumber() {
	return SimpleLineManager::PROGRAM_LINE_NUMBER;
}