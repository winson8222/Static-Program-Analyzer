#include "sp/DesignExtractor/Extractor/AssignExtractor.h"

void AssignExtractor::extract() {
	// Extract all the assign statements
	this->pkbWriterManager->getAssignWriter()->insertAssign(this->root->lineNumber);

	// Extract the assign patterns (all sub-patterns are extracted within PKB API)
	this->pkbWriterManager->getAssignPatternWriter()->addAssignPattern(
		this->root->lineNumber, 
		this->root->children[0]->value, 
		this->root->children[1]->getRPNForm()
	);

	// Extract the assign statement
	this->pkbWriterManager->getStatementWriter()->insertStatement(this->root->lineNumber);
}