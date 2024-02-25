#include "sp/DesignExtractor/Visitor/StatementListVisitor.h"

StatementListVisitor::StatementListVisitor(std::shared_ptr<ASTNode> root,
	std::shared_ptr<PKBWriterManager> pkbWriterManager)
	: IVisitor(root, pkbWriterManager) {
	if (!ASTUtility::nodeIsStatementList(root->type)) {
		throw std::invalid_argument("ERROR: StatementListVisitor - input root is not of NodeType::STATEMENT_LIST");
	}
}

void StatementListVisitor::visit() {
	auto statementLists = this->root->children;
	StatementFactory statementFactory;

	// Logic: for each statement, create the visitor and set context to the parent nodes
	// end goal: the statement visitor should contain the previous contexts - does not need the stmtLst
	for (auto statement : statementLists) {
		std::shared_ptr<StatementVisitor> statementVisitor = 
			statementFactory.createVisitor(statement, this->contexts, this->pkbWriterManager);
		statementVisitor->visit();
	}

	// extract follows and follows* relationship
	// this can only be done on the StatementList visitor
	// current time complexity is O(n^2), due to the nested for loop
	// in milestone 3 we try to optimize this to at least O(nlogn)
	int size = statementLists.size();
	for (int i = 0; i < size - 1; i++) {
		std::shared_ptr<ASTNode> ast1 = statementLists[i];
		std::shared_ptr<ASTNode> ast2 = statementLists[i + 1];

		FollowsExtractor followsExtractor(ast1, ast2, this->pkbWriterManager);
		followsExtractor.extract();

		for (int j = i + 1; j < size; j++) {
			std::shared_ptr<ASTNode> ast3 = statementLists[j];
			FollowsTExtractor followsExtractor(ast1, ast3, this->pkbWriterManager);
			followsExtractor.extract();
		}
	}
}

void StatementListVisitor::setContext(std::vector<std::shared_ptr<ASTNode>> contexts, std::shared_ptr<ASTNode> parent) {
	this->contexts = std::vector<std::shared_ptr<ASTNode>>(contexts.begin(), contexts.end());
	this->contexts.push_back(parent);
}