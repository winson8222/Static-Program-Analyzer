// Include guard to prevent multiple inclusions of this header.
#ifndef QUERYPARSER_H
#define QUERYPARSER_H

// Include necessary headers.
#include "Token.h"
#include <vector>
#include <string>
#include "Tokenizer.h"

using namespace std;

// The Parser class is used for parsing a sequence of tokens.
class QueryParser {
public:
    // Initializes the Parser with a vector of tokens to be parsed.
    // The 'explicit' keyword prevents implicit conversions from vector<Token> to Parser.
    explicit QueryParser(const vector<Token>& tokens);

    // The parse method initiates the parsing process.
    // Returns true if parsing is successful, false otherwise.
    bool parse();

private:
    // Vector of tokens to be parsed.
    vector<Token> tokens;

    // Current index in the tokens vector.
    size_t currentTokenIndex;

    // Private methods for parsing different parts of the input.
    bool parseDeclaration();
    bool parseSelectClause();
    bool parseSuchThatClause();
    bool parsePatternClause();

    // Method to get the current token.
    // Returns a constant reference to the current Token object.
    const Token& currentToken() const;

    // Method to advance to the next token in the sequence.
    bool advanceToken();

    // Method to check if the current token matches a given TokenType.
    // Returns true if it matches, false otherwise.
    bool match(TokenType type);
    bool parseSynonym();
    bool parseEntRef();
    bool parseExpressionSpec();
    bool parseRelRef();
    bool parseStmtRef();
    bool parseDesignEntity();
    bool isUsesOrModifies();
    bool isstmtRefstmtRef();
    bool parseUsesOrModifies();
    bool parsestmtRefstmtRef();
    bool parseExpression();
    bool parseTerm();
    bool parseFactor();
    bool parseVarName();
    bool parseConstValue();



};

#endif // QUERYPARSER_H
