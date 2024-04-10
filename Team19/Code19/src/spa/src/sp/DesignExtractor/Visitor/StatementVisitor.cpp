#include "sp/DesignExtractor/Visitor/IVisitor.h"

void StatementVisitor::setParents(listnode contexts, std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriterManager> pkbWriterManager) {
    int size = contexts.size();
    int curr = size - 1;

    ParentTExtractor parentExtractor(pkbWriterManager->getParentTWriter());
    if (curr >= 0 && !contexts[curr]->equalType(ASTNodeType::PROCEDURE) && !contexts[curr]->equalType(ASTNodeType::CALL)) {
        ParentExtractor parentExtractor(pkbWriterManager->getParentWriter());
        parentExtractor.extract(contexts[curr], root);
    }

    std::shared_ptr<ASTNode> startPoint = contexts[curr];
    while (curr >= 0 && (!startPoint->equalType(ASTNodeType::PROCEDURE)
        && !startPoint->equalType(ASTNodeType::CALL))) {
        parentExtractor.extract(startPoint, root);
        startPoint = contexts[curr--];
    }
}
