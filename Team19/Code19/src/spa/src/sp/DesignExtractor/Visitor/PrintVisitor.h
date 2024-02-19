#pragma once

#include "sp/DesignExtractor/Visitor/IVisitor.h"
#include "sp/DesignExtractor/Extractor/PrintExtractor.h"
#include "sp/DesignExtractor/Extractor/VariableExtractor.h"

#include <iostream>
#include <stdexcept>

class PrintVisitor : public IVisitor {
public:
	PrintVisitor(std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriterManager> pkbWriterManager);

	void visit(std::shared_ptr<ASTNode> node) override;
	void visit() override;
};