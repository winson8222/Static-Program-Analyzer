// Include guard to prevent multiple inclusions of this header.
#ifndef QUERYPARSER_H
#define QUERYPARSER_H

// Include necessary headers.
#include "../../spa/src/qps/parser/Token.h"
#include <vector>
#include <string>
#include "../../spa/src/qps/parser/Tokenizer.h"
#include "../../spa/src/qps/parser/ParsingResult.h"

using namespace std;

// The parser class is used for parsing a sequence of tokens.
class QueryParser {
public:
    // Initializes the parser with a vector of tokens to be parsed.
    // The 'explicit' keyword prevents implicit conversions from vector<Token> to parser.
    explicit QueryParser(const vector<Token>& tokens);

    // The parse method initiates the parsing process.
    // Returns true if parsing is successful, false otherwise.
    ParsingResult parse();

    ParsingResult getParsingResult() const;  // Method to retrieve the result

private:
    // Vector of tokens to be parsed.
    vector<Token> tokens;

    // Current index in the tokens vector.
    size_t currentTokenIndex;






    ParsingResult parsingResult;


    // Private methods for parsing different parts of the input.
    bool parseDeclarations();
    bool parseSelectClause();
    bool parseSuchThatClause();
    bool parsePatternClause();

    bool isUsesOrModifies();
    bool isStmtRefStmtRef();
    bool isVarName();
    bool isConstValue();

    bool parseSynonym();
    bool parseEntRef();
    bool parseExpressionSpec();
    bool parseQuotedExpression();
    bool parseRelRef();
    bool parseStmtRef();
    bool parseDesignEntity();
    bool parseUsesOrModifies();
    bool parseStmtRefStmtRef();
    bool parseExpression();
    bool parseTerm();
    bool parseFactor();

    // Method to get the current token.
    // Returns a constant reference to the current Token object.
    const Token& currentToken() const;

    // Method to advance to the next token in the sequence.
    bool advanceToken();

    // Method to check if the next token matches a given TokenType.
    bool peekNextToken(TokenType type);

    // Method to check if the current token matches a given TokenType.
    // Returns true if it matches, false otherwise.
    bool match(TokenType type);

    bool parseVarSynonyms();
    bool parseStmtSynonyms();
    bool parseAssignSynonyms();





    bool ensureToken(TokenType expected);

    string getGrammarError();
    string getSemanticError();




    
};

#endif // QUERYPARSER_H
