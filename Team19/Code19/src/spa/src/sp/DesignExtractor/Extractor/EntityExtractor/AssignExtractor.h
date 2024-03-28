#pragma once

#include <stdexcept>
#include "sp/DesignExtractor/Extractor/EntityExtractor/IEntityExtractor.h"

/*
* Extracts the assignment statement from the AST and writes the information to the PKB.
* This class implements the IExtractor interface. The methods are documented
* from the base class at IExtractor.h
*/
class AssignExtractor : public IEntityExtractor {
public:
	AssignExtractor(std::shared_ptr<ASTNode> root, std::shared_ptr<AssignWriter> assignWriter);

	void extract() override;
private:
	std::shared_ptr<AssignWriter> assignWriter;
};
