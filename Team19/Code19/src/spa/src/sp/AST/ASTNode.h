#pragma once

#include <vector>
#include <memory>
#include <string>

// ai-gen start (gpt, 2, e)
// prompt: https://chat.openai.com/share/a181de60-e76f-496c-9bee-7ea80f2be651

enum class ASTNodeType {
    PROGRAMS, PROCEDURE, STATEMENT_LIST,

    // Statements
    READ, PRINT, CALL, WHILE, IF_ELSE_THEN, ASSIGN,

    // Expressions and operators
    NOT, AND, OR, GREATER, GREATER_OR_EQUAL, LESSER, LESSER_OR_EQUAL,EQUAL, NOT_EQUAL,
    ADD, SUBTRACT, MULTIPLY, DIVIDE, MODULO,

    // Leaves
    VARIABLE, CONSTANT,
    OTHER,

    ERROR,
};


class ASTNode {
public:
    // constructor for AST
    ASTNode();
    ASTNode(ASTNodeType type, int lineNumber, std::string value);

    // define type of AST node
    ASTNodeType type;
    // define children of the AST
    std::vector<std::shared_ptr<ASTNode>> children;
    // add children to the AST node
    void addChild(std::shared_ptr<ASTNode> child);    // hash the AST
    // define line number
    int lineNumber;
    // define value of the current node
    std::string value;
    void setValue(std::string value);
    
    // hash the ASTNode
    std::size_t hash() const;

    // convert to string
    std::string toString() const;

private:
    std::shared_ptr<ASTNode> root;
    std::string recursiveString(int tabs) const;
};
