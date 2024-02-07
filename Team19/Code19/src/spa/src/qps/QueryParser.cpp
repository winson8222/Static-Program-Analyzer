// Include the Parser class header.
#include "QueryParser.h"
#include <stdexcept>

using namespace std;

// Constructor of the Parser class.
// Initializes the Parser with a vector of tokens to be parsed.
QueryParser::QueryParser(const vector<Token>& tokens) : tokens(tokens), currentTokenIndex(0) {}


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

bool QueryParser::throwError() {
    throw std::invalid_argument("incorrect grammar at: " + currentToken().getValue());
    return false;
}

// This should be validate grammar and not parse, change
bool QueryParser::parse() {

    parseDeclarations();
    parseSelectClause();
    if (currentTokenIndex == tokens.size() - 1) {
        return true;
    }
    advanceToken();

    // check if there is a such that or pattern clause with such that coming first
    if (match(TokenType::SuchKeyword)) {
        parseSuchThatClause();

        if (currentTokenIndex == tokens.size() - 1) {
            return true;
        }

        advanceToken();    
        parsePatternClause();
        
    } else {
        parsePatternClause();        
    }
    if (currentTokenIndex == tokens.size() - 1) {
        return true;
    }
}

// The parseDeclaration method of the Parser class.
// Contains logic to parse declarations.
// Currently a placeholder, actual implementation logic is needed.
void QueryParser::parseDeclarations() {
    int numberOfDeclarations = 0;
    while (!match(TokenType::SelectKeyword)) {
        parseDesignEntity();
        parseSynonym();

        while (match(TokenType::Comma)) {
            advanceToken();
            parseSynonym();
        }

        if (!match(TokenType::Semicolon) || !advanceToken()) {
            throwError();
        }
        numberOfDeclarations++;
    }

    if (numberOfDeclarations == 0) {
        throwError();
    }
    
}

void QueryParser::parseDesignEntity() {
    if (currentToken().getType() == TokenType::DesignEntity) {
        advanceToken();
    }
    else {
		throwError();
    }
}

void QueryParser::parseSynonym() {
    if (currentToken().getType() == TokenType::IDENT) {
        advanceToken();
    }
    else {
		throwError();
	}
    
}

// Check if the keyword Select is present
void QueryParser::parseSelectClause() {
    if (currentToken().getValue() != "Select") {
        throwError();
    }
    advanceToken();
    // check after select if it is a synonym
    if (!match(TokenType::IDENT)) {
        throwError();
    }

}

void QueryParser::parseSuchThatClause() {
    advanceToken();
    if (!match(TokenType::ThatKeyword)) {
        throwError();
    }
    advanceToken();

    return parseRelRef();
}

void QueryParser::parseRelRef() {
    if (isStmtRefStmtRef()) {
        advanceToken();
        parsestmtRefstmtRef();
    } else if (isUsesOrModifies()) {
        advanceToken();
        parseUsesOrModifies();
    } else {
        throwError();
    }

}



// parsing the stmtRef, check if is a synonym, INTEGER or Wildcard
void QueryParser::parseStmtRef() {
    
    if (match(TokenType::INTEGER)) {
        advanceToken();
    } else if (match(TokenType::Wildcard)) {
        advanceToken();
    } else {
        parseSynonym();
    }

}




// parsing the entRef, check if is a synonym, QuoutIDENT or Wildcard
void QueryParser::parseEntRef() {
    

    if (match(TokenType::QuoutIDENT)) {
        advanceToken();
    } else if (match(TokenType::Wildcard)) {
        advanceToken();
    } else {
        parseSynonym();
    }

}

// Parsing the ExpressionSpec,
void QueryParser::parseExpressionSpec() {

    if (match(TokenType::QuoutConst) || match(TokenType::QuoutIDENT)) {
        advanceToken();
    } else if (match(TokenType::Wildcard)) {
        advanceToken();
        if (match(TokenType::DoubleQuote)) {
            advanceToken();
            parseExpression();
            if (!match(TokenType::DoubleQuote)) {
                throwError();
            }
            advanceToken();
            if (match(TokenType::Wildcard)) {
                advanceToken();
            }
        }
    } else if (match(TokenType::DoubleQuote)) {
        advanceToken();
        parseExpression();
        if (!match(TokenType::DoubleQuote)) {
            throwError();
        }
        advanceToken();
    } else {
        throwError();
    }


}

void QueryParser::parseExpression() {
    parseTerm();

    while (match(TokenType::Operator)) {
        if (currentToken().getValue() == "+" || currentToken().getValue() == "-") {
            advanceToken();
        } else {
            throwError();
        }
        advanceToken();
        parseTerm();
    }
}

void QueryParser::parseTerm() {
    parseFactor();

    while (match(TokenType::Operator)) {
        if (currentToken().getValue() == "*" || currentToken().getValue() == "/"
        || currentToken().getValue() == "%") {
            advanceToken();
        } 
        parseFactor();
    }
}

void QueryParser::parseFactor() {
    if (match(TokenType::Lparenthesis)) {
        advanceToken();
        parseExpression();
        if (match(TokenType::Rparenthesis)) {
            advanceToken();
        }
        throwError();
    } else if (isVarName()) {
        advanceToken();
    } else if (isConstValue()) {
        advanceToken();
    } else {
        throwError();
    }
}

bool QueryParser::isConstValue() {
    if (match(TokenType::INTEGER)) {
        return true;
    } 
    return false;
    
}

bool QueryParser::isVarName() {
    if (match(TokenType::IDENT)) {
        return true;
    }
    return false;
}

void QueryParser::parsePatternClause() {
    // check if it is a syn-assign
    if (!match(TokenType::PatternKeyword)) {
        throwError();
    }
    advanceToken();
    if (!match(TokenType::IDENT)) {
        throwError();
    }

    advanceToken();
    if (!match(TokenType::Lparenthesis)) {
        throwError();
    }

    advanceToken();
    parseEntRef();
    if (!match(TokenType::Comma)) {
        throwError();
    }

    advanceToken();
    parseExpressionSpec();
    
    advanceToken();
    if (!match(TokenType::Rparenthesis)) {
        throwError();
    }
}

bool QueryParser::isStmtRefStmtRef() {
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

void QueryParser::parseUsesOrModifies() {
    if (match(TokenType::Lparenthesis)) {
        advanceToken();
    } else {
        throwError();
    }

    bool stmtRefSuccess = false;
    try {
        parseStmtRef();
        stmtRefSuccess = true;
    }
    catch (const std::exception& e) {
        //but no action is needed here because parseEntRef() will be attempted next
    }

    if (!stmtRefSuccess) {
        try {
            parseEntRef(); // If this fails, it throws an exception
        }
        catch (const std::exception& e) {
            throwError();
        }
    }

    if (match(TokenType::Comma)) {
        advanceToken();
    } else {
        throwError();
    }
    parseEntRef();
    if (!match(TokenType::Rparenthesis)) {
        throwError();
    }
}

void QueryParser::parsestmtRefstmtRef() {
    if (match(TokenType::Lparenthesis)) {
        advanceToken();
    } else {
        throwError();
    }

    // stmtRef
    parseStmtRef();

    //','
    if (match(TokenType::Comma)) {
        advanceToken();
    } else {
        throwError();
    }

    parseStmtRef();

    if (!match(TokenType::Rparenthesis)) {
        throwError();
    }
}




