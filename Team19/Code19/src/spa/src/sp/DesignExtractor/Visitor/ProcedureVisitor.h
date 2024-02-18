#pragma once

#include "sp/DesignExtractor/Visitor/IVisitor.h"
#include "sp/AST/ASTNode.h"
#include "pkb/PKBWriterManager.h"
#include "sp/DesignExtractor/Extractor/ProcedureExtractor.h"

class ProcedureVisitor : public IVisitor {
public:
	ProcedureVisitor(std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriterManager> pkbWriterManager)
		: IVisitor(root, pkbWriterManager) {}

	virtual void visit(std::shared_ptr<ASTNode> node) = 0;
};