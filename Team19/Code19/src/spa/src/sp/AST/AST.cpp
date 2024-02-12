#include "AST.h"
#include "ASTNode.h"

// ai-gen start (gpt, 2, e)
// prompt: https://chat.openai.com/share/a181de60-e76f-496c-9bee-7ea80f2be651

AST::AST(std::unique_ptr<ASTNode> root) : root(std::move(root)) {}

const ASTNode* AST::getRoot() const {
    return root.get();
}
