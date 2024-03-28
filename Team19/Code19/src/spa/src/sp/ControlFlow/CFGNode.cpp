#include "CFGNode.h"

CFGNode::CFGNode() : lineNumber(PROCEDURE_END_LINE_NUMBER), children(std::vector<std::shared_ptr<CFGNode>>()) {}

CFGNode::CFGNode(int lineNumber) : lineNumber(lineNumber), children(std::vector<std::shared_ptr<CFGNode>>()) {}

void CFGNode::addChild(std::shared_ptr<CFGNode> child) {
	this->children.push_back(child);
};

std::shared_ptr<CFGNode> CFGNode::getDummyNode() {
	return std::make_shared<CFGNode>();
}

bool CFGNode::isEndOfProcedure() {
	return this->lineNumber == PROCEDURE_END_LINE_NUMBER;
}

int CFGNode::getLineNumber() {
	return this->lineNumber;
}

std::vector<std::shared_ptr<CFGNode>> CFGNode::getChildren() {
	return this->children;
}
