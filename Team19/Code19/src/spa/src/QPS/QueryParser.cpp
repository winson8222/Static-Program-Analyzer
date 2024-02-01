// Include the Parser class header.
#include "QueryParser.h"


using namespace std;

// Constructor of the Parser class.
// Initializes the Parser with a vector of tokens to be parsed.
QueryParser::QueryParser(const vector<Token>& tokens) : tokens(tokens), currentTokenIndex(0) {}

// Orchestrates the parsing process by calling specific parsing methods for different parts of the input.
// Returns true if all parsing is successful, false otherwise.
// Will probably make it work with the Query Evaluator so that it will give the synonyms and 
// the relationships that should be passed to the PKB
bool QueryParser::parse() {
    if (!parseDeclaration()) return false;
    if (!parseSelectClause()) return false;
    if (!parseSuchThatClause()) return false;
    if (!parsePatternClause()) return false;
    return true;
}

// The parseDeclaration method of the Parser class.
// Contains logic to parse declarations.
// Currently a placeholder, actual implementation logic is needed.
bool QueryParser::parseDeclaration() {
    return true; // Placeholder
}

// The parseSelectClause method of the Parser class.
// Contains logic to parse select clauses.
// Currently a placeholder, actual implementation logic is needed.
bool QueryParser::parseSelectClause() {
    return true; // Placeholder
}

bool QueryParser::parseSuchThatClause() {
    return true; // Placeholder
}

bool QueryParser::parsePatternClause() {
    return true; // Placeholder
}

// The currentToken method of the Parser class.
// Returns a constant reference to the current Token being parsed.
const Token& QueryParser::currentToken() const {
    return tokens[currentTokenIndex];
}

// The advanceToken method of the Parser class.
// Advances to the next token in the sequence.
// Returns true if advancement is successful, false if it reaches the end of the tokens.
bool QueryParser::advanceToken() {
    if (currentTokenIndex < tokens.size() - 1) {
        ++currentTokenIndex;
        return true;
    }
    return false;
}

// Checks if the current token matches a given TokenType.
// If it matches, advances to the next token and returns true.
// This should be used in conjunction with Tokenizer::determineTokenType.
// Returns false if there is no match.
bool QueryParser::match(TokenType type) {
    if (currentToken().getType() == type) {
        advanceToken();
        return true;
    }
    return false;
}
