#include "sp/DesignExtractor/Extractor/VariableExtractor.h"

VariableExtractor::VariableExtractor(std::shared_ptr<ASTNode> root, std::shared_ptr<VariableWriter> variableWriter)
	: IExtractor(root) {
	if (!root->equalType(ASTNodeType::VARIABLE)) {
		throw std::invalid_argument("VariableExtractor: root is not of type VARIABLE");
	}
	this->variableWriter = variableWriter;
}

void VariableExtractor::extract() {
	// Extract all variables to the PKB
	this->variableWriter->addEntity(this->root->getValue());
}