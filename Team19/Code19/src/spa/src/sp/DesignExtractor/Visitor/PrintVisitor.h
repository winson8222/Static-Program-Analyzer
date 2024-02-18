#include "sp/DesignExtractor/Visitor/IVisitor.h"

class PrintVisitor : public IVisitor {
public:
	PrintVisitor(std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriterManager> pkbWriterManager)
		: IVisitor(root, pkbWriterManager) {}

	void visit(PrintNode& node) override;
};