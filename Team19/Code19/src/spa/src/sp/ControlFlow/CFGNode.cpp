#include "CFGNode.h"

CFGNode::CFGNode(int lineNumber) : lineNumber(lineNumber), children(std::vector<std::shared_ptr<CFGNode>>()) {};

void CFGNode::addFlow(std::shared_ptr<CFGNode> child) {
	// TODO
};

int CFGNode::getLineNumber() {
	return this->lineNumber;
}

std::vector<std::shared_ptr<CFGNode>> CFGNode::getChildren() {
	//TODO
	return this->children;
}