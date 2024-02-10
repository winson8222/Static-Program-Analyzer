#include <sp/SourceProcessor.h>
#include <sp/LexicalToken.h>
/*
SourceProcessor::SourceProcessor(PKBManager pkbManager) {
    this->pkbManager = pkbManager;
}

void SourceProcessor::parseSource(std::string filepath) {
    // Tokenize and parse source file
    Tokenizer tokenizer;
    std::vector<LexicalToken> tokens = tokenizer.tokenize(filepath);

    // Parse tokens into AST (not implemented)
    // AST ast = parser.parse(tokens);

    // Populate PKB with AST information
    populatePKB();
}

void SourceProcessor::populatePKB() {
    // Use PKBWriter to insert entities and relationships into PKB
    PKBWriter pkbWriter(pkbManager);

    // Example: Insert entities and relationships
    int stmtNum = 1;
    std::string variable = "x";
    pkbWriter.insertStatement(stmtNum);
    pkbWriter.insertVariable(variable);

    // Example: Insert relationships
    int stmt1 = 1, stmt2 = 2;
    pkbWriter.insertFollows(stmt1, stmt2);
}

*/