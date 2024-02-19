#pragma once

#include <memory>
#include "sp/AST/ASTNode.h"
#include "pkb/PKBWriterManager.h"


class IExtractor {
public:
    explicit IExtractor(std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriterManager> pkbWriterManager)
		: root(root), pkbWriterManager(pkbWriterManager) {}

	virtual void extract() = 0;

	std::shared_ptr<ASTNode> root;
	std::shared_ptr<PKBWriterManager> pkbWriterManager;
};