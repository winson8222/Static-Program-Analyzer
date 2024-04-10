#pragma once

#include <stdexcept>
#include "sp/DesignExtractor/Extractor/RelationshipExtractor/IRelationshipExtractor.h"
#include "sp/AST/ASTUtility.h"

/*
* Extracts the Uses relationship between an entity and a variable
* This class implements the IRelationshipExtractor interface, so most
* of the methods are overridden with documentations from IRelationshipExtractor.h
*/
class UsesSExtractor : public IRelationshipExtractor {
public:
	UsesSExtractor(std::shared_ptr<UsesSWriter> usesSWriter);

	void extract(std::shared_ptr<ASTNode> ast1, std::shared_ptr<ASTNode> ast2) override;

private:
	std::shared_ptr<UsesSWriter> usesSWriter;
};

/*
* Extracts the Uses relationship between a procedure and a variable
* This class implements the IRelationshipExtractor interface, so most
* of the methods are overridden with documentations from IRelationshipExtractor.h
*/
class UsesPExtractor : public IRelationshipExtractor {
public:
	UsesPExtractor(std::shared_ptr<UsesPWriter> usesPWriter);

	void extract(std::shared_ptr<ASTNode> ast1, std::shared_ptr<ASTNode> ast2) override;

private:
	std::shared_ptr<UsesPWriter> usesPWriter;
};
