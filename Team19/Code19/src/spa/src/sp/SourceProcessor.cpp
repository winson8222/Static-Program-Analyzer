#include "sp/SourceProcessor.h"
#include <iostream>

SourceProcessor::SourceProcessor(std::string filename, std::shared_ptr<PKBManager> pkbManager) {
    this->pkbManager = pkbManager;
	this->parser = SimpleParser(filename);
    this->root = std::make_shared<ASTNode>();
    std::cout << "File created" << std::endl;
}

void SourceProcessor::reset() {
	this->root = std::make_shared<ASTNode>();
}

void SourceProcessor::parseSIMPLE() {
	// Parse tokens into AST (not implemented)
	this->root = parser.parseProgram();
	std::cout << this->root->toString() << std::endl;
}

void SourceProcessor::buildAST() {
	// Build AST from parsed tokens (not implemented)
	// this->root = ast.build();
}


void SourceProcessor::extractAndPopulate() {
    // Use PKBWriter to insert entities and relationships into PKB
    std::shared_ptr<PKBWriterManager> pkbWriterManager = this->pkbManager->getPKBWriterManager();
	DesignExtractor designExtractor(this->root, pkbWriterManager);
	designExtractor.extractAll();
    designExtractor.populatePKB();
}
