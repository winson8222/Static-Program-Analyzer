#include "sp/DesignExtractor/Visitor/PrintVisitor.h"

PrintVisitor::PrintVisitor(std::shared_ptr<ASTNode> root,
	listnode context,
	std::shared_ptr<PKBWriterManager> pkbWriterManager)
	: StatementVisitor(root, context, pkbWriterManager) {
	if (!root->equalType(ASTNodeType::PRINT)) {
		throw std::invalid_argument("PrintVisitor - root is not of type PRINT");
	}

	auto children = root->getChildren();
	if (children.size() != 1) {
		throw std::invalid_argument("PrintVisitor - root does not have 1 child");
	}
	this->contexts = listnode(context.begin(), context.end());
	this->childVariable = root->getChildByIndex(PRINT_VARIABLE_INDEX);
}


void PrintVisitor::visit() {
	PrintExtractor printExtractor(this->root, this->pkbWriterManager->getPrintWriter());
	printExtractor.extract();

	PrintVarExtractor printVarExtractor(this->pkbWriterManager->getPrintVarNameWriter());
	printVarExtractor.extract(this->root, this->childVariable);

	VariableVisitor variableVisitor(childVariable, this->pkbWriterManager);
	variableVisitor.setUsedContext(contexts, root);
	variableVisitor.visit();
}
