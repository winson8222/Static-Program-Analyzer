#pragma once

#include "sp/DesignExtractor/Extractor/IExtractor.h"
#include <stdexcept>
#include <iostream>

/*
* Extracts the modifies relationship between an entity and a variable
* This class implements the IRelationshipExtractor interface, so most
* of the methods are overridden with documentations from IRelationshipExtractor.h
*/
class ModifiesExtractor : public IRelationshipExtractor {
public:
	ModifiesExtractor(std::shared_ptr<ASTNode> ast1,
		std::shared_ptr<ASTNode> ast2,
		std::shared_ptr<PKBWriterManager> pkbWriterManager)
		: IRelationshipExtractor(ast1, ast2, pkbWriterManager) {}

	void extract() override;

private:
	/*
	* Extracts the modifies relationship between an assignment statement and a variable
	* then writes the relationship to PKB
	*/
	void getAssignModifies();

	/*
	* Extracts the modifies relationship between a read statement and a variable
	* then writes the relationship to PKB
	*/
	void getReadModifies();

	/*
	* Extracts the modifies relationship between a if statement and a variable
	* then writes the relationship to PKB
	*/ 
	void getIfModifies();

	/*
	* Extracts the modifies relationship between a while statement and a variable
	* then writes the relationship to PKB
	*/
	void getWhileModifies();

	/*
	* Extracts the modifies relationship between a procedure and a variable
	* then writes the relationship to PKB
	*/ 
	void getProcedureModifies();

	/*
	* Extracts the modifies relationship between a call statement and a variable
	* then writes the relationship to PKB
	*/
	void getCallModifies();
};