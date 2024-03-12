#include "sp/DesignExtractor/Visitor/IVisitor.h"

void StatementVisitor::setParents(listnode contexts, std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriterManager> pkbWriterManager) {
	int size = contexts.size();
	for (int i = 0; i < size; i++) {
		std::shared_ptr<ASTNode> context = contexts[i];
		if (context->type == ASTNodeType::PROCEDURE) continue;
		ParentTExtractor parentExtractor(context, root, pkbWriterManager->getParentTWriter());
		parentExtractor.extract();
	}
	if (size > 0 && !contexts[size - 1]->equalType(ASTNodeType::PROCEDURE)) {
		ParentExtractor parentExtractor(contexts[size - 1], root, pkbWriterManager->getParentWriter());
		parentExtractor.extract();
	}
}