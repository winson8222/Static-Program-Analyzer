#pragma once

#include <vector>
#include <memory>

enum class ASTNodeType {
    Addition,
    Subtraction,
    Multiplication,
    Division,
    Number
};

class ASTNode {
public:
    ASTNode(ASTNodeType type);

    void addChild(std::unique_ptr<ASTNode> child);
    const std::vector<std::unique_ptr<ASTNode>>& getChildren() const;
    ASTNodeType getType() const;

private:
    ASTNodeType type;
    std::vector<std::unique_ptr<ASTNode>> children;
};