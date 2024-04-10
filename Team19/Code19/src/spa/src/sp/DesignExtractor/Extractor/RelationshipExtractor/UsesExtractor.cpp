#include "sp/DesignExtractor/Extractor/RelationshipExtractor/UsesExtractor.h"

UsesSExtractor::UsesSExtractor(std::shared_ptr<UsesSWriter> usesSWriter) : IRelationshipExtractor() {
	this->usesSWriter = usesSWriter;
}

void UsesSExtractor::extract(std::shared_ptr<ASTNode> ast1, std::shared_ptr<ASTNode> ast2) {
	if (!ASTUtility::nodeStatementCanUses(ast1->getType())) return;
	usesSWriter->addUsesS(ast1->getLineNumber(), ast2->getValue());
}

UsesPExtractor::UsesPExtractor(std::shared_ptr<UsesPWriter> usesPWriter) : IRelationshipExtractor() {
	this->usesPWriter = usesPWriter;
}

void UsesPExtractor::extract(std::shared_ptr<ASTNode> ast1, std::shared_ptr<ASTNode> ast2) {
	if (!ast1->equalType(ASTNodeType::PROCEDURE)) return;
	usesPWriter->addUsesP(ast1->getValue(), ast2->getValue());
}
