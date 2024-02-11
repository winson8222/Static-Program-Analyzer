#include "ASTNode.h"
#include "Utility.h"
#include "AST.h"
#include <sstream>

// ai-gen start (gpt, 2, e)
// prompt: https://chat.openai.com/share/a181de60-e76f-496c-9bee-7ea80f2be651

// Initialize static member
int ASTNode::uniqueIdentifier = 0;

ASTNode::ASTNode(ASTNodeType type, int lineNumber, std::string value) {
    this->type = type;
    this->lineNumber = lineNumber;
    this->value = value;
}

void ASTNode::addChild(std::unique_ptr<ASTNode> child) {
    this->children.push_back(std::move(child));
}

void ASTNode::setValue(std::string value) {
    this->value = value;
}

// Method to generate a unique identifier for the AST node
int ASTNode::getNewUniqueIdentifier() {
    return uniqueIdentifier++;
}

// Method to convert AST node to a string
std::string ASTNode::toString() const {
    return recursiveString(0);
}

// Helper method to convert AST node to a string recursively
std::string ASTNode::recursiveString(int tabs) const {
    std::ostringstream stringStream;

    // to tab a tree representing the children
    for (int i = 0; i < tabs; ++i)
        stringStream << "  ";
    stringStream << "Type: " << Utility::getASTNodeType(type) << ", Line Number: " << lineNumber << ", Value: " << value << "\n";
    for (const auto& child : children) {
        stringStream << child->recursiveString(tabs + 1);
    }
    return stringStream.str();
}
