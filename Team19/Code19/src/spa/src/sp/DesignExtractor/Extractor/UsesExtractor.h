#pragma once

#include "sp/DesignExtractor/Extractor/IExtractor.h"
#include <stdexcept>

class UsesExtractor : public IRelationshipExtractor {
public:
	UsesExtractor(std::shared_ptr<ASTNode> ast1,
		std::shared_ptr<ASTNode> ast2,
		std::shared_ptr<PKBWriterManager> pkbWriterManager)
		: IRelationshipExtractor(ast1, ast2, pkbWriterManager) {}

	void extract() override;

private:
	void getAssignUses();
	void getPrintUses();
	void getIfUses();
	void getWhileUses();
	void getProcedureUses();
	void getCallUses();
};