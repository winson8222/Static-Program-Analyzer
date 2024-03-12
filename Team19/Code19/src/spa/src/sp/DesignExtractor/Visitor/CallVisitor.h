#pragma once

#include "sp/DesignExtractor/Visitor/IVisitor.h"
#include "sp/DesignExtractor/Extractor/CallExtractor.h"
#include "sp/DesignExtractor/Extractor/ProcedureExtractor.h"
#include "sp/DesignExtractor/Visitor/ProcedureVisitor.h"
#include "sp/DesignExtractor/Extractor/ParentExtractor.h"

// ai-gen starts
// prompt: https://platform.openai.com/playground/p/WEPuYktjSFWSXYtIjbHMb5KZ?model=gpt-4&mode=chat

constexpr int CALLS_VARIABLE_INDEX = 0;


/*
* A visitor for the call statement which should
* call on all relevant extractors and sub-visitors
*
* This class is inherited from the IVisitor class,
* so additional documentation should be taken from the
* base abstract class unless further specified
*/
class CallVisitor : public StatementVisitor {
public:
	CallVisitor(std::shared_ptr<ASTNode> root,
		listnode context,
		std::shared_ptr<PKBWriterManager> pkbWriterManager);

	void visit() override;

private:
	/*
	* Get the list of all procedure node and call node within the contexts
	* (only those relevant in the Call Visitor)
	*/
	std::vector<std::shared_ptr<ASTNode>> getProcedureContexts();

	/*
	* Handle invokations of call procedure extractor
	*/
	void handleCallsP(std::shared_ptr<ASTNode> ast1, std::shared_ptr<ASTNode> ast2);

	/*
	* Handle invokations of call procedure extractor transitively
	*/
	void handleCallsT(std::shared_ptr<ASTNode> ast1, std::shared_ptr<ASTNode> ast2);
};

// ai-gen ends