#pragma once

#include <stdexcept>
#include "sp/DesignExtractor/Visitor/IVisitor.h"
#include "sp/DesignExtractor/Visitor/VariableVisitor.h"
#include "sp/DesignExtractor/Extractor/EntityExtractor/ReadExtractor.h"
#include "sp/DesignExtractor/Extractor/RelationshipExtractor/ParentExtractor.h"
#include "sp/DesignExtractor/Extractor/RelationshipExtractor/ReadVarExtractor.h"

constexpr int READ_VARIABLE_INDEX = 0;
/*
* A visitor for the read statement which should
* call on all relevant extractors and sub-visitors
*
* This class is inherited from the IVisitor class,
* so additional documentation should be taken from the
* base abstract class unless further specified
*/
class ReadVisitor : public StatementVisitor {
public:
	ReadVisitor(std::shared_ptr<ASTNode> root,
		listnode context,
		std::shared_ptr<PKBWriterManager> pkbWriterManager);

	void visit() override;

private:
	std::shared_ptr<ASTNode> variableChild;
};
