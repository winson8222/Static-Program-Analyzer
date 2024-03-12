#pragma once

#include "sp/DesignExtractor/Extractor/IExtractor.h"

/*
* This class is used to extract the Parent relationship from the AST
* where one node is the direct nesting of another node. It implements the
* IRelationshipExtractor interface.
*/
class ParentExtractor : public IRelationshipExtractor {
public:
	ParentExtractor(std::shared_ptr<ASTNode> ast1,
		std::shared_ptr<ASTNode> ast2,
		std::shared_ptr<ParentWriter> parentWriter);

	void extract() override;

private:
	std::shared_ptr<ParentWriter> parentWriter;
};

/*
* This class is used to extract the Parent relationship from the AST
* where one node is the direct and indirect/transitive nesting of another node. 
* It implements the IRelationshipExtractor interface.
*/
class ParentTExtractor : public IRelationshipExtractor {
public:
	ParentTExtractor(std::shared_ptr<ASTNode> ast1,
		std::shared_ptr<ASTNode> ast2,
		std::shared_ptr<ParentTWriter> parentTWriter);

	void extract() override;

private:
	std::shared_ptr<ParentTWriter> parentTWriter;
};