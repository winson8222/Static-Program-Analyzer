#pragma once

#include "sp/DesignExtractor/Extractor/IExtractor.h"
#include <stdexcept>

class ConstantExtractor : public IExtractor {
public:
	explicit ConstantExtractor(std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriterManager> pkbWriterManager)
		: IExtractor(root, pkbWriterManager) {
		if (root->type != ASTNodeType::CONSTANT) {
			throw std::invalid_argument("VariableExtractor: root is not of type VARIABLE");
		}
	}

	void extract() override;
};