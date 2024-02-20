#include "ASTNode.h"
#include "sp/Utility.h"
#include "AST.h"
#include <sstream>

// ai-gen start (gpt, 2, e)
// prompt: https://chat.openai.com/share/a181de60-e76f-496c-9bee-7ea80f2be651

ASTNode::ASTNode() {
	this->type = ASTNodeType::PROGRAMS;
	this->lineNumber = 0;
	this->value = "default";
}

ASTNode::ASTNode(ASTNodeType type, int lineNumber, std::string value) {
    this->type = type;
    this->lineNumber = lineNumber;
    this->value = value;
}

void ASTNode::addChild(std::shared_ptr<ASTNode> child) {
    this->children.push_back(std::move(child));
}

void ASTNode::setValue(std::string value) {
    this->value = value;
}

// Implementation of hash function for ASTNode
std::size_t ASTNode::hash() const {
    // Concatenate the properties of ASTNode
    std::stringstream ss;
    ss << Utility::getASTNodeType(type) << lineNumber << value;

    // Hash the concatenated string
    std::hash<std::string> hasher;
    return hasher(ss.str());
}

// Method to convert AST node to a string
std::string ASTNode::toString() const {
    return "String representations: \n" + recursiveString(0);
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

bool ASTNode::operator==(const ASTNode& other) const {
    return type == other.type &&
        lineNumber == other.lineNumber &&
        value == other.value;
}

std::string ASTNode::getRPNForm() {
    if (Utility::nodeIsValidOperator(type) == false) {
        throw std::runtime_error("ERROR: ASTNode is not an operator");
    }
    if (children.size() > 2) {
		throw std::runtime_error("ERROR: ASTNode is not valid expression");
    }


    if (children.size() == 0) {
        return value;
    }
    std::string result = "";
    for (const auto& child : children) {
		result += child->getRPNForm();
	}
    result = result + value;
    return result;
}