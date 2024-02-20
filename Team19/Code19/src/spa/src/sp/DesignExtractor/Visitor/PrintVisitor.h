#pragma once

#include "sp/DesignExtractor/Visitor/IVisitor.h"
#include "sp/DesignExtractor/Extractor/PrintExtractor.h"
#include "sp/DesignExtractor/Extractor/VariableExtractor.h"

#include <iostream>
#include <stdexcept>

class PrintVisitor : public StatementVisitor {
public:
	PrintVisitor(std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriterManager> pkbWriterManager);

	void visit() override;
};