#include "sp/DesignExtractor/Extractor/RelationshipExtractor/CallsPExtractor.h"

CallsPExtractor::CallsPExtractor(std::shared_ptr<ASTNode> ast1,
	std::shared_ptr<ASTNode> ast2, std::shared_ptr<CallsWriter> callWriter)
	: IRelationshipExtractor(ast1, ast2) {
	this->callWriter = callWriter;
}

void CallsPExtractor::extract() {
	// Extract all the call statements
	this->callWriter->addCalls(this->ast1->getValue(), this->ast2->getValue());
}

CallsTExtractor::CallsTExtractor(std::shared_ptr<ASTNode> ast1,
	std::shared_ptr<ASTNode> ast2, std::shared_ptr<CallsTWriter> callWriter)
	: IRelationshipExtractor(ast1, ast2) {
	this->callWriter = callWriter;
}

void CallsTExtractor::extract() {
	// Extract all the call statements
	this->callWriter->addCallsT(this->ast1->getValue(), this->ast2->getValue());
}