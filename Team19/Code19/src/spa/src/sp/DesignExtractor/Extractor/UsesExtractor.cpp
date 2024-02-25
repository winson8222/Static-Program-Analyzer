#include "sp/DesignExtractor/Extractor/UsesExtractor.h"

void UsesExtractor::extract() {
	switch (ast1->type) {
		case ASTNodeType::ASSIGN:
			getAssignUses();
			break;
		case ASTNodeType::PRINT:
			getPrintUses();
			break;
		case ASTNodeType::IF_ELSE_THEN:
			getIfUses();
			break;
		case ASTNodeType::WHILE:
			getWhileUses();
			break;
		case ASTNodeType::PROCEDURE:
			getProcedureUses();
			break;
		case ASTNodeType::CALL:
			getCallUses();
			break;
		default:
			// to do: throwexception
			// this will be handled in M2
			break;
	}
}

void UsesExtractor::getAssignUses() {
	// Add uses for the variable in the assignment statement
	this->pkbWriterManager->getUsesSWriter()->addUsesS(ast1->lineNumber, ast2->value);
}

void UsesExtractor::getPrintUses() {
	// Add uses for the variable in the print statement
	this->pkbWriterManager->getUsesSWriter()->addUsesS(ast1->lineNumber, ast2->value);
}

void UsesExtractor::getIfUses() {
	// Add uses for the variable in the if statement
	this->pkbWriterManager->getUsesSWriter()->addUsesS(ast1->lineNumber, ast2->value);
}

void UsesExtractor::getWhileUses() {
	// Add uses for the variable in the while statement
	this->pkbWriterManager->getUsesSWriter()->addUsesS(ast1->lineNumber, ast2->value);
}

void UsesExtractor::getProcedureUses() {
	// Add uses for the variable in the procedure
	this->pkbWriterManager->getUsesPWriter()->addUsesP(ast1->value, ast2->value);
}

void UsesExtractor::getCallUses() {
	// Do nothing for now
	// will need to handle later in M2
}