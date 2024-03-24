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

static const regex IDENT_REGEX(R"(^[a-zA-Z][a-zA-Z0-9]*$)");
static const regex INTEGER_REGEX(R"(^(0|[1-9][0-9]*)$)");
static const regex clauseKeywordRegex(R"((Select|pattern|such|that|with|and))");
static const regex quoutIDENTRegex(R"(^"\s*[a-zA-Z][a-zA-Z0-9]*\s*"$)");
static const regex quoutConstRegex(R"(^"\s*[0-9]+\s*"$)");
static const regex designEntityRegex(R"((stmt|read|print|while|if|assign|variable|constant|procedure|call))");
static const regex relRefRegex(R"((Follows|Follows\*|Parent|Parent\*|Uses|Modifies|Next|Next\*|Calls|Calls\*|Affects))");
static const regex attrNameRegex(R"((procName|varName|value|stmt#))");
static const regex expressionSpecRegex(R"(".*")");

// Determines the type of token based on its string representation.
// Returns the TokenType of the token.
TokenType Tokenizer::determineTokenType(const string& tokenStr) {
    if (tokenStr == "_") return TokenType::Wildcard;

    if (regex_match(tokenStr, clauseKeywordRegex)) return determineClauseKeywordToken(tokenStr);
    if (tokenStr == "BOOLEAN") return determineBooleanToken(tokenStr);
    if (regex_match(tokenStr, quoutIDENTRegex)) return TokenType::QuoutIDENT;
    if (regex_match(tokenStr, quoutConstRegex)) return TokenType::QuoutConst;
    if (regex_match(tokenStr, expressionSpecRegex)) return TokenType::ExpressionSpec;

    // Single character tokens
    if (tokenStr.size() == 1) return determineSingleCharToken(tokenStr);

    if (regex_match(tokenStr, designEntityRegex)) return determineDesignEntityToken(tokenStr);
    if (regex_match(tokenStr, relRefRegex)) return determineRelRefToken(tokenStr);
    if (regex_match(tokenStr, attrNameRegex)) return TokenType::AttrName;

    // Check for IDENT and INTEGER last as they are more generic
    if (regex_match(tokenStr, IDENT_REGEX)) return TokenType::IDENT;
    if (regex_match(tokenStr, INTEGER_REGEX)) return TokenType::INTEGER;

    return TokenType::SyntaxError;
}

TokenType Tokenizer::determineClauseKeywordToken(const string& tokenStr) {
    if (!tokens.empty() && (isSynonym() || tokens.back().getType() == TokenType::SelectKeyword)) {
        return TokenType::IDENT;
    }
    // Mapping of clause keywords to their TokenType
    static const map<string, TokenType> keywordMap = {
            {"Select", TokenType::SelectKeyword},
            {"pattern", TokenType::PatternKeyword},
            {"such", TokenType::SuchKeyword},
            {"that", TokenType::ThatKeyword},
            {"with", TokenType::WithKeyword},
            {"and", TokenType::AndKeyword}
    };
    auto it = keywordMap.find(tokenStr);
    if (it != keywordMap.end()) return it->second;
    return TokenType::SyntaxError; // Should not reach here for valid clause keywords
}

TokenType Tokenizer::determineBooleanToken(const string& tokenStr) {
    // Ensures BOOLEAN is only recognized as such under specific conditions.
    if (!tokens.empty() && (isSynonym() || (tokens.back().getType() == TokenType::SelectKeyword && !isBooleanDeclared))) {
        isBooleanDeclared = true;
        return TokenType::BooleanKeyword;
    }
    return TokenType::IDENT; // If BOOLEAN is used in a context that does not fit its keyword use.
}

TokenType Tokenizer::determineDesignEntityToken(const string& tokenStr) {
    // Return TokenType::IDENT if the current token can be considered a synonym,
    // otherwise return the specific design entity type.
    if (!tokens.empty() && (isSynonym() || tokens.back().getType() == TokenType::SelectKeyword)) {
        return TokenType::IDENT;
    }
    return TokenType::DesignEntity;
}

TokenType Tokenizer::determineRelRefToken(const string& tokenStr) {
    // Similar to handling clause keywords, but for relationship references.
    static const map<string, TokenType> relRefMap = {
            {"Follows", TokenType::Follows},
            {"Follows*", TokenType::FollowsT},
            {"Parent", TokenType::Parent},
            {"Parent*", TokenType::ParentT},
            {"Uses", TokenType::Uses},
            {"Modifies", TokenType::Modifies},
            {"Next", TokenType::Next},
            {"Next*", TokenType::NextT},
            {"Calls", TokenType::Calls},
            {"Calls*", TokenType::CallsT},
            {"Affects", TokenType::Affects}
    };
    auto it = relRefMap.find(tokenStr);
    if (it != relRefMap.end()) return it->second;

    // Fallback if not matched, though all valid cases should be covered.
    return TokenType::IDENT;
}

TokenType Tokenizer::determineSingleCharToken(const string& tokenStr) {
    static const map<char, TokenType> singleCharMap = {
            {'(', TokenType::Lparenthesis},
            {')', TokenType::Rparenthesis},
            {';', TokenType::Semicolon},
            {',', TokenType::Comma},
            {'.', TokenType::Dot},
            {'=', TokenType::Equal},
            {'<', TokenType::LeftAngleBracket},
            {'>', TokenType::RightAngleBracket}
    };
    auto it = singleCharMap.find(tokenStr[0]);
    if (it != singleCharMap.end()) return it->second;
    return TokenType::SyntaxError; // Default case if it doesn't match known single chars
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