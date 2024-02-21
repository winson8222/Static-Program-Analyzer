#pragma once

#include "sp/DesignExtractor/Extractor/IExtractor.h"
#include <stdexcept>
#include <iostream>

class ModifiesExtractor : public IRelationshipExtractor {
public:
	ModifiesExtractor(std::shared_ptr<ASTNode> ast1,
		std::shared_ptr<ASTNode> ast2,
		std::shared_ptr<PKBWriterManager> pkbWriterManager)
		: IRelationshipExtractor(ast1, ast2, pkbWriterManager) {}

	void extract() override;

private:
	void getAssignModifies();
	void getReadModifies();
	void getIfModifies();
	void getWhileModifies();
	void getProcedureModifies();
	void getCallModifies();
};