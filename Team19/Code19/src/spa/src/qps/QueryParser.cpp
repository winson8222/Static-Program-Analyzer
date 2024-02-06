// Include the Parser class header.
#include "QueryParser.h"


using namespace std;

// Constructor of the Parser class.
// Initializes the Parser with a vector of tokens to be parsed.
QueryParser::QueryParser(const vector<Token>& tokens) : tokens(tokens), currentTokenIndex(0) {}



//bool QueryParser::validateGrammar() {
// Orchestrates the parsing process by calling specific parsing methods for different parts of the input.
// Returns true if all parsing is successful, false otherwise.
// Will probably make it work with the Query Evaluator so that it will give the synonyms and 
// the relationships that should be passed to the PKB


// This should be validate grammar and not parse, change
bool QueryParser::parse() {

    int numberOfDeclarations = 0;
    while (!match(TokenType::SelectKeyword)) {
        if (!parseDeclaration()) {
            return false;
        } else {
            numberOfDeclarations++;
        }

    }
    if (numberOfDeclarations == 0) {
        return false;
    }

    // check if the Select Clause is correctly matched with a synonym
    if (!parseSelectClause()) {
        return false;
    }

    if (currentTokenIndex == tokens.size() - 1) {
        return true;
    }


    // check if there is a such that or pattern clause with such that coming first
    if (match(TokenType::SuchKeyword)) {
        advanceToken();
        if (match(TokenType::ThatKeyword)) {
            advanceToken();
            if (!parseSuchThatClause()) {
                return false;
            }
            if (currentTokenIndex == tokens.size() - 1) {
                return true;
            } else if (match(TokenType::PatternKeyword)) {
                advanceToken();
                if (!parsePatternClause()) {
                    return false;
                }
            } else {
                return false;
            }
            if (currentTokenIndex == tokens.size() - 1) {
                return true;
            }
        }
        return false;
    } else if (match(TokenType::PatternKeyword)) {
        advanceToken();
        if (!parsePatternClause()) {
            return false;
        }
    } else {
        return false;
    }
    if (currentTokenIndex == tokens.size() - 1) {
        return true;
    }
}



// Check if the keyword Select is present
bool QueryParser::parseSelectClause() {
    if (currentToken().getValue() != "Select") {
        return false;
    }
    advanceToken();
    // check after select if it is a synonym
    if (match(TokenType::IDENT)) {
        advanceToken();
        return true;
    } else {
        return false;
    }

}



bool QueryParser::parseDesignEntity() {
    if (currentToken().getType() == TokenType::DesignEntity) {
        advanceToken();
        return true;
    }
    return false;
}
// The parseDeclaration method of the Parser class.
// Contains logic to parse declarations.
// Currently a placeholder, actual implementation logic is needed.
bool QueryParser::parseDeclaration() {
    if (!parseDesignEntity()) {
        return false;
    }

    if (!parseSynonym()) {
        return false;
    }

    while (match(TokenType::Comma)) {
        advanceToken();
        if (!parseSynonym()) {
            return false;
        }
    }

    if(match(TokenType::Semicolon)) {
        advanceToken();
        return true;
    }


    return false;
}

bool QueryParser::parseSynonym() {
    if (currentToken().getType() == TokenType::IDENT) {
        advanceToken();
        return true;
    }
    return false;
}



bool QueryParser::parseSuchThatClause() {
    if (!parseRelRef()) {
        return false;
    }
    return true;
}

bool QueryParser::parseRelRef() {
    if (isstmtRefstmtRef()) {
        advanceToken();
        if (!parsestmtRefstmtRef()) {
            return false;
        }
        return true;
    } else if (isUsesOrModifies()) {
        advanceToken();
        if (!parseUsesOrModifies()) {
            return false;
        }
        return true;
    } else {
        return false;
    }

}



// parsing the stmtRef, check if is a synonym, INTEGER or Wildcard
bool QueryParser::parseStmtRef() {
    if (parseSynonym()) {

        return true;
    }

    if (match(TokenType::INTEGER)) {
        advanceToken();
        return true;
    }

    if (match(TokenType::Wildcard)) {
        advanceToken();
        return true;
    }

    return false;

}




// parsing the entRef, check if is a synonym, QuoutIDENT or Wildcard
bool QueryParser::parseEntRef() {
    if (parseSynonym()) {
        return true;
    }

    if (match(TokenType::QuoutIDENT)) {
        advanceToken();
        return true;
    }

    if (match(TokenType::Wildcard)) {
        advanceToken();
        return true;
    }

    return false;

}

// Parsing the ExpressionSpec,
bool QueryParser::parseExpressionSpec() {

    if (match(TokenType::QuoutConst) || match(TokenType::QuoutIDENT)) {
        advanceToken();
        return true;
    }

    if (match(TokenType::Wildcard)) {
        advanceToken();
        if (match(TokenType::DoubleQuote)) {
            advanceToken();
            if (!parseExpression()) {
                return false;
            }
            if (!match(TokenType::DoubleQuote)) {
                return false;
            }
            advanceToken();
            if (match(TokenType::Wildcard)) {
                advanceToken();
                return true;
            }
            return false;
        } else {
            return true;
        }
    } else if (match(TokenType::DoubleQuote)) {
        advanceToken();
        if (!parseExpression()) {
            return false;
        }
        if (!match(TokenType::DoubleQuote)) {
            return false;
        }
        advanceToken();
        return true;
    } else {
        return false;
    }


}

bool QueryParser::parseExpression() {
    if (!parseTerm()) {
        return false;
    }

    while (match(TokenType::Operator)) {
        if (currentToken().getValue() == "+" || currentToken().getValue() == "-") {
            advanceToken();
        } else {
            return false;
        }
        advanceToken();
        if (!parseTerm()) {
            return false;
        }
    }

    return true;
}

bool QueryParser::parseTerm() {
    if (!parseFactor()) {
        return false;
    }

    while (match(TokenType::Operator)) {
        if (currentToken().getValue() == "*" || currentToken().getValue() == "/"
        || currentToken().getValue() == "%") {
            advanceToken();
        } else {
            return false;
        }
        if (!parseFactor()) {
            return false;
        }
    }
    return true;
}

bool QueryParser::parseFactor() {
    if (match(TokenType::Lparenthesis)) {
        advanceToken();
        if (!parseExpression()) {
            return false;
        }
        if (match(TokenType::Rparenthesis)) {
            advanceToken();
            return true;
        }
        return false;
    } else if (parseVarName()) {
        return true;
    } else if (parseConstValue()) {
        return true;
    } else {
        return false;
    }
}

bool QueryParser::parseConstValue() {
    if (match(TokenType::INTEGER)) {
        advanceToken();
        return true;
    } else {
        return false;
    }
}

bool QueryParser::parseVarName() {
    if (match(TokenType::IDENT)) {
        advanceToken();
        return true;
    }
    return false;
}

bool QueryParser::parsePatternClause() {
    // check if it is a syn-assign
    if (!match(TokenType::IDENT)) {
        return false;
    }

    advanceToken();
    if (!match(TokenType::Lparenthesis)) {
        return false;
    }
    advanceToken();
    if (!parseEntRef()) {
        return false;
    }
    if (!match(TokenType::Comma)) {
        return false;
    }
    advanceToken();
    // for now expression == entRef first
    if (!parseExpressionSpec()) {
        return false;
    }
    advanceToken();
    if (!match(TokenType::Rparenthesis)) {
        return false;
    }

    return true;
}

// The currentToken method of the Parser class.
// Returns a constant reference to the current Token being parsed.
const Token& QueryParser::currentToken() const {
    return tokens[currentTokenIndex];
}

// The advanceToken method of the Parser class.
// Advances to the next token in the sequence.
// Returns true if advancement is successful, false if it reaches the end of the tokens.
bool QueryParser::advanceToken() {
    if (currentTokenIndex < tokens.size() - 1) {
        ++currentTokenIndex;
        return true;
    }
    return false;
}

// Checks if the current token matches a given TokenType.
// If it matches, advances to the next token and returns true.
// This should be used in conjunction with Tokenizer::determineTokenType.
// Returns false if there is no match.
bool QueryParser::match(TokenType type) {
    if (currentToken().getType() == type) {

        return true;
    }
    return false;
}

bool QueryParser::isstmtRefstmtRef() {
    if (match(TokenType::Parent) || match(TokenType::ParentT) ||
    match(TokenType::Follows) || match(TokenType::FollowsT)) {
        return true;

    }
    return false;
}

bool QueryParser::isUsesOrModifies() {
    if (match(TokenType::Uses) || match(TokenType::Modifies)) {
        return true;
    }
    return false;
}

bool QueryParser::parseUsesOrModifies() {
    if (match(TokenType::Lparenthesis)) {
        advanceToken();
    } else {
        return false;
    }

    if (!parseStmtRef() && !parseEntRef()) {
        return false;
    }
    if (match(TokenType::Comma)) {
        advanceToken();
    } else {
        return false;
    }
    if (!parseEntRef()) {
        return false;
    }
    if (match(TokenType::Rparenthesis)) {
        advanceToken();
    } else {
        return false;
    }
    return true;
}

bool QueryParser::parsestmtRefstmtRef() {
    if (match(TokenType::Lparenthesis)) {
        advanceToken();
    } else {
        return false;
    }

    // stmtRef
    if (!parseStmtRef()) {
        return false;
    }


    //','
    if (match(TokenType::Comma)) {
        advanceToken();
    } else {
        return false;
    }

    if (!parseStmtRef()) {
        return false;
    }

    if (match(TokenType::Rparenthesis)) {
        advanceToken();
    } else {
        return false;
    }
    return true;
}




