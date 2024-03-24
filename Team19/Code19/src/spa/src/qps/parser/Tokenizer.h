#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "../../spa/src/qps/parser/Token.h"
#include <string>
#include <vector>
#include <regex>

using namespace std;

// The Tokenizer class is used for converting a string query into tokens.
class Tokenizer {
public:
    // Constructor for the Tokenizer class.
    // It takes a constant reference to a string as input, representing the query to be tokenized.
    // The 'explicit' keyword prevents implicit conversions from string to Tokenizer.
    explicit Tokenizer(const string& query);

    // This method tokenizes the stored query and returns a vector of Token objects.
    vector<Token> tokenize();

    string removeSpaces(string str);

private:
    // Private member variable to store the query string.
    string query;

    // A regular expression object used to identify tokens in the query string.
    regex tokenRegex;

    // string the represents the last relationship used (such that, with, pattern)
    // it is used to explicitly state the relationship instead of "and"
    string lastRelationship;

    // A private method that splits the query into tokens based on the regular expression.
    // Returns a vector of Token objects.
    void splitQuery();

    vector<Token> tokens;
    bool isBooleanDeclared = false; //special case for boolean because it is treated as a synonym after selection if it was declared

    // A private method to determine the type of a token given its string representation.
    // Returns the TokenType of the token which is usefull in the QueryParser.
    TokenType determineTokenType(const string& tokenStr);
    // helper fn for determineTokenType
    TokenType determineClauseKeywordToken(const string& tokenStr);
    TokenType determineSingleCharToken(const string& tokenStr);
    TokenType determineBooleanToken(const string& tokenStr);
    TokenType determineDesignEntityToken(const string& tokenStr);
    TokenType determineRelRefToken(const string& tokenStr);

    bool checkIfDeclaration();
    bool isSynonym();

};

#endif // TOKENIZER_H
