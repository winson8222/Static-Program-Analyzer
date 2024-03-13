#pragma once

#include "sp/DesignExtractor/Visitor/IVisitor.h"
#include "sp/DesignExtractor/Visitor/VariableVisitor.h"
#include "sp/DesignExtractor/Extractor/EntityExtractor/AssignExtractor.h"
#include "sp/DesignExtractor/Extractor/PatternExtractor/AssignPatternExtractor.h"
#include "sp/DesignExtractor/Extractor/EntityExtractor/VariableExtractor.h"
#include "sp/DesignExtractor/Extractor/RelationshipExtractor/ParentExtractor.h"
#include "sp/DesignExtractor/Visitor/ExpressionVisitor.h"
#include <stdexcept>

// ai-gen start (gpt, 2, e)
// prompt: https://platform.openai.com/playground/p/WEPuYktjSFWSXYtIjbHMb5KZ?model=gpt-4&mode=chat

constexpr int ASSIGN_LHS = 0;
constexpr int ASSIGN_RHS = 1;

/*
* A visitor for the assign statement which should
* call on all relevant extractors and sub-visitors
*
* This class is inherited from the IVisitor class,
* so additional documentation should be taken from the
* base abstract class unless further specified
*/
class AssignVisitor : public StatementVisitor {
public:
	AssignVisitor(std::shared_ptr<ASTNode> root, listnode context, std::shared_ptr<PKBWriterManager> pkbWriterManager);

	void visit() override;

private:
	std::shared_ptr<ASTNode> lhsExpr;
	std::shared_ptr<ASTNode> rhsExpr;

	/*
	* Handle invoking the assign extractor
	*/
	void handleAssignExtraction(std::shared_ptr<ASTNode> node);

	/*
	* Handle invoking the variable modifies extractor
	*/
	void handleLHSExtraction(std::shared_ptr<ASTNode> node);

	/*
	* Handle invoking the expression used extractor
	*/
	void handleRHSExtraction(std::shared_ptr<ASTNode> node);

	/*
	* Handle invoking the pattern extractor
	*/
	void handleAssignPatternExtraction(std::shared_ptr<ASTNode> ast1, std::shared_ptr<ASTNode> ast2, std::shared_ptr<ASTNode> ast3);
};

// ai-gen end