#include "sp/SourceProcessor.h"
#include <iostream>

SourceProcessor::SourceProcessor(PKBManager pkbManager) {
    this->pkbManager = pkbManager;
    std::cout << "File created" << std::endl;
}

void SourceProcessor::reset() {
}

void SourceProcessor::tokenize(std::string filepath) {
    // Tokenize and parse source file
    std::vector<LexicalToken> tokens = Tokenizer::tokenize(filepath);
    this->tokens = tokens;
    // Parse tokens into AST (not implemented)
    // AST ast = parser.parse(tokens);
}

void SourceProcessor::parse() {
	// Parse tokens into AST (not implemented)
	// AST ast = parser.parse(tokens);
}

void SourceProcessor::buildAST() {
	// Build AST from parsed tokens (not implemented)
	// this->root = ast.build();
}

void SourceProcessor::extractAndPopulate() {
    // Use PKBWriter to insert entities and relationships into PKB
    std::shared_ptr<PKBWriter> pkbWriter = this->pkbManager.getPKBWriter();

    // Example: Insert entities and relationships
    int stmtNum = 1;
    std::string variable = "x";
    pkbWriter->insertStatement(stmtNum);
    pkbWriter->insertVariable(variable);
    pkbWriter->insertModifiesS(stmtNum, variable);
}
