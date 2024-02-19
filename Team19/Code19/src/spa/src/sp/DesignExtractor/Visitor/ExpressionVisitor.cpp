#include "sp/DesignExtractor/Visitor/ExpressionVisitor.h"

ExpressionVisitor::ExpressionVisitor(std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriterManager> pkbWriterManager)
	: IVisitor(root, pkbWriterManager) {
	
}

void ExpressionVisitor::visit() {

}

void ExpressionVisitor::visit(std::shared_ptr<ASTNode> node) {
	
}