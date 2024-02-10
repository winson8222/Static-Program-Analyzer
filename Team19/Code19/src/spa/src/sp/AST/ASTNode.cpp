#include "ASTNode.h"

ASTNode::ASTNode(ASTNodeType type) : type(type) {}

void ASTNode::addChild(std::unique_ptr<ASTNode> child) {
    children.push_back(std::move(child));
}

const std::vector<std::unique_ptr<ASTNode>>& ASTNode::getChildren() const {
    return children;
}

ASTNodeType ASTNode::getType() const {
    return type;
}