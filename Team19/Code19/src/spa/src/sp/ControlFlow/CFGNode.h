#pragma once

#include <vector>
#include <memory>
#include <string>

/**
 * @brief Represents a node in the Abstract Syntax Tree (AST).
 */
class CFGNode {
public:
    /**
     * @brief Default constructor for ASTNode.
     */
    CFGNode() = default;

    /**
     * @brief Constructor for creating an ASTNode with specified type, line number, and value.
     *
     * @param type The type of the AST node.
     * @param lineNumber The line number associated with the AST node.
     * @param value The value associated with the AST node.
     */
    CFGNode(ASTNodeType type, int lineNumber, std::string value);

    /**
     * @brief Adds a child node to the current AST node.
     *
     * @param child A shared pointer to the child AST node to be added.
     */
    void addFlow(std::shared_ptr<CFGNode> child);
}