#pragma once

#include <stdexcept>
#include "sp/DesignExtractor/Extractor/RelationshipExtractor/IRelationshipExtractor.h"
#include "sp/AST/ASTUtility.h"

/*
* Extracts the modifies relationship between an entity and a variable
* This class implements the IRelationshipExtractor interface, so most
* of the methods are overridden with documentations from IRelationshipExtractor.h
*/
class ModifiesSExtractor : public IRelationshipExtractor {
public:
	ModifiesSExtractor(std::shared_ptr<ASTNode> ast1,
		std::shared_ptr<ASTNode> ast2,
		std::shared_ptr<ModifiesSWriter> modifiesSWriter);

	void extract() override;

private:
	std::shared_ptr<ModifiesSWriter> modifiesSWriter;
};

/*
* Extracts the modifies relationship between a procedure and a variable
* This class implements the IRelationshipExtractor interface, so most
* of the methods are overridden with documentations from IRelationshipExtractor.h
*/
class ModifiesPExtractor : public IRelationshipExtractor {
public:
	ModifiesPExtractor(std::shared_ptr<ASTNode> ast1,
		std::shared_ptr<ASTNode> ast2,
		std::shared_ptr<ModifiesPWriter> modifiesPWriter);

	void extract() override;

private:
	std::shared_ptr<ModifiesPWriter> modifiesPWriter;
};
