#include "sp/DesignExtractor/Visitor/CallVisitor.h"

void CallVisitor::visit() {
	// TODO
	CallExtractor callExtractor(this->root, this->pkbWriterManager);
	callExtractor.extract();

	VariableExtractor variableExtractor(this->root->children[0], this->pkbWriterManager);
	variableExtractor.extract();
}