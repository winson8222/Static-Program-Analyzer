#include "IRelationshipExtractor.h"

void IRelationshipExtractor::setASTs(std::shared_ptr<ASTNode> ast1, std::shared_ptr<ASTNode> ast2) {
	this->ast1 = std::move(ast1);
	this->ast2 = std::move(ast2);
}

void ICFGExtractor::setCFGs(std::shared_ptr<CFGNode> cfg1, std::shared_ptr<CFGNode> cfg2) {
	this->cfg1 = std::move(cfg1);
	this->cfg2 = std::move(cfg2);
}