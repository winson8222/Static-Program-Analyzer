// Include guard to prevent multiple inclusions of this header.
#ifndef QUERYPARSER_H
#define QUERYPARSER_H

// Include necessary headers.
#include "../../spa/src/qps/Token.h"
#include <vector>
#include <string>
#include "../../spa/src/qps/Tokenizer.h"
#include "../../spa/src/qps/ParsingResult.h"

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

    ParsingResult getParsingResult() const;  // Method to retrieve the result

private:
    // Vector of tokens to be parsed.
    vector<Token> tokens;

    // Current index in the tokens vector.
    size_t currentTokenIndex;

    ParsingResult parsingResult;

    // Private methods for parsing different parts of the input.
    void parseDeclarations();
    void parseSelectClause();
    void parseSuchThatClause();
    void parsePatternClause();

    bool isUsesOrModifies();
    bool isStmtRefStmtRef();
    bool isVarName();
    bool isConstValue();

    void parseSynonym();
    void parseEntRef();
    void parseExpressionSpec();
    void parseQuotedExpression();
    void parseRelRef();
    void parseStmtRef();
    void parseDesignEntity();
    void parseUsesOrModifies();
    void parsestmtRefstmtRef();
    void parseExpression();
    void parseTerm();
    void parseFactor();

    // Method to get the current token.
    // Returns a constant reference to the current Token object.
    const Token& currentToken() const;

    // Method to advance to the next token in the sequence.
    bool advanceToken();

    // Method to check if the current token matches a given TokenType.
    // Returns true if it matches, false otherwise.
    bool match(TokenType type);

    void ensureToken(TokenType expected);

    void throwError();

    
};

#endif // QUERYPARSER_H
