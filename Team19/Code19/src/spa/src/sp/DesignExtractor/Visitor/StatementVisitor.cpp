#include "sp/DesignExtractor/Visitor/IVisitor.h"

void StatementVisitor::setParents(listnode contexts, std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriterManager> pkbWriterManager) {
    int size = contexts.size();
    int curr = size - 1;
    std::shared_ptr<ASTNode> startPoint = contexts[curr];
    while (curr >= 0 && (!startPoint->equalType(ASTNodeType::PROCEDURE)
        && !startPoint->equalType(ASTNodeType::CALL))) {
        startPoint = contexts[--curr];
    }

    for (int i = curr; i < size; i++) {
        std::shared_ptr<ASTNode> context = contexts[i];
        if (context->equalType(ASTNodeType::PROCEDURE)) continue;
        ParentTExtractor parentExtractor(context, root, pkbWriterManager->getParentTWriter());
        parentExtractor.extract();
    }

    if (size > 0 && !contexts[size - 1]->equalType(ASTNodeType::PROCEDURE) && !contexts[size - 1]->equalType(ASTNodeType::CALL)) {
        ParentExtractor parentExtractor(contexts[size - 1], root, pkbWriterManager->getParentWriter());
        parentExtractor.extract();
    }
}
