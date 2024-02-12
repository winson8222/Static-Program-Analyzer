#include <sp/SourceProcessor.h>
#include <sp/LexicalToken.h>
#include <iostream>

SourceProcessor::SourceProcessor(PKBManager pkbManager) {
    this->pkbManager = pkbManager;
    std::cout << "File created" << std::endl;
}

void SourceProcessor::parseSource(std::string filepath) {
    // Tokenize and parse source file
    
    // Parse tokens into AST (not implemented)
    // AST ast = parser.parse(tokens);

    // Populate PKB with AST information
    populatePKB();
}

void SourceProcessor::populatePKB() {
    // Use PKBWriter to insert entities and relationships into PKB
    std::shared_ptr<PKBWriter> pkbWriter = this->pkbManager.getPKBWriter();

    // Example: Insert entities and relationships
    int stmtNum = 1;
    std::string variable = "x";
    pkbWriter->insertStatement(stmtNum);
    pkbWriter->insertVariable(variable);
    pkbWriter->insertModifiesS(stmtNum, variable);
}
