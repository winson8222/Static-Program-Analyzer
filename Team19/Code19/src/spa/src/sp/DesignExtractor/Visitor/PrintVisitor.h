#pragma once

#include "sp/DesignExtractor/Visitor/IVisitor.h"
#include "sp/DesignExtractor/Visitor/VariableVisitor.h"

#include "sp/DesignExtractor/Extractor/EntityExtractor/PrintExtractor.h"
#include "sp/DesignExtractor/Extractor/RelationshipExtractor/ParentExtractor.h"


constexpr int PRINT_VARIABLE_INDEX = 0;
/*
* A visitor for the while statement which should
* call on all relevant extractors and sub-visitors
*
* This class is inherited from the IVisitor class,
* so additional documentation should be taken from the
* base abstract class unless further specified
*/
class PrintVisitor : public StatementVisitor {
public:
	PrintVisitor(std::shared_ptr<ASTNode> root, 
		listnode context,
		std::shared_ptr<PKBWriterManager> pkbWriterManager);

	void visit() override;

private:
	std::shared_ptr<ASTNode> childVariable;
};