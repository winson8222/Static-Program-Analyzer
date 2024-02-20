#include "sp/DesignExtractor/Visitor/StatementListVisitor.h"


void StatementListVisitor::visit() {
	auto statementLists = this->root->children;
	StatementFactory statementFactory;

	for (auto statement : statementLists) {
		std::shared_ptr<StatementVisitor> statementVisitor = statementFactory.createVisitor(statement, this->pkbWriterManager);
		statementVisitor->visit();
	}

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