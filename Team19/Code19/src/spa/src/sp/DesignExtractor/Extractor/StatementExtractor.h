#pragma once

#include "sp/DesignExtractor/Extractor/IExtractor.h"

/*
* Extracts a general statement from the AST and writes the information to the PKB.
* This class implements the IExtractor interface. The methods are documented
* from the base class at IExtractor.h
*/
class StatementExtractor : public IExtractor {
public:
	StatementExtractor(std::shared_ptr<ASTNode> root, std::shared_ptr<StatementWriter> statementWriter);

	void extract() override;

private:
	std::shared_ptr<StatementWriter> statementWriter;
};