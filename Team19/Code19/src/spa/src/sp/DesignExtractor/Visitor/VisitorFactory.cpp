#include <memory>
#include "sp/DesignExtractor/Visitor/VisitoryFactory.h"

std::shared_ptr<StatementVisitor> StatementFactory::createVisitor(std::shared_ptr<ASTNode> node, 
		listnode parent,
		std::shared_ptr<PKBWriterManager> pkbWriterManager) {
	switch (node->type) {
		case ASTNodeType::ASSIGN:
			return std::make_shared<AssignVisitor>(node, parent, pkbWriterManager);
		case ASTNodeType::READ:
			return std::make_shared<ReadVisitor>(node, parent, pkbWriterManager);
		case ASTNodeType::PRINT:
			return std::make_shared<PrintVisitor>(node, parent, pkbWriterManager);
		case ASTNodeType::CALL:
			return std::make_shared<CallVisitor>(node, parent, pkbWriterManager);
		case ASTNodeType::WHILE:
			return std::make_shared<WhileVisitor>(node, parent, pkbWriterManager);
		case ASTNodeType::IF_ELSE_THEN:
			return std::make_shared<IfElseThenVisitor>(node, parent, pkbWriterManager);
		default:
			throw std::invalid_argument("ERROR: Not a statement!");
	}
}

std::shared_ptr<IVisitor> ExpressionFactory::createVisitor(std::shared_ptr<ASTNode> node, std::shared_ptr<PKBWriterManager> pkbWriterManager) {
	switch (node->type) {
		default:
			throw std::invalid_argument("ExpressionFactory - node type not supported");
	}
}