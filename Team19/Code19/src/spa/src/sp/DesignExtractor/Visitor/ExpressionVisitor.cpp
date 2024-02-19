#include "sp/DesignExtractor/Visitor/ExpressionVisitor.h"

ExpressionVisitor::ExpressionVisitor(std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriterManager> pkbWriterManager)
	: IVisitor(root, pkbWriterManager) {
	
}

ExpressionVisitor::visit() {

}

ExpressionVisitor::visit(std::shared_ptr<ASTNode> node) {
	
}