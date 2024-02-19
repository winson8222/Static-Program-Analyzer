#include "sp/DesignExtractor/Visitor/StatementListVisitor.h"

void StatementListVisitor::visit(std::shared_ptr<ASTNode> node) {
	// do nothing
}

void StatementListVisitor::visit() {

	std::cout << "REACHED STATEMENT LIST" << std::endl;
	auto statementLists = this->root->children;
	for (auto statement : statementLists) {
		if (!Utility::nodeIsStatement(statement->type)) {
			throw std::runtime_error("Not a statement!");
		}

		if (statement->type == ASTNodeType::ASSIGN) {
			AssignVisitor assignVisitor(statement, this->pkbWriterManager);
			assignVisitor.visit();
		}
		else if (statement->type == ASTNodeType::PRINT) {
			PrintVisitor printVisitor(statement, this->pkbWriterManager);
			printVisitor.visit();
		}
		else if (statement->type == ASTNodeType::READ) {
			ReadVisitor readVisitor(statement, this->pkbWriterManager);
			readVisitor.visit();
		}
		else if (statement->type == ASTNodeType::CALL) {
			CallVisitor callVisitor(statement, this->pkbWriterManager);
			callVisitor.visit();
		}
		else if (statement->type == ASTNodeType::IF_ELSE_THEN) {
			IfElseThenVisitor ifElseThenVisitor(statement, this->pkbWriterManager);
			ifElseThenVisitor.visit();
		}
		else if (statement->type == ASTNodeType::WHILE) {
			WhileVisitor whileVisitor(statement, this->pkbWriterManager);
			whileVisitor.visit();
		}
		else {
			throw std::runtime_error("Unknown statement type!");
		}
	}
}