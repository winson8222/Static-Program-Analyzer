#pragma once

#include "sp/DesignExtractor/Visitor/IVisitor.h"
#include "sp/DesignExtractor/Extractor/VariableExtractor.h"
#include "sp/DesignExtractor/Extractor/ConstantExtractor.h"
#include "sp/Utility.h"

#include <iostream>
#include <stdexcept>

/*
* Visitor for visiting the RelExpression node - to be used on While + If nodes
*/
class ExpressionVisitor : public IVisitor {
public:
	ExpressionVisitor(std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriterManager> pkbWriterManager);
	void visit() override;
	void depthFirstSearch(std::shared_ptr<ASTNode> node);
};

class ArithmeticExpressionVisitor : public ExpressionVisitor {
public:
	using ExpressionVisitor::ExpressionVisitor;
	void depthFirstSearch(std::shared_ptr<ASTNode> node);
};