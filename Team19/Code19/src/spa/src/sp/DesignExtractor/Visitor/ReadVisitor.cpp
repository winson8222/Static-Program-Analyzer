#include "sp/DesignExtractor/Visitor/ReadVisitor.h"

void ReadVisitor::visit(std::shared_ptr<ASTNode> node) {
	// std::string readVar = node.getReadVar();
	// pkbWriterManager->insertReadStmt(node.getStatementNumber(), readVar);
}

void ReadVisitor::visit() {
	std::cout << "ReadVisitor" << std::endl;
	// TODO
	ReadExtractor readExtractor(this->root, this->pkbWriterManager);
	readExtractor.extract();

	VariableExtractor variableExtractor(this->root->children[0], this->pkbWriterManager);
	variableExtractor.extract();
}

/*
#include "sp/DesignExtractor/Visitor/PrintVisitor.h"

void PrintVisitor::visit(std::shared_ptr<ASTNode> node) {
	// do nothing for now
}

void PrintVisitor::visit() {
	// TODO
	if (this->root->type != ASTNodeType::PRINT) {
		throw std::runtime_error("This is not a print node!");
	}
	// I'm here in the Print Visitor - now my purpose is
	// to populate print statements and the variable (and the uses relationships)

	PrintExtractor printExtractor(this->root, this->pkbWriterManager);
	printExtractor.extract();

	VariableExtractor variableExtractor(this->root->children[0], this->pkbWriterManager);
	variableExtractor.extract();
}
*/