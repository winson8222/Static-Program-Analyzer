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

void DesignExtractor::populatePKB() {
    for (const auto& pair : designs) {
        for (auto value : pair.second) {
            if (pair.first == "c") {
				int intValue = std::stoi(value);
				this->pkbWriter->insertConstant(intValue);
            }
            else if (pair.first == "v") {
                this->pkbWriter->insertVariable(value);
			}
		}
	}
    std::cout << "PKB Populated\n" << std::endl;
}

void DesignExtractor::extractAll() {
	// Implementation of extractAll method goes here
	extractFollows();
	extractFollowsStar();
	extractParents();
	extractParentsStar();
	extractUses();
	extractModifies();
	extractAssigns();
    this->designs["c"] = extractConstants();
	extractProcedures();
	extractStatements();
	extractIf();
	extractWhiles();
	extractCall();
	extractRead();
	extractPrint();
	this->designs["v"] = extractVariables();

    std::cout << "Information Extracted\n" << std::endl;
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

std::unordered_set<std::string> DesignExtractor::extractConstants() {
    // Implementation of extractConstants method goes here
    std::vector<ASTNode> constants;
    recursivelyExtractConstants(root, constants);
    
    std::unordered_set<std::string> constantValues;
    for (auto node : constants) {
        constantValues.insert(node.value);
    }

    return constantValues;
}

void DesignExtractor::recursivelyExtractConstants(const std::shared_ptr<ASTNode>& node, std::vector<ASTNode>& constants) {
    	// Check if the current node is of type Constant
    if (node->type == ASTNodeType::CONSTANT) {
		// If it's a constant node, add it to the set
		constants.push_back(*node);
	}

	// Recursively traverse children
    for (const auto& child : node->children) {
		recursivelyExtractConstants(child, constants);
	}

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

std::unordered_set<std::string> DesignExtractor::extractCall() {
    // Implementation of extractCall method goes here
    return std::unordered_set<std::string>();
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