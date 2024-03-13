#include "sp/DesignExtractor/Extractor/RelationshipExtractor/UsesExtractor.h"

UsesSExtractor::UsesSExtractor(std::shared_ptr<ASTNode> ast1, std::shared_ptr<ASTNode> ast2,
	std::shared_ptr<UsesSWriter> usesSWriter) : IRelationshipExtractor(ast1, ast2) {
	this->usesSWriter = usesSWriter;
}

void UsesSExtractor::extract() {
	if (!ASTUtility::nodeStatementCanUses(ast1->getType())) return;
	usesSWriter->addUsesS(ast1->getLineNumber(), ast2->getValue());
}

UsesPExtractor::UsesPExtractor(std::shared_ptr<ASTNode> ast1, std::shared_ptr<ASTNode> ast2,
	std::shared_ptr<UsesPWriter> usesPWriter) : IRelationshipExtractor(ast1, ast2) {
	this->usesPWriter = usesPWriter;
}

void UsesPExtractor::extract() {
	if (!ast1->equalType(ASTNodeType::PROCEDURE)) return;
	usesPWriter->addUsesP(ast1->getValue(), ast2->getValue());
}