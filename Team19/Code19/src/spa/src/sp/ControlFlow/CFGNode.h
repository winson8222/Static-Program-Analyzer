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
	 * @brief Default constructor for CFGNode.
	 */
	CFGNode() = default;

	/**
	 * @brief Constructor for creating an CFGNode with specified line number.
	 *
	 * @param lineNumber The line number associated with the AST node.
	 */
	CFGNode(int lineNumber);

	/**
	 * @brief Adds a child node to the current CFG node.
	 *
	 * @param child A shared pointer to the child CFG node to be added.
	 */
	void addChild(std::shared_ptr<CFGNode> child);

	/**
	 * @brief Returns the line number this CFGNode is representing.
	 *
	 * @return The respective line number.
	 */
	int getLineNumber();

	/**
	 * @brief Returns all possible CFGNodes that this CFGNode links to.
	 *
	 * @return A vector of pointers to all CFGNodes.
	 */
	vector<std::shared_ptr<CFGNode>> getChildren();

private:
	int lineNumber;
	vector<std::shared_ptr<CFGNode>> children;
}