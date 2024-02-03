// Include guard to prevent multiple inclusions of this header.
#ifndef TOKENIZER_H
#define TOKENIZER_H

// Include necessary headers.
#include "Token.h"
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

private:
    // Private member variable to store the query string.
    string query;

    // A regular expression object used to identify tokens in the query string.
    regex tokenRegex;

    // A private method that splits the query into tokens based on the regular expression.
    // Returns a vector of Token objects.
    vector<Token> splitQuery();

    // A private method to determine the type of a token given its string representation.
    // Returns the TokenType of the token which is usefull in the QueryParser.
    TokenType determineTokenType(const string& tokenStr);
};

#endif // TOKENIZER_H
