// ai-gen start (gpt, 0, e)
// prompt https://chat.openai.com/share/a181de60-e76f-496c-9bee-7ea80f2be651

#include <iostream>
#include <vector>
#include <unordered_set>
#include "AST/ASTNode.h" // Assuming you have ASTNode defined in ASTNode.h

class DesignExtractor {
public:
    // Constructor taking in the root node of the AST
    DesignExtractor(std::unique_ptr<ASTNode> root);

    // Method to extract all variables from the AST
    std::unordered_set<std::string> extractVariables();

private:
    // Recursive function to traverse the AST and extract variables
    void extractVariablesRecursive(ASTNode* node, std::unordered_set<std::string>& variables);

    std::unique_ptr<ASTNode> root;
};