#include "../../spa/src/qps/parser/Tokenizer.h"
#include <stdexcept>
#include <algorithm> // For std::remove
#include <string>    // For std::string
#include <map>

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
    auto clauseKeywordToken = determineClauseKeywordToken(tokenStr);
    if (clauseKeywordToken != TokenType::SyntaxError) return clauseKeywordToken;

    auto singleCharToken = determineSingleCharToken(tokenStr);
    if (singleCharToken != TokenType::SyntaxError) return singleCharToken;

    auto booleanToken = determineBooleanToken(tokenStr);
    if (booleanToken != TokenType::SyntaxError) return booleanToken;

    auto designEntityToken = determineDesignEntityToken(tokenStr);
    if (designEntityToken != TokenType::SyntaxError) return designEntityToken;

    auto relRefToken = determineRelRefToken(tokenStr);
    if (relRefToken != TokenType::SyntaxError) return relRefToken;

    // IDENT and INTEGER are more generic and should be checked last
    if (regex_match(tokenStr, regex("^[a-zA-Z][a-zA-Z0-9]*$"))) {
        return TokenType::IDENT;
    }
    if (regex_match(tokenStr, regex("^(0|[1-9][0-9]*)$"))) {
        return TokenType::INTEGER;
    }
    if (regex_match(tokenStr, regex("^[+\\-*/%&|<>=!~^]$"))) {
        return TokenType::Operator;
    }

    return TokenType::SyntaxError;
}


TokenType Tokenizer::determineClauseKeywordToken(const string& tokenStr) {
    if (tokenStr == "Select") return TokenType::SelectKeyword;
    if (tokenStr == "pattern") return TokenType::PatternKeyword;
    if (tokenStr == "such") return TokenType::SuchKeyword;
    if (tokenStr == "that") return TokenType::ThatKeyword;
    if (tokenStr == "with") return TokenType::WithKeyword;
    if (tokenStr == "and") return TokenType::AndKeyword;
    return TokenType::SyntaxError;
}


TokenType Tokenizer::determineBooleanToken(const string& tokenStr) {
    if (tokenStr == "BOOLEAN") {
        if (isBooleanDeclared) return TokenType::IDENT; // Assuming isBooleanDeclared checks if BOOLEAN was previously declared
        isBooleanDeclared = true;
        return TokenType::BooleanKeyword;
    }
    return TokenType::SyntaxError;
}

TokenType Tokenizer::determineDesignEntityToken(const string& tokenStr) {
    if (tokenStr == "stmt" || tokenStr == "read" || tokenStr == "print" || tokenStr == "while" ||
        tokenStr == "if" || tokenStr == "assign" || tokenStr == "variable" || tokenStr == "constant" ||
        tokenStr == "procedure" || tokenStr == "call") {
        return TokenType::DesignEntity;
    }
    return TokenType::SyntaxError;
}


TokenType Tokenizer::determineRelRefToken(const string& tokenStr) {
    if (tokenStr == "Follows") return TokenType::Follows;
    if (tokenStr == "Follows*") return TokenType::FollowsT;
    if (tokenStr == "Parent") return TokenType::Parent;
    if (tokenStr == "Parent*") return TokenType::ParentT;
    if (tokenStr == "Uses") return TokenType::Uses;
    if (tokenStr == "Modifies") return TokenType::Modifies;
    if (tokenStr == "Next") return TokenType::Next;
    if (tokenStr == "Next*") return TokenType::NextT;
    if (tokenStr == "Calls") return TokenType::Calls;
    if (tokenStr == "Calls*") return TokenType::CallsT;
    if (tokenStr == "Affects") return TokenType::Affects;
    return TokenType::SyntaxError;
}

TokenType Tokenizer::determineSingleCharToken(const string& tokenStr) {
    if (tokenStr == "(") return TokenType::Lparenthesis;
    if (tokenStr == ")") return TokenType::Rparenthesis;
    if (tokenStr == ";") return TokenType::Semicolon;
    if (tokenStr == ",") return TokenType::Comma;
    if (tokenStr == ".") return TokenType::Dot;
    if (tokenStr == "=") return TokenType::Equal;
    if (tokenStr == "<") return TokenType::LeftAngleBracket;
    if (tokenStr == ">") return TokenType::RightAngleBracket;
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