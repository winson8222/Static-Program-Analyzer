#include "../../spa/src/qps/parser/Tokenizer.h"
#include <stdexcept>
#include <algorithm> // For std::remove
#include <string>    // For std::string

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

// Determines the type of a token based on its string representation.
// Returns the TokenType of the token.
TokenType Tokenizer::determineTokenType(const string& tokenStr) {
    // Logic to determine the type of the token.
    
    // Wildcard: A single underscore.
    if (tokenStr == "_") {
        return TokenType::Wildcard;
    }
    // ClauseKeyword: Specific clause keywords.
    else if (regex_match(tokenStr, regex("^(Select|pattern|such|that|with|and)$"))) {
        // The first case check if there is unconventional naming 
        // and avoids assigning wrong token type
        if (!tokens.empty() && (tokens.back().getType() == TokenType::SelectKeyword 
            || checkIfDeclaration() || tokens.back().getType() == TokenType::Lparenthesis 
            || tokens.back().getType() == TokenType::Comma)) {
            return TokenType::IDENT;
        }
        if (tokenStr == "Select") {
            return TokenType::SelectKeyword;
        }
        else if (tokenStr == "pattern") {
            lastRelationship = "pattern";
            return TokenType::PatternKeyword;
        }
        else if (tokenStr == "such") {
            lastRelationship = "such that";
            return TokenType::SuchKeyword;
        }
        else if (tokenStr == "that") {
            return TokenType::ThatKeyword;
        }
        else if (tokenStr == "with") {
            lastRelationship = "with";
            return TokenType::WithKeyword;
        }
        else if (tokenStr == "and") {
            return TokenType::AndKeyword;
        }
    }
    else if (tokenStr == "BOOLEAN") {
        return TokenType::BooleanKeyword;
    }
    // QuoutIDENT: An IDENT enclosed in double quotes.
    else if (regex_match(tokenStr, regex("^\"\\s*[a-zA-Z][a-zA-Z0-9]*\\s*\"$"))) {
        return TokenType::QuoutIDENT;
    }
    // QuoutConst: A constant enclosed in double quotes (for pattern matching).
    else if (regex_match(tokenStr, regex("^\"\\s*[0-9]+\\s*\"$"))) {
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
    else if (tokenStr == ".") {
        return TokenType::Dot;
    }
    else if (tokenStr == "=") {
        return TokenType::Equal;
    }
    else if (tokenStr == "<") {
        return TokenType::LeftAngleBracket;
    }
    else if (tokenStr == ">") {
        return TokenType::RightAngleBracket;
    }
    // DesignEntity: Specific keywords.
    else if (regex_match(tokenStr, regex("^(stmt|read|print|while|if|assign|variable|constant|procedure|call)$"))) {
        if (!tokens.empty() && (tokens.back().getType() == TokenType::SelectKeyword 
            || checkIfDeclaration() || tokens.back().getType() == TokenType::Lparenthesis 
            || tokens.back().getType() == TokenType::Comma)) {
            return TokenType::IDENT;
        }
        else {
            return TokenType::DesignEntity;
        }
    }
    // RelRef: Specific keywords.
    else if (regex_match(tokenStr, regex("^(Follows|Follows\\*|Parent|Parent\\*|Uses|Modifies|Next|Next\\*|Calls|Calls\\*)$"))) {
        if (!tokens.empty() && (tokens.back().getType() == TokenType::SelectKeyword 
            || checkIfDeclaration() || tokens.back().getType() == TokenType::Lparenthesis 
            || tokens.back().getType() == TokenType::Comma)) {
            return TokenType::IDENT;
        }
        else if (tokenStr == "Follows") {
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
        else if (tokenStr == "Next") {
            return TokenType::Next;
        }
        else if (tokenStr == "Next*") {
            return TokenType::NextT;
        }
        else if (tokenStr == "Calls") {
            return TokenType::Calls;
        }
        else if (tokenStr == "Calls*") {
            return TokenType::CallsT;
        }
    }
    // AttrName: Specific attributes.
    else if (regex_match(tokenStr, regex("^(procName|varName|value|stmt#)$"))) {
        if (!tokens.empty() && (tokens.back().getType() == TokenType::SelectKeyword
            || checkIfDeclaration() || tokens.back().getType() == TokenType::Lparenthesis
            || tokens.back().getType() == TokenType::Comma)) {
            return TokenType::IDENT;
        }
        else {
            return TokenType::AttrName;
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
    else if (regex_match(tokenStr, regex("^[+\\-*/%&|!~^]$"))) {
        return TokenType::Operator;
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