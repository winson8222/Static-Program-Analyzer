#pragma once

#include "sp/DesignExtractor/Extractor/IExtractor.h"
#include <stdexcept>

/*
* VariableExtractor is responsible for extracting variable information from the AST
* This class is a subclass of IExtractor and implements the extract method from it.
* Documentation for the methods can be found in the IExtractor class.
*/
class VariableExtractor : public IExtractor {
public:
	explicit VariableExtractor(std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriterManager> pkbWriterManager)
		: IExtractor(root, pkbWriterManager) {
		if (root->type != ASTNodeType::VARIABLE) {
			throw std::invalid_argument("VariableExtractor: root is not of type VARIABLE");
		}
	}

	void extract() override;
};