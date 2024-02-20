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
			throw std::invalid_argument("UsesExtractor: Invalid ASTNode type");
	}
}

void UsesExtractor::getAssignUses() {
	this->pkbWriterManager->getUsesSWriter()->addUsesS(ast1->lineNumber, ast2->value);
}

void UsesExtractor::getPrintUses() {
	this->pkbWriterManager->getUsesSWriter()->addUsesS(ast1->lineNumber, ast2->value);
}

void UsesExtractor::getIfUses() {
	this->pkbWriterManager->getUsesSWriter()->addUsesS(ast1->lineNumber, ast2->value);
}

void UsesExtractor::getWhileUses() {
	this->pkbWriterManager->getUsesSWriter()->addUsesS(ast1->lineNumber, ast2->value);
}

void UsesExtractor::getProcedureUses() {
	this->pkbWriterManager->getUsesPWriter()->addUsesP(ast1->value, ast2->value);
}

void UsesExtractor::getCallUses() {
	// Do nothing for now
}