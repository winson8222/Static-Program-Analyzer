#include "sp/SourceProcessor.h"

SourceProcessor::SourceProcessor(std::string filename, std::shared_ptr<PKBManager> pkbManager) 
	: parser(filename), pkbManager(pkbManager), root(std::make_shared<ASTNode>()) {}

void SourceProcessor::reset() {
	this->root = std::make_shared<ASTNode>();
}

void SourceProcessor::parseSIMPLE() {
	this->root = parser.parse();
}

void SourceProcessor::extractAndPopulate() {
    // Use PKBWriter to insert entities and relationships into PKB
    std::shared_ptr<PKBWriterManager> pkbWriterManager = this->pkbManager->getPKBWriterManager();
	DesignExtractorFacade designExtractor(this->root, pkbWriterManager);
	designExtractor.extractAll();
}