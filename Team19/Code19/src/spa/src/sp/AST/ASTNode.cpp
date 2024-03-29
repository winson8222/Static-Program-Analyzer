#include <sstream>
#include "sp/AST/ASTNode.h"
#include "sp/AST/ASTUtility.h"

// ai-gen start (gpt, 2, e)
// prompt: https://chat.openai.com/share/a181de60-e76f-496c-9bee-7ea80f2be651

ASTNode::ASTNode() {
	this->type = ASTNodeType::PROGRAMS;
	this->lineNumber = 0;
	this->value = "default";
    this->visited = false;
}

ASTNode::ASTNode(ASTNodeType type, int lineNumber, std::string value) {
    this->type = type;
    this->lineNumber = lineNumber;
    this->value = value;
    this->visited = false;
}

void ASTNode::addChild(std::shared_ptr<ASTNode> child) {
    this->children.push_back(std::move(child));
}

void ASTNode::setValue(std::string value) {
    this->value = value;
}

std::size_t ASTNode::hash() const {
    // Concatenate the properties of ASTNode
    std::stringstream ss;
    ss << ASTUtility::getASTNodeType.find(type)->second << lineNumber << value;

    // Hash the concatenated string
    std::hash<std::string> hasher;
    return hasher(ss.str());
}

std::string ASTNode::toString() const {
    return "String representations: \n" + recursiveString(0);
}

std::string ASTNode::recursiveString(int tabs) const {
    std::ostringstream stringStream;

    // to tab a tree representing the children - each tab represents a level of the tree
    for (int i = 0; i < tabs; ++i)
        stringStream << "  ";
    stringStream << "Type: " << ASTUtility::getASTNodeType.find(type)->second << ", Line Number: " << lineNumber << ", Value: " << value << "\n";
    // depth-first search to print the children recursively
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
    if (!ASTUtility::nodeIsValidOperator(type) && !ASTUtility::nodeIsValidRelFactor(type)) {
        throw std::runtime_error("ERROR: ASTNode is not an operator");
    }
    if (children.size() > 2) {
		throw std::runtime_error("ERROR: ASTNode is not valid expression");
    }

    if (children.size() == 0) {
        return "'" + value + "'";
    }
    std::string result;

    // depth-first search to concatenate the children recursively into RPN
    for (const auto& child : children) {
		result += child->getRPNForm();
	}
    result = result + "'" + value + "'";
    return result;
}

void ASTNode::setVisited() {
    this->visited = true;
}

bool ASTNode::getVisited() {
	return this->visited;
}

std::vector<std::shared_ptr<ASTNode>> ASTNode::getChildren() {
	return this->children;
}

ASTNodeType ASTNode::getType() {
	return this->type;
}

std::string ASTNode::getValue() {
	return this->value;
}

int ASTNode::getLineNumber() {
	return this->lineNumber;
}

std::shared_ptr<ASTNode> ASTNode::getChildByIndex(int index) {
	return this->children[index];
}

void ASTNode::setChildByIndex(int index, std::shared_ptr<ASTNode> child) {
	this->children[index] = child;
}

bool ASTNode::equalType(ASTNodeType type) {
	return this->type == type;
}
// ai-gen end
