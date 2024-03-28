#pragma once

#include <string>
#include <vector>
#include <regex>
#include <map>
#include <functional>
#include "qps/parser/Token.h"

// The Tokenizer class is used for converting a string query into tokens.
class Tokenizer {
public:
    // Constructor for the Tokenizer class.
    // It takes a constant reference to a string as input, representing the query to be tokenized.
    // The 'explicit' keyword prevents implicit conversions from string to Tokenizer.
    explicit Tokenizer(const std::string& query);

    // This method tokenizes the stored query and returns a vector of Token objects.
    vector<Token> tokenize();

    std::string removeSpaces(std::string str);

    std::map<std::string, TokenType> clauseTypeMap = {
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
            {"Affects", TokenType::Affects},
    };

    std::map<std::string, TokenType> signMap = {
            {"(", TokenType::Lparenthesis},
            {")", TokenType::Rparenthesis},
            {";", TokenType::Semicolon},
            {",", TokenType::Comma},
            {".", TokenType::Dot},
            {"=", TokenType::Equal},
            {"<", TokenType::LeftAngleBracket},
            {">", TokenType::RightAngleBracket},
            // Add other mappings as necessary...
    };


    const std::map<std::string, std::function<TokenType()>> tokenFunctionMap = {
            {"Select", [this]() -> TokenType {
                return TokenType::SelectKeyword;
            }},
            {"pattern", [this]() -> TokenType {
                lastRelationship = "pattern";
                return TokenType::PatternKeyword;
            }},
            {"such", [this]() -> TokenType {
                // Assuming you want to concatenate "such that" when "that" comes next,
                // this will initially set it to "such". You might adjust based on your parsing logic.
                lastRelationship = "such";
                return TokenType::SuchKeyword;
            }},
            {"that", [this]() -> TokenType {
                if (lastRelationship == "such") {
                    lastRelationship += " that";
                }
                return TokenType::ThatKeyword;
            }},
            {"with", [this]() -> TokenType {
                lastRelationship = "with";
                return TokenType::WithKeyword;
            }},
            {"and", [this]() -> TokenType {
                return TokenType::AndKeyword;
            }},
            {"not", [this]() -> TokenType {
                return TokenType::NotKeyword;
            }},
    };

private:
    // Private member variable to store the query string.
    std::string query;

    // A regular expression object used to identify tokens in the query string.
    std::regex tokenRegex;

    // string the represents the last relationship used (such that, with, pattern)
    // it is used to explicitly state the relationship instead of "and"
    std::string lastRelationship;

    std::string nextToken;

    // A private method that splits the query into tokens based on the regular expression.
    // Returns a vector of Token objects.
    void splitQuery();

    vector<Token> tokens;
    bool isBooleanDeclared = false; //special case for boolean because it is treated as a synonym after selection if it was declared

    // A private method to determine the type of token given its string representation.
    // Returns the TokenType of the token which is useful in the QueryParser.
    TokenType determineTokenType(const std::string& tokenStr);
    // helper fn for determineTokenType
    TokenType determineQuoutToken(const std::string& tokenStr);
    TokenType determineClauseKeywordToken(const std::string& tokenStr);
    TokenType determineSingleCharToken(const std::string& tokenStr);
    TokenType determineBooleanToken(const std::string& tokenStr);
    TokenType determineDesignEntityToken(const std::string& tokenStr);
    TokenType determineRelRefToken(const std::string& tokenStr);
    TokenType determineAttrNameToken(const std::string& tokenStr);

    bool checkIfDeclaration();
    bool isSynonym();
    static bool isSyntaxError(TokenType tokenType);
};
