#pragma once

#include "sp/DesignExtractor/Visitor/IVisitor.h"
#include "sp/DesignExtractor/Visitor/AssignVisitor.h"
#include "sp/DesignExtractor/Visitor/WhileVisitor.h"
#include "sp/DesignExtractor/Visitor/IfElseThenVisitor.h"
#include "sp/DesignExtractor/Visitor/CallVisitor.h"
#include "sp/DesignExtractor/Visitor/ReadVisitor.h"
#include "sp/DesignExtractor/Visitor/PrintVisitor.h"

#include "sp/Utility.h"
#include <stdexcept>
#include <iostream>

class StatementListVisitor : public IVisitor {
public:
	StatementListVisitor(std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriterManager> pkbWriterManager)
		: IVisitor(root, pkbWriterManager) {}

	void visit(std::shared_ptr<ASTNode> node) override;
	void visit() override;
};