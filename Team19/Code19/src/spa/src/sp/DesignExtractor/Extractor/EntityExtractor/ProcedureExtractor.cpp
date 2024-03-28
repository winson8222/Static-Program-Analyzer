#include "sp/DesignExtractor/Extractor/EntityExtractor/ProcedureExtractor.h"
#include "sp/AST/ASTUtility.h"

ProcedureExtractor::ProcedureExtractor(std::shared_ptr<ASTNode> root, std::shared_ptr<ProcedureWriter> procedureWriter)
	: IEntityExtractor(root) {
	if (!root->equalType(ASTNodeType::PROCEDURE)) {
		throw std::runtime_error("ProcedureExtractor::ProcedureExtractor: root is not of type PROCEDURE");
	}
	this->procedureWriter = procedureWriter;
}

void ProcedureExtractor::extract() {
	// Insert procedures into PKB
	this->procedureWriter->insertProcedure(root->getValue());
}
