#include "sp/DesignExtractor/Extractor/RelationshipExtractor/NextExtractor.h"

NextExtractor::NextExtractor(std::shared_ptr<CFGNode> cfgNode1, 
	std::shared_ptr<CFGNode> cfgNode2,
	std::shared_ptr<NextWriter> nextWriter) 
	: ICFGExtractor(cfgNode1, cfgNode2) {
	this->nextWriter = nextWriter;
}

void NextExtractor::extract() {
	nextWriter->addNext(this->cfg1->getLineNumber(), this->cfg2->getLineNumber());
}