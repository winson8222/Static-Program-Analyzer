#include "sp/DesignExtractor/Visitor/IVisitor.h"

class CallVisitor : public IVisitor {
public:
	CallVisitor(std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriterManager> pkbWriterManager)
			: IVisitor(root, pkbWriterManager) {}

	void visit(CallNode& node) override;
};