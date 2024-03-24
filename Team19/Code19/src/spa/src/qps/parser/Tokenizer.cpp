#include "../../spa/src/qps/parser/Tokenizer.h"
#include <stdexcept>
#include <algorithm> // For std::remove
#include <string>    // For std::string
#include <map>
#include <unordered_map>

using namespace std;

// Initializes the Tokenizer with a given query string.
Tokenizer::Tokenizer(const string& query) : query(query) {
    // Regex to split based on quouted text, whitespaces, parentheses, commas, semicolons
    tokenRegex = std::regex(R"("[^"]*"|[\w`~@#$%^&*+={}:-]+|_|[,;.<>()\"\'])");
}

// This method tokenizes the stored query and returns a vector of Token objects.
vector<Token> Tokenizer::tokenize() {
    splitQuery();  // Call the splitQuery method to get tokens.

    return tokens;
}

// This method splits the query into tokens based on the regular expression.
// It returns a vector of Token objects representing the individual tokens.
void Tokenizer::splitQuery() {
    // Iterator to go through each token found by the regex.
    std::sregex_token_iterator iter(query.begin(), query.end(), tokenRegex);
    std::sregex_token_iterator end;  // End iterator.

    for (; iter != end; ++iter) {  // Loop through all tokens.
        auto tokenType = determineTokenType(*iter);  // Determine the type of each token.
        if (*iter == "and") {
            tokens.emplace_back(tokenType, lastRelationship);  // Add the token to the vector.
        }
        else {
            tokens.emplace_back(tokenType, removeSpaces(*iter));  // Add the token to the vector.
        }

    }


}

// Determines the type of token based on its string representation.
// Returns the TokenType of the token.

TokenType Tokenizer::determineTokenType(const string& tokenStr) {
    if (tokenStr == "_") {
        return TokenType::Wildcard;
    }

    TokenType tokenType;

    tokenType = determineClauseKeywordToken(tokenStr);
    if (!isSyntaxError(tokenType)) return tokenType;

    tokenType = determineBooleanToken(tokenStr);
    if (!isSyntaxError(tokenType)) return tokenType;

    tokenType = determineAttrNameToken(tokenStr);
    if (!isSyntaxError(tokenType)) return tokenType;

    tokenType = determineQuoutToken(tokenStr);
    if (!isSyntaxError(tokenType)) return tokenType;

    tokenType = determineSingleCharToken(tokenStr);
    if (!isSyntaxError(tokenType)) return tokenType;

    tokenType = determineDesignEntityToken(tokenStr);
    if (!isSyntaxError(tokenType))return tokenType;

    tokenType = determineRelRefToken(tokenStr);
    if (!isSyntaxError(tokenType)) return tokenType;

    // IDENT: Starts with a letter and may continue with letters or digits.
    if (regex_match(tokenStr, regex("^[a-zA-Z][a-zA-Z0-9]*$"))) {
        return TokenType::IDENT;
    }

    // INTEGER: Either 0 or a sequence of digits with no leading zero.
    if (regex_match(tokenStr, regex("^(0|[1-9][0-9]*)$"))) {
        return TokenType::INTEGER;
    }

    // OPERATOR: "+-*/%&|<>=!~^"
    if (regex_match(tokenStr, regex("^[+\\-*/%&|!~^]$"))) {
        return TokenType::Operator;
    }

    return TokenType::SyntaxError;
}

bool Tokenizer::isSyntaxError(TokenType tokenType) {
    return tokenType == TokenType::SyntaxError;
}

TokenType Tokenizer::determineClauseKeywordToken(const string& tokenStr) {
    if (regex_match(tokenStr, regex("^(Select|pattern|such|that|with|and)$"))) {
        if (!tokens.empty() && (isSynonym() || tokens.back().getType() == TokenType::SelectKeyword)) {
            return TokenType::IDENT;
        }

        auto it = tokenFunctionMap.find(tokenStr);
        if (it != tokenFunctionMap.end()) {
            return it->second(); // Execute the function
        }
    }
    return TokenType::SyntaxError;
}


TokenType Tokenizer::determineBooleanToken(const string& tokenStr) {
    if (tokenStr == "BOOLEAN") {
        if (!tokens.empty() && (isSynonym() || (tokens.back().getType() == TokenType::SelectKeyword && isBooleanDeclared))) {
            isBooleanDeclared = true;
            return TokenType::IDENT;
        }
        return TokenType::BooleanKeyword;
    }
    return TokenType::SyntaxError;
}

TokenType Tokenizer::determineQuoutToken(const string& tokenStr) {
    if (regex_match(tokenStr, regex("^\"\\s*[a-zA-Z][a-zA-Z0-9]*\\s*\"$"))) {
        return TokenType::QuoutIDENT;
    }
    if (regex_match(tokenStr, regex("^\"\\s*[0-9]+\\s*\"$"))) {
        return TokenType::QuoutConst;
    }
    if (regex_match(tokenStr, regex("\".*\""))) {
        return TokenType::ExpressionSpec;
    }
    return TokenType::SyntaxError;
}

TokenType Tokenizer::determineSingleCharToken(const string& tokenStr) {
    if (signMap.find(tokenStr) != signMap.end()) {
        return signMap[tokenStr];
    }
    return TokenType::SyntaxError;
}

TokenType Tokenizer::determineDesignEntityToken(const string& tokenStr) {
    if (regex_match(tokenStr, regex("^(stmt|read|print|while|if|assign|variable|constant|procedure|call)$"))) {
        if (!tokens.empty() && (isSynonym() || tokens.back().getType() == TokenType::SelectKeyword)) {
            return TokenType::IDENT;
        } else {
            return TokenType::DesignEntity;
        }
    }
    return TokenType::SyntaxError;
}

TokenType Tokenizer::determineRelRefToken(const string& tokenStr) {
    if (regex_match(tokenStr, regex("^(Follows|Follows\\*|Parent|Parent\\*|Uses|Modifies|Next|Next\\*|Calls|Calls\\*|Affects)$"))) {
        if (!tokens.empty() && (isSynonym() || tokens.back().getType() == TokenType::SelectKeyword)) {
            return TokenType::IDENT;
        }

        if (clauseTypeMap.find(tokenStr) != clauseTypeMap.end()) {
            return clauseTypeMap[tokenStr];
        }
    }
    return TokenType::SyntaxError;
}

TokenType Tokenizer::determineAttrNameToken(const string& tokenStr) {
    if (regex_match(tokenStr, regex("^(procName|varName|value|stmt#)$"))) {
        if (!tokens.empty() && (isSynonym() || tokens.back().getType() == TokenType::SelectKeyword)) {
            return TokenType::IDENT;
        } else {
            return TokenType::AttrName;
        }
    }
    return TokenType::SyntaxError;
}

// Check if the current token is a declaration token
bool Tokenizer::checkIfDeclaration() {
    int i = tokens.size() - 1;
    while(i >= 0) {
        if (tokens[i].getType() == TokenType::DesignEntity) {
            return true;
        }
        if (tokens[i].getType() == TokenType::Semicolon) {
            return false;
        }
        i--;
    }
    return false;
}

string Tokenizer::removeSpaces(string str) {
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
    return str;
}

bool Tokenizer::isSynonym() {
    return checkIfDeclaration() || tokens.back().getType() == TokenType::Lparenthesis
           || tokens.back().getType() == TokenType::Comma || tokens.back().getType() == TokenType::PatternKeyword
           || tokens.back().getType() == TokenType::LeftAngleBracket;
}