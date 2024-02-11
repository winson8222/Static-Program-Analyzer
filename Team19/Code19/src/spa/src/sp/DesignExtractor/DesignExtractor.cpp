// ai-gen start (gpt, 0, e)
// prompt https://chat.openai.com/share/a181de60-e76f-496c-9bee-7ea80f2be651

#include "DesignExtractor.h"

// Constructor implementation
DesignExtractor::DesignExtractor(std::unique_ptr<ASTNode> root) : root(std::move(root)) {}

// Method to extract all variables from the AST
std::unordered_set<std::string> DesignExtractor::extractVariables() {
    std::unordered_set<std::string> variables;
    extractVariablesRecursive(root.get(), variables);
    return variables;
}

// Recursive function to traverse the AST and extract variables
void DesignExtractor::extractVariablesRecursive(ASTNode* node, std::unordered_set<std::string>& variables) {
    if (!node) {
        return;
    }

    // If the node represents a variable, add it to the set of variables
    if (node->getType() == ASTNodeType::VARIABLE) {
        variables.insert(node->getValue());
    }

    // Recursively process children nodes
    for (const auto& child : node->getChildren()) {
        extractVariablesRecursive(child.get(), variables);
    }
}