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
		listnode context,
		std::shared_ptr<PKBWriterManager> pkbWriterManager)
		: IVisitor(root, pkbWriterManager) {
		if (root->type != ASTNodeType::VARIABLE) {
			throw std::invalid_argument("ERROR: VARIABLE NOT SUPPORTED");
		}
		if (root->children.size() != 0) {
			throw std::invalid_argument("ERROR: VARIABLE HAVE LEAFS");
		}
		this->contexts = listnode(context.begin(), context.end());
	}

	void visit() override;
	void setContext(std::vector<std::shared_ptr<ASTNode>> contexts, std::shared_ptr<ASTNode> parent);
	std::vector<std::shared_ptr<ASTNode>> contexts;
};