#include "SimpleLineManager.h"

SimpleLineManager::SimpleLineManager() {
	this->lineNumber = 0;
}

int SimpleLineManager::getLine() {
	return this->lineNumber;
}

void SimpleLineManager::nextLine() {
	this->lineNumber++;
}

int SimpleLineManager::getProgramLineNumber() {
	return SimpleLineManager::PROGRAM_LINE_NUMBER;
}
