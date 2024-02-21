#include "sp/DesignExtractor/Extractor/AssignExtractor.h"

void AssignExtractor::extract() {
	// Extract all the assign statements
	this->pkbWriterManager->getAssignWriter()->insertAssign(this->root->lineNumber);
	this->pkbWriterManager->getAssignPatternWriter()->addAssignPattern(
		this->root->lineNumber, 
		this->root->children[0]->value, 
		this->root->children[1]->getRPNForm()
	);
	this->pkbWriterManager->getStatementWriter()->insertStatement(this->root->lineNumber);
}