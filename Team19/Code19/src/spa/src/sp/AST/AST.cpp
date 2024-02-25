#include "AST.h"
#include "ASTNode.h"

AST::AST(std::shared_ptr<ASTNode> root) : root(std::move(root)) {}

const ASTNode* AST::getRoot() const {
    return root.get();
}
