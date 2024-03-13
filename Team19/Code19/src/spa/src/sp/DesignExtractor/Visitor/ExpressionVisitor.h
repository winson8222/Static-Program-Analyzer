#pragma once

#include "sp/DesignExtractor/Visitor/IVisitor.h"
#include "sp/DesignExtractor/Visitor/VariableVisitor.h"
#include "sp/DesignExtractor/Extractor/EntityExtractor/VariableExtractor.h"
#include "sp/DesignExtractor/Extractor/EntityExtractor/ConstantExtractor.h"
#include "sp/DesignExtractor/Extractor/PatternExtractor/IfsPatternExtractor.h"
#include "sp/DesignExtractor/Extractor/PatternExtractor/WhilePatternExtractor.h"
#include "sp/AST/ASTUtility.h"
#include <stdexcept>

constexpr int EXPR_LHS_INDEX = 0;
constexpr int EXPR_RHS_INDEX = 1;

/*
* A visitor for the valid expression statement which should
* call on all relevant extractors and sub-visitors. It should group
* all those that are on right hand side of assignment or conditions
* for while/if statements together.
*
* This class is inherited from the IVisitor class,
* so additional documentation should be taken from the
* base abstract class unless further specified
*/
class ExpressionVisitor : public IVisitor {
public:
	ExpressionVisitor(std::shared_ptr<ASTNode> root, ASTNodeType caller, std::shared_ptr<PKBWriterManager> pkbWriterManager);
	void visit() override;

	/*
	* A method to recursively call the visitor on the AST,
	* knowing that the root is an expression statement and that
	* all nodes are valid expressions
	*/
	void depthFirstSearch(std::shared_ptr<ASTNode> node);

	/*
	* A method to get the used contexts of the expression for
	* later call of used context in the PKB
	*/
	void setUsedContext(listnode contexts, std::shared_ptr<ASTNode> parent);

private:
	/*
	* A vector to get the used contexts of the expression for
	*/ 
	listnode usedContexts;

	/*
	* The caller type of the expression
	*/
	ASTNodeType caller;

	/*
	* A method to handle the pattern extraction of the expression
	* Works if the caller is either while or if statement, and do nothing otherwise
	*/
	void handlePatternExtraction(std::shared_ptr<ASTNode> variableNode);

	/*
	* A method to handle the variable visitor of the expression
	*/
	void handleVariableVisitor(std::shared_ptr<ASTNode> variableNode);

	/*
	* A method to handle the constant extraction of the expression
	*/
	void handleConstantExt(std::shared_ptr<ASTNode> constantNode);
};

// This class is prototype for future design considerations
class ArithmeticExpressionVisitor : public ExpressionVisitor {
public:
	using ExpressionVisitor::ExpressionVisitor;
	void depthFirstSearch(std::shared_ptr<ASTNode> node);
};