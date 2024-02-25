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
	explicit AssignExtractor(std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriterManager> pkbWriterManager)
		: IExtractor(root, pkbWriterManager) {
		if (root->children.size() != 2 || root->type != ASTNodeType::ASSIGN) {
			throw std::runtime_error("ERROR: AssignExtractor root node type not supported");
		}
	}

	void extract() override;
};