#include "sp/DesignExtractor/Extractor/RelationshipExtractor/CallsPExtractor.h"

CallsPExtractor::CallsPExtractor(std::shared_ptr<CallsWriter> callWriter)
	: IRelationshipExtractor() {
	this->callWriter = callWriter;
}

void CallsPExtractor::extract(std::shared_ptr<ASTNode> ast1, std::shared_ptr<ASTNode> ast2) {
	// Extract all the call statements
	this->callWriter->addCalls(ast1->getValue(), ast2->getValue());
}

CallsTExtractor::CallsTExtractor(std::shared_ptr<CallsTWriter> callWriter)
	: IRelationshipExtractor() {
	this->callWriter = callWriter;
}

void CallsTExtractor::extract(std::shared_ptr<ASTNode> ast1, std::shared_ptr<ASTNode> ast2) {
	// Extract all the call statements
	this->callWriter->addCallsT(ast1->getValue(), ast2->getValue());
}

CallProcNameExtractor::CallProcNameExtractor(std::shared_ptr<CallProcNameWriter> callWriter)
	: IRelationshipExtractor() {
	this->callWriter = callWriter;
}

void CallProcNameExtractor::extract(std::shared_ptr<ASTNode> ast1, std::shared_ptr<ASTNode> ast2) {
	// Extract all the call line number to values
	this->callWriter->addCallProcName(ast1->getLineNumber(), ast2->getValue());
}
