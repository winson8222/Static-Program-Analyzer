#pragma once

#include "sp/DesignExtractor/Extractor/IExtractor.h"
#include <iostream>

/*
* This class is used to extract the Parent relationship from the AST
* where one node is the direct nesting of another node. It implements the
* IRelationshipExtractor interface.
*/
class ParentExtractor : public IRelationshipExtractor {
public:
	explicit ParentExtractor(std::shared_ptr<ASTNode> ast1, 
		std::shared_ptr<ASTNode> ast2,
		std::shared_ptr<PKBWriterManager> pkbWriterManager)
		: IRelationshipExtractor(ast1, ast2, pkbWriterManager) {}

	void extract() override;
};

/*
* This class is used to extract the Parent relationship from the AST
* where one node is the direct and indirect/transitive nesting of another node. 
* It implements the IRelationshipExtractor interface.
*/
class ParentTExtractor : public IRelationshipExtractor {
public:
	explicit ParentTExtractor(std::shared_ptr<ASTNode> ast1,
		std::shared_ptr<ASTNode> ast2,
		std::shared_ptr<PKBWriterManager> pkbWriterManager)
		: IRelationshipExtractor(ast1, ast2, pkbWriterManager) {}

	void extract() override;
};