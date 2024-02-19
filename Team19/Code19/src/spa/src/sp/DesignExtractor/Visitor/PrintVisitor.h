#pragma once

#include "sp/DesignExtractor/Visitor/IVisitor.h"
#include "sp/DesignExtractor/Extractor/PrintExtractor.h"
#include "sp/DesignExtractor/Extractor/VariableExtractor.h"

#include <iostream>
#include <stdexcept>

class PrintVisitor : public IVisitor {
public:
	PrintVisitor(std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriterManager> pkbWriterManager)
		: IVisitor(root, pkbWriterManager) {
		if (root->type != ASTNodeType::PRINT) {
			throw std::invalid_argument("PrintVisitor - root is not of type PRINT");
		}
	}

	void visit(std::shared_ptr<ASTNode> node) override;
	void visit() override;
};