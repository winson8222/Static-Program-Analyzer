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
			break;
			// throw std::invalid_argument("Modifies Extractor: Invalid ASTNode type");
	}
}

void ModifiesExtractor::getAssignModifies() {
	this->pkbWriterManager->getModifiesSWriter()->addModifiesP(ast1->lineNumber, ast2->value);
}

void ModifiesExtractor::getReadModifies() {
	this->pkbWriterManager->getModifiesSWriter()->addModifiesP(ast1->lineNumber, ast2->value);
}

void ModifiesExtractor::getIfModifies() {
	this->pkbWriterManager->getModifiesSWriter()->addModifiesP(ast1->lineNumber, ast2->value);
}

void ModifiesExtractor::getWhileModifies() {
	this->pkbWriterManager->getModifiesSWriter()->addModifiesP(ast1->lineNumber, ast2->value);
}

void ModifiesExtractor::getProcedureModifies() {
	this->pkbWriterManager->getModifiesPWriter()->addModifiesP(ast1->value, ast2->value);
}

void ModifiesExtractor::getCallModifies() {
	// Do nothing for now
}