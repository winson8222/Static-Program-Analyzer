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
		this->contexts = std::vector<std::shared_ptr<ASTNode>>();
	}

	void visit() override;
};