#include "sp/DesignExtractor/Extractor/ModifiesExtractor.h"

void ModifiesExtractor::extract() {
	switch (ast1->type) {
		case ASTNodeType::ASSIGN:
			getAssignModifies();
			break;
		case ASTNodeType::READ:
			getReadModifies();
			break;
		case ASTNodeType::IF_ELSE_THEN:
			getIfModifies();
			break;
		case ASTNodeType::WHILE:
			getWhileModifies();
			break;
		case ASTNodeType::PROCEDURE:
			getProcedureModifies();
			break;
		case ASTNodeType::CALL:
			getCallModifies();
			break;
		default:
			// to do: throw exception
			// for now bugs will happen if exception is thrown so will handle in M2
			break;
	}
}

void ModifiesExtractor::getAssignModifies() {
	// Add modifies to the ModifiesS table
	this->pkbWriterManager->getModifiesSWriter()->addModifiesS(ast1->lineNumber, ast2->value);
}

void ModifiesExtractor::getReadModifies() {
	// Add modifies to the ModifiesS table
	this->pkbWriterManager->getModifiesSWriter()->addModifiesS(ast1->lineNumber, ast2->value);
}

void ModifiesExtractor::getIfModifies() {
	// Add modifies to the ModifiesS table
	this->pkbWriterManager->getModifiesSWriter()->addModifiesS(ast1->lineNumber, ast2->value);
}

void ModifiesExtractor::getWhileModifies() {
	// Add modifies to the ModifiesS table
	this->pkbWriterManager->getModifiesSWriter()->addModifiesS(ast1->lineNumber, ast2->value);
}

void ModifiesExtractor::getProcedureModifies() {
	// Add modifies to the ModifiesP table
	this->pkbWriterManager->getModifiesPWriter()->addModifiesP(ast1->value, ast2->value);
}

void ModifiesExtractor::getCallModifies() {
	// Do nothing for now
	// ideas: will need to modify pointers/variables in the future
	this->pkbWriterManager->getModifiesSWriter()->addModifiesS(ast1->lineNumber, ast2->value);
}