#include <memory>
#include "sp/DesignExtractor/Visitor/VisitoryFactory.h"

std::shared_ptr<StatementVisitor> StatementFactory::createVisitor(std::shared_ptr<ASTNode> node, std::shared_ptr<PKBWriterManager> pkbWriterManager) {
	switch (node->type) {
		case ASTNodeType::ASSIGN:
			return std::make_shared<AssignVisitor>(node, pkbWriterManager);
		case ASTNodeType::READ:
			return std::make_shared<ReadVisitor>(node, pkbWriterManager);
		case ASTNodeType::PRINT:
			return std::make_shared<PrintVisitor>(node, pkbWriterManager);
		case ASTNodeType::CALL:
			return std::make_shared<CallVisitor>(node, pkbWriterManager);
		case ASTNodeType::WHILE:
			return std::make_shared<WhileVisitor>(node, pkbWriterManager);
		case ASTNodeType::IF_ELSE_THEN:
			return std::make_shared<IfElseThenVisitor>(node, pkbWriterManager);
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