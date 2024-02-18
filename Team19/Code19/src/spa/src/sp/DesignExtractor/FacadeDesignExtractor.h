#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "pkb/PKBWriterManager.h"
#include "sp/AST/ASTNode.h" // Assuming you have ASTNode defined in ASTNode.h
#include "sp/DesignExtractor/Visitor/IVisitor.h"

#include "sp/DesignExtractor/Visitor/AssignVisitor.h"
#include "sp/DesignExtractor/Visitor/CallVisitor.h"
#include "sp/DesignExtractor/Visitor/IfElseThenVisitor.h"
#include "sp/DesignExtractor/Visitor/PrintVisitor.h"
#include "sp/DesignExtractor/Visitor/ReadVisitor.h"
#include "sp/DesignExtractor/Visitor/WhileVisitor.h"
#include "sp/DesignExtractor/Visitor/ProcedureVisitor.h"

class FDesignExtractor {
public:
    FDesignExtractor(std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriterManager> pkbWriterManager)
        : root(root), pkbWriterManager(pkbWriterManager) {}

    void extractAll();

private:
    std::shared_ptr<ASTNode> root;
    std::shared_ptr<PKBWriterManager> pkbWriterManager;
};