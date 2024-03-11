#include "CFGNode.h"

CFGNode::CFGNode(ASTNodeType type, int lineNumber, std::string value){};

/**
 * @brief Adds a child node to the current AST node.
 *
 * @param child A shared pointer to the child AST node to be added.
 */
void CFGNode::addFlow(std::shared_ptr<CFGNode> child) {};