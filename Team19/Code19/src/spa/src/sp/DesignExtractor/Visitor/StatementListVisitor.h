#pragma once

#include <stdexcept>
#include <vector>
#include "sp/DesignExtractor/Visitor/IVisitor.h"
#include "sp/DesignExtractor/Visitor/VisitoryFactory.h"
#include "sp/DesignExtractor/Extractor/RelationshipExtractor/FollowsExtractor.h"
#include "sp/DesignExtractor/Extractor/EntityExtractor/StatementExtractor.h"
#include "sp/AST/ASTUtility.h"

/*
* A visitor for the statement list which should
* call on all relevant extractors and sub-visitors
*
* This class is inherited from the IVisitor class,
* so additional documentation should be taken from the
* base abstract class unless further specified
*/
class StatementListVisitor : public IVisitor {
public:
	StatementListVisitor(std::shared_ptr<ASTNode> root,
		std::shared_ptr<PKBWriterManager> pkbWriterManager);

	void visit() override;

	/*
	* This method is used to set the context of all children nodes (which are under statement lists)
	* to the node that invoke this StatementListVisitor.
	*/
	void setContext(std::vector<std::shared_ptr<ASTNode>> contexts, std::shared_ptr<ASTNode> parent);

	std::vector<std::shared_ptr<ASTNode>> contexts;

private:
	std::vector<std::shared_ptr<ASTNode>> statementLists;
	void handleAllFollows();
	void handleStatementExtraction(std::shared_ptr<ASTNode> statement);
	void handleFollowsS(std::shared_ptr<ASTNode> ast1, std::shared_ptr<ASTNode> ast2);
	void handleFollowsT(std::shared_ptr<ASTNode> ast1, std::shared_ptr<ASTNode> ast2);
};