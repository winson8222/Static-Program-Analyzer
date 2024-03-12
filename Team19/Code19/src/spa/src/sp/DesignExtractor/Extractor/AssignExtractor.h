#pragma once

#include "sp/DesignExtractor/Extractor/IExtractor.h"
#include <stdexcept>

/*
* Extracts the assignment statement from the AST and writes the information to the PKB.
* This class implements the IExtractor interface. The methods are documented
* from the base class at IExtractor.h
*/
class AssignExtractor : public IExtractor {
public:
	AssignExtractor(std::shared_ptr<ASTNode> root, std::shared_ptr<AssignWriter> assignWriter);

	void extract() override;
private:
	std::shared_ptr<AssignWriter> assignWriter;
};