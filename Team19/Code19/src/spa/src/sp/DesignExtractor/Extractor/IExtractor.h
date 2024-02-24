#pragma once

#include <memory>
#include "sp/AST/ASTNode.h"
#include "pkb/PKBWriterManager.h"

/*
* IExtractor is an interface for all extractors (specifically for entities)
* It is used to extract entity designs from the AST and store it in the PKB
*/
class IExtractor {
public:
	/*
	* Constructor for IExtractor, takes in the root of the AST and the PKBWriterManager
	*/
    explicit IExtractor(std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriterManager> pkbWriterManager)
		: root(root), pkbWriterManager(pkbWriterManager) {}
	
	/*
	* Extracts information from the AST and stores it in the PKB by calling
	* the respective PKB writer manager methods
	*/
	virtual void extract() = 0;

	std::shared_ptr<ASTNode> root;
	std::shared_ptr<PKBWriterManager> pkbWriterManager;
};

/*
* IRelationshipExtractor is an interface for all relationship extractors, specifically
* for traversal to expressions instead
* It is used to extract relationships from the AST and store it in the PKB
*/
class IRelationshipExtractor {
public:
	explicit IRelationshipExtractor(std::shared_ptr<ASTNode> ast1,
		std::shared_ptr<ASTNode> ast2,
		std::shared_ptr<PKBWriterManager> pkbWriterManager)
		: ast1(ast1), ast2(ast2), pkbWriterManager(pkbWriterManager) {}

	/*
	* Extracts relationships from the AST and stores it in the PKB by calling
	* the respective PKB writer manager methods
	*/
	virtual void extract() = 0;

	std::shared_ptr<ASTNode> ast1;
	std::shared_ptr<ASTNode> ast2;
	std::shared_ptr<PKBWriterManager> pkbWriterManager;
};