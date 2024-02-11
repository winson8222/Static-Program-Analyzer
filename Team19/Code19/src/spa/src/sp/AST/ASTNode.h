#pragma once

#include <vector>
#include <memory>
#include <string>

enum class ASTNodeType {
    PROGRAM,
    PROCEDURE,
    STATEMENT_LIST,

    // Stmts
    ASSIGN, CALL, IF_ELSE_THEN, PRINT, READ, WHILE,

    // Expressions
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
    ASTNode() = default;
    ASTNode(ASTNodeType type, int lineNumber = 0);

    // define type of AST node
    ASTNodeType type;
    // define children of the AST
    std::vector<std::unique_ptr<ASTNode>> children;
    // define line number
    int lineNumber;
    // define value of the current node
    std::string value;
    void setValue(std::string value);


    // add children to the AST node
    void ASTNode::addChild(std::unique_ptr<ASTNode> child);    // hash the AST
    int hashInteger{ ASTNode::getNewUniqueIdentifier() };

    // convert to string
    std::string toString() const;

private:
    std::unique_ptr<ASTNode> root;
    static int uniqueIdentifier;
    static int getNewUniqueIdentifier();
    std::string toStringHelper(int tabs) const;
};
