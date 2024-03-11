#include "sp/DesignExtractor/Extractor/ProcedureExtractor.h"

ProcedureExtractor::ProcedureExtractor(std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriterManager> pkbWriterManager)
	: IExtractor(root, pkbWriterManager) {
	if (root->type != ASTNodeType::PROCEDURE) {
		// std::cout << "ProcedureExtractor::ProcedureExtractor: root is not of type PROCEDURE" << std::endl;
	}
}

void ProcedureExtractor::extract() {
	// Insert procedures into PKB
	this->pkbWriterManager->getProcedureWriter()->insertProcedure(root->value);
}