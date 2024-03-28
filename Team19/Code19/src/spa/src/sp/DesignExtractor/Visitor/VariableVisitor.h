#pragma once

#include <stdexcept>
#include "sp/DesignExtractor/Visitor/IVisitor.h"
#include "sp/DesignExtractor/Extractor/EntityExtractor/VariableExtractor.h"
#include "sp/DesignExtractor/Extractor/RelationshipExtractor/UsesExtractor.h"
#include "sp/DesignExtractor/Extractor/RelationshipExtractor/ModifiesExtractor.h"


/*
* A visitor for the variable which should
* call on all relevant extractors and sub-visitors
*
* This class is inherited from the IVisitor class,
* so additional documentation should be taken from the
* base abstract class unless further specified
*/
class VariableVisitor : public IVisitor {
public:
	VariableVisitor(std::shared_ptr<ASTNode> root,
		std::shared_ptr<PKBWriterManager> pkbWriterManager);

	void visit() override;

	/*
	* Set current Variable Visitor to contains context of which statement or procedure USES it
	* @param contexts - list of contexts that uses the variable
	* @param parent - the parent node of the context
	* This method should be called inside statements that are:
	* - Assign, Call, If, While, Print
	*/
	void setUsedContext(listnode contexts, std::shared_ptr<ASTNode> parent);

	/*
	* Set current Variable Visitor to contains context of which statement or procedure MODIFIES it
	* @param contexts - list of contexts that modifies the variable
	* @param parent - the parent node of the context
	* This method should be called inside statements that are:
	* - Assign, Call, If, While, Read
	*/
	void setModifiedContext(listnode contexts, std::shared_ptr<ASTNode> parent);
	
private:
	/*
	* Contexts of the current variable, all nodes that use it
	*/
	std::vector<std::shared_ptr<ASTNode>> usedContexts;

	/*
	* Contexts of the current variable, all nodes that modifies it
	* 	
	*/
	std::vector<std::shared_ptr<ASTNode>> modifiedContexts;


	/*
	* Handle invokations of UsesPExtractor
	*/
	void handleUsesP(std::shared_ptr<ASTNode> user, std::shared_ptr<ASTNode> variable);

	/*
	* Handle invokations of UsesSExtractor
	*/
	void handleUsesS(std::shared_ptr<ASTNode> user, std::shared_ptr<ASTNode> variable);

	/*
	* Handle invokations of ModifiesPExtractor
	*/
	void handleModifiesP(std::shared_ptr<ASTNode> user, std::shared_ptr<ASTNode> variable);

	/*
	* Handle invokations of ModifiesSExtractor
	*/
	void handleModifiesS(std::shared_ptr<ASTNode> user, std::shared_ptr<ASTNode> variable);
};