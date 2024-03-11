#pragma once

#include "sp/DesignExtractor/Extractor/IExtractor.h"
#include "sp/AST/ASTUtility.h"
#include <stdexcept>

/*
* Extracts the Uses relationship between an entity and a variable
* This class implements the IRelationshipExtractor interface, so most
* of the methods are overridden with documentations from IRelationshipExtractor.h
*/
class UsesExtractor : public IRelationshipExtractor {
public:
	UsesExtractor(std::shared_ptr<ASTNode> ast1,
		std::shared_ptr<ASTNode> ast2,
		std::shared_ptr<PKBWriterManager> pkbWriterManager)
		: IRelationshipExtractor(ast1, ast2, pkbWriterManager) {
	}

	void extract() override;

private:
	/*
	* Extracts the used relationship between an assignment statement and a variable
	* then writes the relationship to PKB
	*/
	void getAssignUses();

	/*
	* Extracts the used relationship between an print statement and a variable
	* then writes the relationship to PKB
	*/
	void getPrintUses();

	/*
	* Extracts the used relationship between an if statement and a variable
	* then writes the relationship to PKB
	*/
	void getIfUses();

	/*
	* Extracts the used relationship between an while statement and a variable
	* then writes the relationship to PKB
	*/
	void getWhileUses();

	/*
	* Extracts the used relationship between an procedure statement and a variable
	* then writes the relationship to PKB
	*/
	void getProcedureUses();

	/*
	* Extracts the used relationship between an call statement and a variable
	* then writes the relationship to PKB
	*/
	void getCallUses();
};