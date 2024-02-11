// ai-gen start (gpt, 0, e)
// prompt https://chat.openai.com/share/a181de60-e76f-496c-9bee-7ea80f2be651

#include "sp/AST/ASTNode.h"
#include "DesignExtractor.h"
#include <unordered_set>

DesignExtractor::DesignExtractor(std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriter> pkbWriter)
    : root(std::move(root)), pkbWriter(std::move(pkbWriter)) {
    // No need to assign them in the constructor body
    std::cout << "Initialized" << std::endl;
}

void DesignExtractor::extractFollows() {
    // Implementation of extractFollows method goes here
}

void DesignExtractor::extractFollowsStar() {
    // Implementation of extractFollowsStar method goes here
}

void DesignExtractor::extractParents() {
    // Implementation of extractParents method goes here
}

void DesignExtractor::extractParentsStar() {
    // Implementation of extractParentsStar method goes here
}

void DesignExtractor::extractUses() {
    // Implementation of extractUses method goes here
}

void DesignExtractor::extractModifies() {
    // Implementation of extractModifies method goes here
}

void DesignExtractor::extractAssigns() {
    // Implementation of extractAssigns method goes here
}

void DesignExtractor::extractConstants() {
    // Implementation of extractConstants method goes here
}

void DesignExtractor::extractProcedures() {
    // Implementation of extractProcedures method goes here
}

void DesignExtractor::extractStatements() {
    // Implementation of extractStatements method goes here
}

void DesignExtractor::extractIf() {
    // Implementation of extractIf method goes here
}

void DesignExtractor::extractWhiles() {
    // Implementation of extractWhiles method goes here
}

void DesignExtractor::extractCall() {
    // Implementation of extractCall method goes here
}

void DesignExtractor::extractRead() {
    // Implementation of extractRead method goes here
}

void DesignExtractor::extractPrint() {
    // Implementation of extractPrint method goes here
}

std::unordered_set<std::string> DesignExtractor::extractVariables() {
    // Recursive function to traverse the AST and extract variables
    // Implementation of extractVariablesRecursive method goes here
    std::vector<ASTNode> variables;
    recursivelyExtractVariables(root, variables);

    std::unordered_set<std::string> variableNames;
    for (auto node : variables) {
		variableNames.insert(node.value);
	}
    
    for (auto val : variableNames) {
		this->pkbWriter->insertVariable(val);
	}
	return variableNames;
}

void DesignExtractor::recursivelyExtractVariables(const std::shared_ptr<ASTNode>& node, std::vector<ASTNode>& variables) {
    // Check if the current node is of type Variable
    if (node->type == ASTNodeType::VARIABLE) {
        // If it's a variable node, add it to the set
        variables.push_back(*node);
    }

    // Recursively traverse children
    for (const auto& child : node->children) {
        recursivelyExtractVariables(child, variables);
    }
}