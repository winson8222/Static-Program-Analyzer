#pragma once

#include "sp/DesignExtractor/Visitor/IVisitor.h"
#include "sp/DesignExtractor/Extractor/WhileExtractor.h"
#include "sp/DesignExtractor/Extractor/ParentExtractor.h"
#include "sp/DesignExtractor/Visitor/ExpressionVisitor.h"
#include "sp/DesignExtractor/Visitor/StatementListVisitor.h"
#include <stdexcept>
#include <memory>

class WhileVisitor : public StatementVisitor {
public:
	WhileVisitor(std::shared_ptr<ASTNode> root, 
		listnode context, 
		std::shared_ptr<PKBWriterManager> pkbWriterManager);

	void visit() override;
	void addContext(std::shared_ptr<ASTNode> context) override;
};