#pragma once

#include "sp/DesignExtractor/Visitor/IVisitor.h"
#include "sp/AST/ASTNode.h"
#include "pkb/PKBWriterManager.h"
#include "sp/DesignExtractor/Extractor/ProcedureExtractor.h"
#include "sp/DesignExtractor/Visitor/StatementListVisitor.h"


/*
* A visitor for the procedure node which should
* call on all relevant extractors and sub-visitors
*
* This class is inherited from the IVisitor class,
* so additional documentation should be taken from the
* base abstract class unless further specified
*/
class ProcedureVisitor : public IVisitor {
public:
	ProcedureVisitor(std::shared_ptr<ASTNode> node, std::shared_ptr<PKBWriterManager> pkbWriterManager);
	void visit() override;
	void setIsVisited();
	bool checkIfVisited();

private:
	bool wasVisited;
};