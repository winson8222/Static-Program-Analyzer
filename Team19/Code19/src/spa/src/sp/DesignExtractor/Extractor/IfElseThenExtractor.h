#pragma once

#include "sp/DesignExtractor/Extractor/IExtractor.h"

/*
* Extracts the if-then-else statement from the AST and writes the information to the PKB.
* This class implements the IExtractor interface. The methods are documented
* from the base class at IExtractor.h
*/
class IfThenElseExtractor : public IExtractor {
public:
	explicit IfThenElseExtractor(std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriterManager> pkbWriterManager)
		: IExtractor(root, pkbWriterManager) {}

	void extract() override;
};