#include "../../spa/src/qps/Tokenizer.h"
#include <stdexcept>

using namespace std;

// Initializes the Tokenizer with a given query string.
Tokenizer::Tokenizer(const string& query) : query(query) {
    // Regex to split based on quouted text, whitespaces, parentheses, commas, semicolons
    tokenRegex = std::regex(R"("[^"]*"|[\w.`~@#$%^&*+={}:<>-]+|_|[,;()\"\'])");
}

// This method tokenizes the stored query and returns a vector of Token objects.
vector<Token> Tokenizer::tokenize() {
    auto tokens = splitQuery();  // Call the splitQuery method to get tokens.

    return tokens;
}

// This method splits the query into tokens based on the regular expression.
// It returns a vector of Token objects representing the individual tokens.
vector<Token> Tokenizer::splitQuery() {
    vector<Token> tokens;  // Vector to store tokens.
    // Iterator to go through each token found by the regex.
    std::sregex_token_iterator iter(query.begin(), query.end(), tokenRegex);
    std::sregex_token_iterator end;  // End iterator.

    for (; iter != end; ++iter) {  // Loop through all tokens.
        auto tokenType = determineTokenType(*iter);  // Determine the type of each token.
        tokens.emplace_back(tokenType, *iter);  // Add the token to the vector.
    }

    return tokens; 
}

// Determines the type of a token based on its string representation.
// Returns the TokenType of the token.
TokenType Tokenizer::determineTokenType(const string& tokenStr) {
    // Logic to determine the type of the token.
    
    // Wildcard: A single underscore.
    if (tokenStr == "_") {
        return TokenType::Wildcard;
    }
    // ClauseKeyword: Specific clause keywords.
    else if (regex_match(tokenStr, regex("^(Select|pattern|such|that)$"))) {
        if (tokenStr == "Select") {
            return TokenType::SelectKeyword;
        }
        else if (tokenStr == "pattern") {
            return TokenType::PatternKeyword;
        }
        else if (tokenStr == "such") {
            return TokenType::SuchKeyword;
        }
        else if (tokenStr == "that") {
            return TokenType::ThatKeyword;
        }
    }
    // QuoutIDENT: An IDENT enclosed in double quotes.
    else if (regex_match(tokenStr, regex("^\"[a-zA-Z][a-zA-Z0-9]*\"$"))) {
        return TokenType::QuoutIDENT;
    }
    // QuoutConst: A constant enclosed in double quotes (for pattern matching).
    else if (regex_match(tokenStr, regex("^\"[1-9]*\"$"))) {
        return TokenType::QuoutConst;
    }
    //
    else if (regex_match(tokenStr, regex("\".*\""))) {
        return TokenType::DoubleQuote;
    }
    // Lparenthesis: '('
    else if (tokenStr == "(") {
        return TokenType::Lparenthesis;
    }
    // Rparenthesis: ')'
    else if (tokenStr == ")") {
        return TokenType::Rparenthesis;
    }
    // Semicolon: ';'
    else if (tokenStr == ";") {
        return TokenType::Semicolon;
    }
    // Comma: ','
    else if (tokenStr == ",") {
        return TokenType::Comma;
    }
    // DesignEntity: Specific keywords.
    else if (regex_match(tokenStr, regex("^(stmt|read|print|while|if|assign|variable|constant|procedure)$"))) {
        return TokenType::DesignEntity;
    }
    // RelRef: Specific keywords.
    else if (regex_match(tokenStr, regex("^(Follows|Follows\\*|Parent|Parent\\*|Uses|Modifies)$"))) {
        if (tokenStr == "Follows") {
            return TokenType::Follows;
        }
        else if (tokenStr == "Follows*") {
            return TokenType::FollowsT;
        }
        else if (tokenStr == "Parent") {
            return TokenType::Parent;
        }
        else if (tokenStr == "Parent*") {
            return TokenType::ParentT;
        }
        else if (tokenStr == "Uses") {
            return TokenType::Uses;
        }
        else if (tokenStr == "Modifies") {
            return TokenType::Modifies;
        }
    }
    // IDENT: Starts with a letter and may continue with letters or digits.
    else if (regex_match(tokenStr, regex("^[a-zA-Z][a-zA-Z0-9]*$"))) {
        return TokenType::IDENT;
    }
    // INTEGER: Either 0 or a sequence of digits with no leading zero.
    else if (regex_match(tokenStr, regex("^(0|[1-9][0-9]*)$"))) {
        return TokenType::INTEGER;
    }
    // OPERATOR" "+-*/%&|<>=!~^"
    else if (regex_match(tokenStr, regex("^[+\\-*/%&|<>=!~^]$"))) {
        return TokenType::Operator;
    }

    // If no pattern matches, throw an error.
    throw std::invalid_argument("Unrecognized token: " + tokenStr);

}
