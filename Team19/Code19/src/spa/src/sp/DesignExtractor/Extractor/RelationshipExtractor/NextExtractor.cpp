#include "sp/DesignExtractor/Extractor/RelationshipExtractor/NextExtractor.h"

NextExtractor::NextExtractor(std::shared_ptr<NextWriter> nextWriter) : ICFGExtractor() {
	this->nextWriter = nextWriter;
}

void NextExtractor::extract(std::shared_ptr<CFGNode> cfg1, std::shared_ptr<CFGNode> cfg2) {
	nextWriter->addNext(cfg1->getLineNumber(), cfg2->getLineNumber());
}
