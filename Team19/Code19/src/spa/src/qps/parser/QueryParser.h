// Include guard to prevent multiple inclusions of this header.
#ifndef QUERYPARSER_H
#define QUERYPARSER_H

// Include necessary headers.
#include "../../spa/src/qps/parser/Token.h"
#include <vector>
#include <string>
#include <unordered_set>
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
    void throwGrammarError();
    void throwSemanticError();
    void throwIncompleteQueryError();

private:
    const std::unordered_map<TokenType, std::unordered_set<std::string>> validStmtSynonymsMap = {
            {TokenType::Parent, {"stmt", "assign", "while", "if", "print", "read"}},
            {TokenType::ParentT, {"stmt", "assign", "while", "if", "print", "read"}},
            {TokenType::Follows, {"stmt", "assign", "while", "if", "print", "read"}},
            {TokenType::FollowsT, {"stmt", "assign", "while", "if", "print", "read"}},
            {TokenType::Uses, {"stmt", "print", "while", "if", "assign", "call", "read"}},
            {TokenType::Modifies, {"stmt", "print", "while", "if", "assign", "call", "read"}},
            {TokenType::Next, {"stmt", "assign", "while", "if", "print", "read", "call"}},
            {TokenType::NextT, {"stmt", "assign", "while", "if", "print", "read", "call"}},
            {TokenType::Affects, {"stmt", "assign", "while", "if", "print", "read", "call"}},
    };

    const std::unordered_map<string, std::unordered_set<std::string>> validAttrMap = {
            {"stmt", {"stmt#"}},
            {"assign", {"stmt#"}},
            {"while", {"stmt#"}},
            {"if", {"stmt#"}},
            {"print", {"stmt#", "varName"}},
            {"read", {"stmt#", "varName"}},
            {"call", {"stmt#", "procName"}},
            {"variable", {"varName"}},
            {"procedure", {"procName"}},
            {"constant", {"value"}}
    };

    const std::unordered_map<string, TokenType> attrToTypeMap = {
            {"stmt#", TokenType::INTEGER},
            {"varName", TokenType::QuoutIDENT},
            {"procName", TokenType::QuoutIDENT},
            {"value", TokenType::INTEGER}
    };
    // Vector of tokens to be parsed.
    vector<Token> tokens;

    // Current index in the tokens vector.
    size_t currentTokenIndex;


    ParsingResult parsingResult;

    Token currentSuchThatToken;


    // Private methods for parsing different parts of the input.
    void parseDeclarations();
    void parseSelectClause();
    void parseSuchThatClause();
    void parsePatternClause();
    void parseWithClause();

    bool isUsesOrModifies();
    bool isStmtRefStmtRef();
    bool isCalls();
    bool isVarName();
    bool isConstValue();

    void parseSynonym();
    void parseEntRef();
    void parseExpressionSpec(PatternClause &clause);
    void parseQuotedExpression();
    void parseRelRef(SuchThatClause& clause);
    void parseStmtRef();
    void parseDesignEntity();
    void parseUsesOrModifies(SuchThatClause& clause);
    void parseStmtRefStmtRef(SuchThatClause& clause);
    void parseCalls(SuchThatClause& clause);
    void parseExpression();
    void parseTerm();
    void parseFactor();
    TokenType parseRef();
    void parseAttrRef();
    void parseAttr();
    void parseIfParams(PatternClause &clause);
    void parseWhileParams(PatternClause &clause);

    // Method to get the current token.
    // Returns a constant reference to the current Token object.
    const Token& currentToken() const;

    // Method to advance to the next token in the sequence.
    void advanceToken();

    // Method to check if the next token matches a given TokenType.
    bool peekNextToken(TokenType type);

    // Method to check if the current token matches a given TokenType.
    // Returns true if it matches, false otherwise.
    bool match(TokenType type);

    void parseEntSynonym();
    void parseStmtSynonyms();
    void parsePatternSynonym();


    // helper function to replace concatenation of tokens
    string concatTokens(size_t start, size_t end);






    void ensureToken(TokenType expected);


    bool checkValidStmtNum();
    bool checkValidAttr(Token synToken);
    bool checkIfStmt();
    bool checkIfEnt();
    bool checkIfPatternSyn();

};

#endif // QUERYPARSER_H


