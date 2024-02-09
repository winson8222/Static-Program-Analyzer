// Include the Parser class header.
#include "../../spa/src/qps/QueryParser.h"
#include <stdexcept>
#include <iostream>

using namespace std;

// Constructor of the QueryParser class.
// Initializes the QueryParser with a vector of Token objects to be parsed.
QueryParser::QueryParser(const vector<Token>& tokens) : tokens(tokens), currentTokenIndex(0), parsingResult() {}

// Parses the entire query.
// Processes declarations, select clause, and optional such that and pattern clauses.
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

// Parses a synonym in the query.
void QueryParser::parseSynonym(string designEntity) {
    ensureToken(TokenType::IDENT);


    // check if the token value is declared as synonyms in any of the set
    if (!parsingResult.getDeclaredSynonym(currentToken().getValue()).empty()) {
        throwSemanticError();
    }
    parsingResult.addDeclaredSynonym(currentToken().getValue(), designEntity);
    advanceToken();

}

// parses the design entity in the query.
void QueryParser::parseDesignEntity() {;
    string designEntity = currentToken().getValue();


    advanceToken();
    parseSynonym(designEntity);

    while (match(TokenType::Comma)) {
        advanceToken();
        parseSynonym(designEntity);
    }

    ensureToken(TokenType::Semicolon);
    advanceToken();
}

// Parses declarations in the query.
// Processes design entities and their synonyms, and ensures correct syntax with semicolons.
void QueryParser::parseDeclarations() {
    int numberOfDeclarations = 0;
    while (!match(TokenType::SelectKeyword)) {

        parseDesignEntity();

        numberOfDeclarations++;
    }

    if (numberOfDeclarations == 0) {
        throwGrammarError();
    }
    
}






// Parses the select clause in the query.
// Checks for the 'Select' keyword and ensures the following token is a valid identifier.
void QueryParser::parseSelectClause() {
    if (currentToken().getValue() != "Select") {
        throwGrammarError();
    }
    advanceToken();
    ensureToken(TokenType::IDENT);
    //check if the token value is declared as synonyms in any of the set
if (parsingResult.getDeclaredSynonym(currentToken().getValue()).empty()) {
        throwSemanticError();
    }



}




// Parses the 'such that' clause in the query.
// Ensures the correct syntax and calls the function to process relation references.
void QueryParser::parseSuchThatClause() {
    advanceToken();
    ensureToken(TokenType::ThatKeyword);
    advanceToken();

    return parseRelRef();
}

// Parses relation references in a 'such that' clause.
// Determines the type of relation and calls the appropriate parsing function.
void QueryParser::parseRelRef() {
    if (isStmtRefStmtRef()) {
        advanceToken();
        parsestmtRefstmtRef();
    } else if (isUsesOrModifies()) {
        advanceToken();
        parseUsesOrModifies();
    } else {
        throwGrammarError();
    }

}

// Checks if the current context is a statement reference to statement reference relation.
bool QueryParser::isStmtRefStmtRef() {
    if (match(TokenType::Parent) || match(TokenType::ParentT) ||
        match(TokenType::Follows) || match(TokenType::FollowsT)) {
        return true;

    }
    return false;
}

// Checks if the current context is a 'Uses' or 'Modifies' relation.
bool QueryParser::isUsesOrModifies() {
    if (match(TokenType::Uses) || match(TokenType::Modifies)) {
        return true;
    }
    return false;
}

// Parses a 'Uses' or 'Modifies' relation in the query.
// Ensures correct syntax and processes statement and entity references.
void QueryParser::parseUsesOrModifies() {
    if (match(TokenType::Lparenthesis)) {
        advanceToken();
    }
    else {
        throwGrammarError();
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
            throwGrammarError();
        }
    }

    if (match(TokenType::Comma)) {
        advanceToken();
    }
    else {
        throwGrammarError();
    }
    parseEntRef();
    ensureToken(TokenType::Rparenthesis);
}

// Parses a statement reference to statement reference relation.
// Ensures correct syntax and processes multiple statement references.
void QueryParser::parsestmtRefstmtRef() {
    if (match(TokenType::Lparenthesis)) {
        advanceToken();
    }
    else {
        throwGrammarError();
    }

    // stmtRef
    parseStmtRef();

    //','
    if (match(TokenType::Comma)) {
        advanceToken();
    }
    else {
        throwGrammarError();
    }

    parseStmtRef();

    ensureToken(TokenType::Rparenthesis);
}

// Parses a statement reference in the query.
// Handles different types of statement references like integer, wildcard, or synonym.
void QueryParser::parseStmtRef() {
    
    if (match(TokenType::INTEGER)) {
        advanceToken();
    } else if (match(TokenType::Wildcard)) {
        advanceToken();
    } else {
        parseStmtSynonyms();
    }

}

// Parses an entity reference in the query.
// Handles different types of entity references like quoted identifier, wildcard, or synonym.
void QueryParser::parseEntRef() {
    

    if (match(TokenType::QuoutIDENT)) {
        advanceToken();
    } else if (match(TokenType::Wildcard)) {
        advanceToken();
    } else {
        parseVarSynonyms();
    }

}




// Parses the pattern clause in the query.
// Ensures the correct syntax and processes entity references and expression specifications.
void QueryParser::parsePatternClause() {

    ensureToken(TokenType::PatternKeyword);
    advanceToken();
    // check if it is a syn-assign
    parseAssignSynonyms();

    ensureToken(TokenType::Lparenthesis);

    advanceToken();
    parseEntRef();
    ensureToken(TokenType::Comma);

    advanceToken();
    parseExpressionSpec();

    ensureToken(TokenType::Rparenthesis);
}

// Parses the expression specification in the query.
// Handles different forms of expressions like quoted constants, wildcards, or quoted expressions.
void QueryParser::parseExpressionSpec() {

    if (match(TokenType::QuoutConst) || match(TokenType::QuoutIDENT)) {
        advanceToken();
    } else if (match(TokenType::Wildcard)) {
        advanceToken();
        if (match(TokenType::DoubleQuote)) {
            parseQuotedExpression();
            ensureToken(TokenType::Wildcard);
            advanceToken();
        }
        
    } else if (match(TokenType::DoubleQuote)) {
        parseQuotedExpression();
    } else {
        throwGrammarError();
    }


}

// Parses a quoted expression in the query.
// Processes the expression enclosed in double quotes.
void QueryParser::parseQuotedExpression() {
    advanceToken();
    parseExpression();
    ensureToken(TokenType::DoubleQuote);
    advanceToken();
    
}

// Parses an expression in the query.
// Processes terms and operators within the expression.
void QueryParser::parseExpression() {
    parseTerm();

    while (match(TokenType::Operator)) {
        if (currentToken().getValue() == "+" || currentToken().getValue() == "-") {
            advanceToken();
        } else {
            throwGrammarError();
        }
        advanceToken();
        parseTerm();
    }
}

// Parses a term in an expression.
// Processes factors and operators within the term.
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

// Parses a factor in a term.
// Handles parentheses, variable names, and constant values.
void QueryParser::parseFactor() {
    if (match(TokenType::Lparenthesis)) {
        advanceToken();
        parseExpression();
        if (match(TokenType::Rparenthesis)) {
            advanceToken();
        }
        throwGrammarError();
    } else if (isVarName()) {
        advanceToken();
    } else if (isConstValue()) {
        advanceToken();
    } else {
        throwGrammarError();
    }
}

// Checks if the current token is a constant value.
bool QueryParser::isConstValue() {
    return match(TokenType::INTEGER);
}

// Checks if the current token is a variable name.
bool QueryParser::isVarName() {
    return match(TokenType::IDENT);
}

// Returns a constant reference to the current Token being parsed.
const Token& QueryParser::currentToken() const {
    return tokens[currentTokenIndex];
}

// Advances to the next token in the token sequence.
// Returns true if advancement is successful, false if it reaches the end of the token sequence.
bool QueryParser::advanceToken() {
    if (currentTokenIndex < tokens.size() - 1) {
        ++currentTokenIndex;
        return true;
    }
    throwGrammarError();
}

// Checks if the current token matches a given TokenType.
// Advances to the next token and returns true if it matches.
// Returns false if there is no match.
bool QueryParser::match(TokenType type) {
    if (currentToken().getType() == type) {
        return true;
    }
    return false;
}

// Ensures the next token matches the expected TokenType.
// Throws an error if the token does not match the expected type.
void QueryParser::ensureToken(TokenType expected) {
    if (!match(expected)) {
        throwGrammarError();
    }
}

// Throws a standard invalid_argument exception with a custom error message for grammar error.
bool QueryParser::throwGrammarError() {
    throw std::invalid_argument("incorrect grammar at: " + currentToken().getValue());

}

// Throws a standard invalid_argument exception with a custom error message for semantic error.
bool QueryParser::throwSemanticError() {
    throw std::invalid_argument("semantic error at: " + currentToken().getValue());
}

// Parses a variable synonym in the query.
void QueryParser::parseVarSynonyms() {
    ensureToken(TokenType::IDENT);
    // check if the token value is declared as variable synonyms in any of the set
    if (parsingResult.getDeclaredSynonym(currentToken().getValue()) != "variable") {
        throwSemanticError();
    }
    advanceToken();

}

// Parses a statement synonym in the query.
void QueryParser::parseStmtSynonyms() {
    ensureToken(TokenType::IDENT);
    if (parsingResult.getDeclaredSynonym(currentToken().getValue()) != "stmt") {
        throwSemanticError();
    }
    advanceToken();
}


// Parses an assignment synonym in the query.
void QueryParser::parseAssignSynonyms() {
    ensureToken(TokenType::IDENT);
    if (parsingResult.getDeclaredSynonym(currentToken().getValue()) != "assign") {
        throwSemanticError();
    }
    advanceToken();
}



ParsingResult QueryParser::getParsingResult() const {
    return parsingResult;
}

