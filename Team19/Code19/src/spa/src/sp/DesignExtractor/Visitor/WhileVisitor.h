#pragma once

#include "sp/DesignExtractor/Visitor/IVisitor.h"
#include "sp/DesignExtractor/Extractor/EntityExtractor/WhileExtractor.h"
#include "sp/DesignExtractor/Extractor/RelationshipExtractor/ParentExtractor.h"
#include "sp/DesignExtractor/Visitor/ExpressionVisitor.h"
#include "sp/DesignExtractor/Visitor/StatementListVisitor.h"
#include <stdexcept>
#include <memory>

// Define constants for the indices
constexpr int WHILE_EXPRESSION_INDEX = 0;
constexpr int WHILE_STATEMENT_LIST_INDEX = 1;

/*
* A visitor for the while statement which should
* call on all relevant extractors and sub-visitors
* 
* This class is inherited from the IVisitor class,
* so additional documentation should be taken from the
* base abstract class unless further specified
*/
class WhileVisitor : public StatementVisitor {
public:
	WhileVisitor(std::shared_ptr<ASTNode> root, 
		listnode context, 
		std::shared_ptr<PKBWriterManager> pkbWriterManager);

	void visit() override;

private:
	std::shared_ptr<ASTNode> expression;
	std::shared_ptr<ASTNode> statementList;

	/*
	* Invokes the WhileExtractor to extract the while statement
	*/
	void handleWhileExtraction(std::shared_ptr<ASTNode> root);

	/*
	* Invokes the ExpressionVisitor to visit the expression
	*/
	void handleExpressionVisitor();

	/*
	* Invokes the StatementListVisitor to visit the statement list
	*/
	void handleStatementListVisitor(std::shared_ptr<ASTNode> statementList);
};