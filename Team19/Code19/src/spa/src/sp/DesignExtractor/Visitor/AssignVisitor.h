#include "sp/DesignExtractor/Visitor/IVisitor.h"

class AssignVisitor : public IVisitor {
public:
	AssignVisitor(std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriterManager> pkbWriterManager)
			: IVisitor(root, pkbWriterManager) {}

	void visit(AssignNode& node) override;
};