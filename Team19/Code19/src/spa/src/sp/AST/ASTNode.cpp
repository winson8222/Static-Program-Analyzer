#include <sstream>
#include <numeric>
#include "sp/AST/ASTNode.h"
#include "sp/AST/ASTUtility.h"

// ai-gen start (gpt, 2, e)
// prompt: https://chat.openai.com/share/a181de60-e76f-496c-9bee-7ea80f2be651

ASTNode::ASTNode()
    : type(ASTNodeType::PROGRAMS), 
    lineNumber(0), 
    value("default"), 
    visited(false) {
}

ASTNode::ASTNode(ASTNodeType type, int lineNumber, std::string value)
    : type(type), 
    lineNumber(lineNumber), 
    value(std::move(value)), 
    visited(false) {

}

void ASTNode::addChild(std::shared_ptr<ASTNode> child) {
    this->children.push_back(std::move(child));
}

void ASTNode::setValue(std::string value) {
    this->value = std::move(value);
}


std::size_t ASTNode::combine_hash(std::size_t seed, std::size_t hash) const {
    return seed ^ (hash + 0x9e3779b9 + (seed << 6) + (seed >> 2));
}

std::size_t ASTNode::hash() const {
    // Obtain the string representation of 'type'
    std::string type_str = ASTUtility::getASTNodeType.find(type)->second;

    // Hash each component
    std::hash<std::string> hash_string;
    std::hash<int> hash_int;
    std::size_t hash_type = hash_string(type_str);
    std::size_t hash_lineNumber = hash_int(lineNumber);
    std::size_t hash_value = hash_string(value);

    // Combine the hashes
    std::size_t seed = hash_type;
    seed = combine_hash(seed, hash_lineNumber);
    seed = combine_hash(seed, hash_value);

    return seed;
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

    if (children.empty()) {
        return "'" + value + "'";
    }
    std::string result = std::accumulate(children.begin(), children.end(), std::string{},
        [](const std::string& acc, const std::shared_ptr<ASTNode>& child) {
            return acc + child->getRPNForm();
        });
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
