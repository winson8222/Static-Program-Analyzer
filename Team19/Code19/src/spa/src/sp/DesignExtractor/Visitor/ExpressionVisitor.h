#pragma once

#include "sp/DesignExtractor/Visitor/IVisitor.h"
#include "sp/DesignExtractor/Visitor/VariableVisitor.h"
#include "sp/DesignExtractor/Extractor/VariableExtractor.h"
#include "sp/DesignExtractor/Extractor/ConstantExtractor.h"
#include "sp/AST/ASTUtility.h"

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
	void setUsedContext(listnode contexts, std::shared_ptr<ASTNode> parent);
	listnode usedContexts;
};

class ArithmeticExpressionVisitor : public ExpressionVisitor {
public:
	using ExpressionVisitor::ExpressionVisitor;
	void depthFirstSearch(std::shared_ptr<ASTNode> node);
};