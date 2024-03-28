#include "sp/DesignExtractor/Extractor/RelationshipExtractor/ModifiesExtractor.h"

ModifiesSExtractor::ModifiesSExtractor(std::shared_ptr<ASTNode> ast1, std::shared_ptr<ASTNode> ast2, 
	std::shared_ptr<ModifiesSWriter> modifiesSWriter) : IRelationshipExtractor(ast1, ast2) {
	this->modifiesSWriter = modifiesSWriter;
}

void ModifiesSExtractor::extract() {
	// Add modifies to the ModifiesS table
	if (!ASTUtility::nodeStatementCanModifies(ast1->getType())) return;
	this->modifiesSWriter->addModifiesS(ast1->getLineNumber(), ast2->getValue());
}

ModifiesPExtractor::ModifiesPExtractor(std::shared_ptr<ASTNode> ast1, std::shared_ptr<ASTNode> ast2,
	std::shared_ptr<ModifiesPWriter> modifiesPWriter) : IRelationshipExtractor(ast1, ast2) {
	this->modifiesPWriter = modifiesPWriter;
}

void ModifiesPExtractor::extract() {
	// Add modifies to the ModifiesP table
	if (!ast1->equalType(ASTNodeType::PROCEDURE)) return;
	this->modifiesPWriter->addModifiesP(ast1->getValue(), ast2->getValue());
}
