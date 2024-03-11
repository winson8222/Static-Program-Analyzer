#include "sp/DesignExtractor/Visitor/StatementListVisitor.h"

StatementListVisitor::StatementListVisitor(std::shared_ptr<ASTNode> root,
	std::shared_ptr<PKBWriterManager> pkbWriterManager)
	: IVisitor(root, pkbWriterManager) {
	if (!ASTUtility::nodeIsStatementList(root->type)) {
		throw std::invalid_argument("ERROR: StatementListVisitor - input root is not of NodeType::STATEMENT_LIST");
	}
}

void StatementListVisitor::visit() {
	std::vector<std::shared_ptr<ASTNode>> statementLists = this->root->getChildren();
	StatementFactory statementFactory;

	// Logic: for each statement, create the visitor and set context to the parent nodes
	// end goal: the statement visitor should contain the previous contexts - does not need the stmtLst
	for (auto statement : statementLists) {
		std::shared_ptr<StatementVisitor> statementVisitor = 
			statementFactory.createVisitor(statement, this->contexts, this->pkbWriterManager);
		statementVisitor->visit();
		StatementExtractor statementExtractor(statement, this->pkbWriterManager->getStatementWriter());
		statementExtractor.extract();
	}

	handleFollows();
}

void StatementListVisitor::setContext(std::vector<std::shared_ptr<ASTNode>> contexts, std::shared_ptr<ASTNode> parent) {
	this->contexts = std::vector<std::shared_ptr<ASTNode>>(contexts.begin(), contexts.end());
	this->contexts.push_back(parent);
}


// extract follows and follows* relationship
// this can only be done on the StatementList visitor
// current time complexity is O(n^2), due to the nested for loop
// in milestone 3 we try to optimize this to at least O(nlogn)

void StatementListVisitor::handleFollows() {
	std::vector<std::shared_ptr<ASTNode>> statementLists = this->root->getChildren();
	int size = statementLists.size();

	for (int i = 0; i < size - 1; i++) {
		std::shared_ptr<ASTNode> ast1 = root->getChildByIndex(i);
		std::shared_ptr<ASTNode> ast2 = root->getChildByIndex(i + 1);

		FollowsExtractor followsExtractor(ast1, ast2, this->pkbWriterManager->getFollowsWriter());
		followsExtractor.extract();

		for (int j = i + 1; j < size; j++) {
			std::shared_ptr<ASTNode> ast3 = root->getChildByIndex(j);
			FollowsTExtractor followsExtractor(ast1, ast3, this->pkbWriterManager->getFollowsTWriter());
			followsExtractor.extract();
		}
	}
}