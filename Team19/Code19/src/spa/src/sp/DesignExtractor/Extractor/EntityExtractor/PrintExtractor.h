#pragma once

#include <stdexcept>
#include "sp/DesignExtractor/Extractor/EntityExtractor/IEntityExtractor.h"

/*
* Extracts the print statement from the AST and writes the information to the PKB.
* This class implements the IExtractor interface. The methods are documented
* from the base class at IExtractor.h
*/
class PrintExtractor : public IEntityExtractor {
public:
	PrintExtractor(std::shared_ptr<ASTNode> root, std::shared_ptr<PrintWriter> printWriter);

	void extract() override;

private:
	std::shared_ptr<PrintWriter> printWriter;
};
