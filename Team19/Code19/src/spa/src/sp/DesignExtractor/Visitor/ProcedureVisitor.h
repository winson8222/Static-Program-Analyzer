#pragma once

#include "sp/DesignExtractor/Visitor/IVisitor.h"
#include "sp/AST/ASTNode.h"
#include "pkb/PKBWriterManager.h"
#include "sp/DesignExtractor/Extractor/ProcedureExtractor.h"
#include "sp/DesignExtractor/Visitor/StatementListVisitor.h"

class ProcedureVisitor : public IVisitor {
public:
	ProcedureVisitor(std::shared_ptr<ASTNode> node, std::shared_ptr<PKBWriterManager> pkbWriterManager)
		: IVisitor(node, pkbWriterManager) {
		if (node->type != ASTNodeType::PROCEDURE) {
			throw std::invalid_argument("ProcedureVisitor - input node type must be of type PROCEDURE");
		}
	}

	// Purpose: From this node, extract information from the current node
	// then recursively call other visitor to visit children nodes
	void visit(std::shared_ptr<ASTNode> node) override;
	void visit() override;
};