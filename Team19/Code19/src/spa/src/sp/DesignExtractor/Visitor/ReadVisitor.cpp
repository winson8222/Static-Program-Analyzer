#include "sp/DesignExtractor/Visitor/ReadVisitor.h"


void ReadVisitor::visit() {
	ReadExtractor readExtractor(this->root, this->pkbWriterManager);
	readExtractor.extract();

	VariableExtractor variableExtractor(this->root->children[0], this->pkbWriterManager);
	variableExtractor.extract();
}