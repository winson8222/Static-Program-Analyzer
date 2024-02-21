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

class IRelationshipExtractor {
public:
	explicit IRelationshipExtractor(std::shared_ptr<ASTNode> ast1,
		std::shared_ptr<ASTNode> ast2,
		std::shared_ptr<PKBWriterManager> pkbWriterManager)
		: ast1(ast1), ast2(ast2), pkbWriterManager(pkbWriterManager) {}

	virtual void extract() = 0;

	std::shared_ptr<ASTNode> ast1;
	std::shared_ptr<ASTNode> ast2;
	std::shared_ptr<PKBWriterManager> pkbWriterManager;
};