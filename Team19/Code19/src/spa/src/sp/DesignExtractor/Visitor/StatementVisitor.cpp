#include "sp/DesignExtractor/Visitor/IVisitor.h"

void StatementVisitor::setParents(listnode contexts, std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriterManager> pkbWriterManager) {
    int size = contexts.size();
    int curr = size - 1;

    if (curr >= 0 && !contexts[curr]->equalType(ASTNodeType::PROCEDURE) && !contexts[curr]->equalType(ASTNodeType::CALL)) {
        ParentExtractor parentExtractor(contexts[curr], root, pkbWriterManager->getParentWriter());
        parentExtractor.extract();
    }

    std::shared_ptr<ASTNode> startPoint = contexts[curr];
    while (curr >= 0 && (!startPoint->equalType(ASTNodeType::PROCEDURE)
        && !startPoint->equalType(ASTNodeType::CALL))) {
        ParentTExtractor parentExtractor(startPoint, root, pkbWriterManager->getParentTWriter());
        parentExtractor.extract();
        startPoint = contexts[curr--];
    }
}
