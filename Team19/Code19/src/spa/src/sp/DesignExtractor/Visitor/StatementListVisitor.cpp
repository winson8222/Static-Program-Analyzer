#include "sp/DesignExtractor/Visitor/StatementListVisitor.h"


void StatementListVisitor::visit() {
	auto statementLists = this->root->children;
	StatementFactory statementFactory;

	for (auto statement : statementLists) {
		std::shared_ptr<StatementVisitor> statementVisitor = statementFactory.createVisitor(statement, this->pkbWriterManager);
		statementVisitor->visit();
	}
}