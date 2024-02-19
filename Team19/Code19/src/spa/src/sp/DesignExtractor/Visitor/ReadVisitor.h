#pragma once

#include "sp/DesignExtractor/Visitor/IVisitor.h"
#include "sp/DesignExtractor/Extractor/ReadExtractor.h"
#include "sp/DesignExtractor/Extractor/VariableExtractor.h"
#include <stdexcept>
#include <iostream>

class ReadVisitor : public IVisitor {
public:
	ReadVisitor(std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriterManager> pkbWriterManager)
		: IVisitor(root, pkbWriterManager) {
		if (root->type != ASTNodeType::READ) {
			throw std::invalid_argument("PrintVisitor - root is not of type PRINT");
		}
	}

	void visit(std::shared_ptr<ASTNode> node) override;
	void visit() override;
};