#include "sp/DesignExtractor/Visitor/IVisitor.h"

class ProcedureVisitor : public IVisitor {
public:
	ProcedureVisitor(std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriterManager> pkbWriterManager)
		: IVisitor(root, pkbWriterManager) {}

	void visit(ProcedureNode& node) override;
};