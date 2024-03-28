#pragma once

#include "sp/DesignExtractor/Extractor/RelationshipExtractor/IRelationshipExtractor.h"

/*
* Extracts the relation of procedure calling another directly from the AST and writes the information to the PKB.
* This class implements the IExtractor interface. The methods are documented
* from the base class at IExtractor.h
*/
class CallsPExtractor : public IRelationshipExtractor {
public:
	CallsPExtractor(std::shared_ptr<ASTNode> ast1,
		std::shared_ptr<ASTNode> ast2,
		std::shared_ptr<CallsWriter> callWriter);

	void extract() override;
private:
	std::shared_ptr<CallsWriter> callWriter;
};


/*
* Extracts the relations of procedure calling transitively on each other
* from the AST and writes the information to the PKB.
* This class implements the IExtractor interface. The methods are documented
* from the base class at IExtractor.h
*/
class CallsTExtractor : public IRelationshipExtractor {
public:
	CallsTExtractor(std::shared_ptr<ASTNode> ast1,
		std::shared_ptr<ASTNode> ast2,
		std::shared_ptr<CallsTWriter> callWriter);

	void extract() override;
private:
	std::shared_ptr<CallsTWriter> callWriter;
};

/*
* Extracts the relations of procedure calling any procedure name
* from the AST and writes the information to the PKB.
* This class implements the IExtractor interface. The methods are documented
* from the base class at IExtractor.h
*/
class CallProcNameExtractor : public IRelationshipExtractor {
public:
	CallProcNameExtractor(std::shared_ptr<ASTNode> ast1,
		std::shared_ptr<ASTNode> ast2,
		std::shared_ptr<CallProcNameWriter> callWriter);

	void extract() override;

private:
	std::shared_ptr<CallProcNameWriter> callWriter;
};
