#include "sp/DesignExtractor/Extractor/ProcedureExtractor.h"

ProcedureExtractor::ProcedureExtractor(std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriterManager> pkbWriterManager)
	: IExtractor(root, pkbWriterManager) {
	if (root->type != ASTNodeType::PROCEDURE) {
		throw std::runtime_error("ProcedureExtractor::ProcedureExtractor: root is not of type PROCEDURE");
	}
}

void ProcedureExtractor::extract() {
	// Insert procedures into PKB
	this->pkbWriterManager->getProcedureWriter()->insertProcedure(root->value);
}