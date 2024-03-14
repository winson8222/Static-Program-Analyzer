#pragma once

#include "sp/DesignExtractor/Visitor/IVisitor.h"
#include "sp/AST/ASTNode.h"
#include "pkb/PKBWriterManager.h"
#include "sp/DesignExtractor/Extractor/EntityExtractor/ProcedureExtractor.h"
#include "sp/DesignExtractor/Visitor/StatementListVisitor.h"
#include "sp/DesignExtractor/Visitor/CFGVIsitor.h"
#include "sp/ControlFlow/SimpleControlFlow.h"

constexpr int PROCEDURE_STATEMENT_LIST_INDEX = 0;

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

	/*
	* A method to set the procedure node to status visited
	*/
	void setIsVisited();

	/*
	* A method to check if the procedure node has been visited
	*/
	bool checkIfVisited();

	/*
	* A method to add all contexts relevant before the procedure is called
	* @param contexts a vector of shared pointers to ASTNode
	*/
	void addContexts(std::vector<std::shared_ptr<ASTNode>> contexts);

private:
	std::shared_ptr<ASTNode> statementListNode;
	bool wasVisited;

	/*
	* A method to handle the extraction of the procedure
	*/
	void handleProcedureExtractor();

	/*
	* A method to handle the visiting of the statement list node
	*/
	void handleStatementListVisitor();

	/*
	* A method to generate control flow graph for the procedure
	*/
	void handleControlFlowGraph();
};