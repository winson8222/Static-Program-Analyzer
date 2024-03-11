#pragma once

#include "sp/DesignExtractor/Extractor/IExtractor.h"

/*
* Extracts the call statement from the AST and writes the information to the PKB.
* This class implements the IExtractor interface. The methods are documented
* from the base class at IExtractor.h
*/
class CallExtractor : public IExtractor {
public:
	CallExtractor(std::shared_ptr<ASTNode> root, std::shared_ptr<CallWriter> callWriter);

	void extract() override;
private:
	std::shared_ptr<CallWriter> callWriter;
};

class CallsPExtractor : public IRelationshipExtractor {
public:
	CallsPExtractor(std::shared_ptr<ASTNode> ast1, 
		std::shared_ptr<ASTNode> ast2,
		std::shared_ptr<CallsWriter> callWriter);

	void extract() override;
private:
	std::shared_ptr<CallsWriter> callWriter;
};

class CallsTExtractor : public IRelationshipExtractor {
public:
	CallsTExtractor(std::shared_ptr<ASTNode> ast1,
		std::shared_ptr<ASTNode> ast2,
		std::shared_ptr<CallsTWriter> callWriter);

	void extract() override;
private:
	std::shared_ptr<CallsTWriter> callWriter;
};