// Include the Tokenizer class header.
#include "Tokenizer.h"

using namespace std;

// Initializes the Tokenizer with a given query string.
// The regex for tokenization is also defined here.
Tokenizer::Tokenizer(const string& query) : query(query) {
    // Regex to split based on whitespaces, parentheses, commas, semicolons
    tokenRegex = std::regex(R"([\s,;()]+)");
}

// This method tokenizes the stored query and returns a vector of Token objects.
vector<Token> Tokenizer::tokenize() {
    auto tokens = splitQuery();  // Call the splitQuery method to get tokens.

    //More processing is possible here

    return tokens;  // Return the vector of tokens.
}

// This method splits the query into tokens based on the regular expression.
// It returns a vector of Token objects representing the individual tokens.
vector<Token> Tokenizer::splitQuery() {
    vector<Token> tokens;  // Vector to store tokens.
    // Iterator to go through each token found by the regex.
    std::sregex_token_iterator iter(query.begin(), query.end(), tokenRegex, -1);
    std::sregex_token_iterator end;  // End iterator.

    for (; iter != end; ++iter) {  // Loop through all tokens.
        auto tokenType = determineTokenType(*iter);  // Determine the type of each token.
        tokens.emplace_back(tokenType, *iter);  // Add the token to the vector.
    }

    return tokens;  // Return the vector of tokens.
}

// Determines the type of a token based on its string representation.
// Returns the TokenType of the token.
TokenType Tokenizer::determineTokenType(const string& tokenStr) {
    // Logic to determine the type of the token.
    // This is a placeholder and should be modified according to specific grammar-rules/Lexical-rules.
    
    // Sample implementation to identify an identifier.
    if (std::regex_match(tokenStr, std::regex("^[a-zA-Z][a-zA-Z0-9]*$"))) {
        return TokenType::IDENT;
    }

    // Add more conditions for other token types.

    return TokenType::IDENT; // Default return type, should be modified.
}
