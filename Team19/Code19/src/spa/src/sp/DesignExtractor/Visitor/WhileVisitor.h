#pragma once

#include "sp/DesignExtractor/Visitor/IVisitor.h"
#include "sp/DesignExtractor/Extractor/WhileExtractor.h"
#include "sp/DesignExtractor/Visitor/RelExpressionVisitor.h"
#include "sp/DesignExtractor/Visitor/StatementListVisitor.h"
#include <stdexcept>
#include <memory>

class WhileVisitor : public IVisitor {
public:
	WhileVisitor(std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriterManager> pkbWriterManager);

	void visit(std::shared_ptr<ASTNode> node) override;
	void visit() override;
};