#pragma once

#include "sp/DesignExtractor/Extractor/IExtractor.h"

/*
* Extracts the if-then-else statement from the AST and writes the information to the PKB.
* This class implements the IExtractor interface. The methods are documented
* from the base class at IExtractor.h
*/
class IfThenElseExtractor : public IExtractor {
public:
	IfThenElseExtractor(std::shared_ptr<ASTNode> root, std::shared_ptr<IfWriter> ifWriter);

	void extract() override;

private:
	std::shared_ptr<IfWriter> ifWriter;
};