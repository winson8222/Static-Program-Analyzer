#include "ASTNode.h"
#include <sstream>

// Initialize static member
int ASTNode::uniqueIdentifier = 0;

ASTNode::ASTNode(ASTNodeType type, int lineNumber) {
    this->type = type;
    this->lineNumber = lineNumber;
}

void ASTNode::addChild(std::unique_ptr<ASTNode> child) {
    children.push_back(std::move(child));
}

void ASTNode::setValue(std::string value) {
    this->value = value;
}

// Method to generate a unique identifier for the AST node
int ASTNode::getNewUniqueIdentifier() {
    return ++uniqueIdentifier;
}

// Method to convert AST node to a string
std::string ASTNode::toString() const {
    return toStringHelper(0);
}

// Helper method to convert AST node to a string recursively
std::string ASTNode::toStringHelper(int tabs) const {
    std::ostringstream stringStream;
    for (int i = 0; i < tabs; ++i)
        stringStream << " ";
    stringStream << "Type: " << static_cast<int>(type) << ", Line Number: " << lineNumber << ", Value: " << value << "\n";
    for (const auto& child : children) {
        stringStream << "child";
    }
    return stringStream.str();
}
