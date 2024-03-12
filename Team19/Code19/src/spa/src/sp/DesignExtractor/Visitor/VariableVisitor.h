#pragma once

#include "sp/DesignExtractor/Visitor/IVisitor.h"
#include "sp/DesignExtractor/Extractor/VariableExtractor.h"
#include "sp/DesignExtractor/Extractor/UsesExtractor.h"
#include "sp/DesignExtractor/Extractor/ModifiesExtractor.h"
#include <stdexcept>


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
	std::vector<std::shared_ptr<ASTNode>> usedContexts;
	std::vector<std::shared_ptr<ASTNode>> modifiedContexts;
};