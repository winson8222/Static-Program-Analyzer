#pragma once

#include <stdexcept>
#include "sp/DesignExtractor/Extractor/EntityExtractor/IEntityExtractor.h"

/*
* Extracts a general statement from the AST and writes the information to the PKB.
* This class implements the IExtractor interface. The methods are documented
* from the base class at IExtractor.h
*/
class StatementExtractor : public IEntityExtractor {
public:
	StatementExtractor(std::shared_ptr<ASTNode> root, std::shared_ptr<StatementWriter> statementWriter);

	void extract() override;

private:
	std::shared_ptr<StatementWriter> statementWriter;
};
