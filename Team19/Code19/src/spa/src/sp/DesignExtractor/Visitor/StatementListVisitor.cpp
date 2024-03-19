#include "sp/DesignExtractor/Visitor/StatementListVisitor.h"

StatementListVisitor::StatementListVisitor(std::shared_ptr<ASTNode> root,
	std::shared_ptr<PKBWriterManager> pkbWriterManager)
	: IVisitor(root, pkbWriterManager) {
	if (!ASTUtility::nodeIsStatementList(root->getType())) {
		throw std::invalid_argument("ERROR: StatementListVisitor - input root is not of NodeType::STATEMENT_LIST");
	}
	this->statementLists = root->getChildren();
}


// Logic: for each statement, create the visitor and set context to the parent nodes
// end goal: the statement visitor should contain the previous contexts - does not need the stmtLst
void StatementListVisitor::visit() {
	StatementFactory statementFactory;
	
	for (auto statement : statementLists) {
		std::shared_ptr<StatementVisitor> statementVisitor = statementFactory.createVisitor(statement, this->contexts, this->pkbWriterManager);
		statementVisitor->visit();
		statementVisitor->setParents(this->contexts, statement, this->pkbWriterManager);
		handleStatementExtraction(statement);
		// setParents(this->contexts, this->root, this->pkbWriterManager);
	}

	handleAllFollows();
}

void StatementListVisitor::setContext(std::vector<std::shared_ptr<ASTNode>> contexts, std::shared_ptr<ASTNode> parent) {
	this->contexts = std::vector<std::shared_ptr<ASTNode>>(contexts.begin(), contexts.end());
	this->contexts.push_back(parent);
}


// extract follows and follows* relationship
// this can only be done on the StatementList visitor
// current time complexity is O(n^2), due to the nested for loop
// in milestone 3 we try to optimize this to at least O(nlogn)
void StatementListVisitor::handleAllFollows() {
	int size = statementLists.size();

	for (int i = 0; i < size - 1; i++) {
		std::shared_ptr<ASTNode> ast1 = root->getChildByIndex(i);
		std::shared_ptr<ASTNode> ast2 = root->getChildByIndex(i + 1);
		handleFollowsS(ast1, ast2);

		for (int j = i + 1; j < size; j++) {
			std::shared_ptr<ASTNode> ast3 = root->getChildByIndex(j);
			handleFollowsT(ast1, ast3);
		}
	}
}

void StatementListVisitor::handleStatementExtraction(std::shared_ptr<ASTNode> statement) {
	StatementExtractor statementExtractor(statement, this->pkbWriterManager->getStatementWriter());
	statementExtractor.extract();
}

void StatementListVisitor::handleFollowsS(std::shared_ptr<ASTNode> ast1, std::shared_ptr<ASTNode> ast2) {
	FollowsExtractor followsExtractor(ast1, ast2, this->pkbWriterManager->getFollowsWriter());
	followsExtractor.extract();
}

void StatementListVisitor::handleFollowsT(std::shared_ptr<ASTNode> ast1, std::shared_ptr<ASTNode> ast2) {
	FollowsTExtractor followsExtractor(ast1, ast2, this->pkbWriterManager->getFollowsTWriter());
	followsExtractor.extract();
}