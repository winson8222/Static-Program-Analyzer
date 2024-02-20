#pragma once

#include "sp/DesignExtractor/Visitor/IVisitor.h"
#include "sp/DesignExtractor/Extractor/ReadExtractor.h"
#include "sp/DesignExtractor/Extractor/VariableExtractor.h"
#include <stdexcept>
#include <iostream>

class ReadVisitor : public StatementVisitor {
public:
	ReadVisitor(std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriterManager> pkbWriterManager)
		: StatementVisitor(root, pkbWriterManager) {
		if (root->type != ASTNodeType::READ) {
			throw std::invalid_argument("ReadVisitor - root is not of type PRINT");
		}
		if (root->children.size() != 1) {
			throw std::invalid_argument("ReadVisitor - root does not have 1 child");
		}
	}

	void visit() override;
};