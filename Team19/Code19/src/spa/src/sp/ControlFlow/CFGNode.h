#pragma once

#include <vector>
#include <memory>
#include <string>

/**
 * @brief Represents a node in the Control Flow Graph (CFG).
 */
class CFGNode {
public:
	/**
	 * @brief Constructor for creating an CFGNode with no specified line number.
	 */
	CFGNode();

	/**
	 * @brief Constructor for creating an CFGNode with specified line number.
	 *
	 * @param lineNumber The line number associated with the CFG node.
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
	std::vector<std::shared_ptr<CFGNode>> getChildren();

	/**
	* @brief Gets a dummy node signifying the end of the procedure.
	*/
	static std::shared_ptr<CFGNode> getDummyNode();

	/**
	* @brief Checks if a node represents the dummy node for end of procedure.
	*/
	bool isEndOfProcedure();

private:
	static const int PROCEDURE_END_LINE_NUMBER = -1;

	int lineNumber;
	std::vector<std::shared_ptr<CFGNode>> children;
};
