#pragma once

#include "sp/DesignExtractor/Extractor/EntityExtractor/IEntityExtractor.h"
#include <stdexcept>

/*
* VariableExtractor is responsible for extracting variable information from the AST
* This class is a subclass of IExtractor and implements the extract method from it.
* Documentation for the methods can be found in the IExtractor class.
*/
class VariableExtractor : public IEntityExtractor {
public:
	VariableExtractor(std::shared_ptr<ASTNode> root, std::shared_ptr<VariableWriter> variableWriter);

	void extract() override;

private:
	std::shared_ptr<VariableWriter> variableWriter;
};