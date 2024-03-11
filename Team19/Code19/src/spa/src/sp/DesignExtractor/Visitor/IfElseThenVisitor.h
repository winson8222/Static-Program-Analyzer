#pragma once

#include "sp/DesignExtractor/Extractor/IfElseThenExtractor.h"
#include "sp/DesignExtractor/Visitor/IVisitor.h"
#include "sp/DesignExtractor/Visitor/ExpressionVisitor.h"
#include "sp/DesignExtractor/Visitor/StatementListVisitor.h"
#include "sp/DesignExtractor/Extractor/ParentExtractor.h"
#include <stdexcept>


/*
* A visitor for the if-then-else statement which should
* call on all relevant extractors and sub-visitors
*
* This class is inherited from the IVisitor class,
* so additional documentation should be taken from the
* base abstract class unless further specified
*/
class IfElseThenVisitor : public StatementVisitor {
public:
	IfElseThenVisitor(std::shared_ptr<ASTNode> root, 
		listnode context,
		std::shared_ptr<PKBWriterManager> pkbWriterManager);
	void visit() override;
	void addContext(std::shared_ptr<ASTNode> context) override;
};