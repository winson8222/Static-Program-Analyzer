#pragma once

#include "sp/DesignExtractor/Visitor/IVisitor.h"
#include "sp/DesignExtractor/Extractor/VariableExtractor.h"
#include "sp/DesignExtractor/Extractor/UsesExtractor.h"
#include "sp/DesignExtractor/Extractor/ModifiesExtractor.h"
#include <stdexcept>
#include <iostream>

class VariableVisitor : public IVisitor {
public:
	VariableVisitor(std::shared_ptr<ASTNode> root,
		std::shared_ptr<PKBWriterManager> pkbWriterManager)
		: IVisitor(root, pkbWriterManager) {
		if (root->type != ASTNodeType::VARIABLE) {
			throw std::invalid_argument("ERROR: VARIABLE NOT SUPPORTED");
		}
		if (root->children.size() != 0) {
			throw std::invalid_argument("ERROR: VARIABLE HAVE LEAFS");
		}
	}

	void visit() override;

	/*
	* Set current Variable Visitor to contains context of which statement or procedure uses it
	*/
	void setUsedContext(listnode contexts, std::shared_ptr<ASTNode> parent);
	void setModifiedContext(listnode contexts, std::shared_ptr<ASTNode> parent);
	
private:
	std::vector<std::shared_ptr<ASTNode>> usedContexts;
	std::vector<std::shared_ptr<ASTNode>> modifiedContexts;
};