// Include the parser class header.
#include "../../spa/src/qps/parser/QueryParser.h"
#include <stdexcept>
#include <iostream>

using namespace std;

// Constructor of the QueryParser class.
// Initializes the QueryParser with a vector of Token objects to be parsed.
QueryParser::QueryParser(const vector<Token>& tokens) : tokens(tokens), currentTokenIndex(0), parsingResult() {}

// Parses the entire query and validate the syntax and semantics, stop parsing when there is an error.
// Processes declarations, select clause, and optional such that and pattern clauses.
ParsingResult QueryParser::parse() {
    try {
        if (match(TokenType::DesignEntity)) {
            parseDeclarations();
        }
        parseSelectClause();
        if (currentTokenIndex == tokens.size() - 1) {
            return parsingResult;
        }
        advanceToken();

        while (currentTokenIndex <= tokens.size() - 1) {
            // check if there is a such that or pattern clause with such that coming first
            if (match(TokenType::SuchKeyword) || (match(TokenType::AndKeyword) && currentToken().getValue() == "such that")) {
                if (match(TokenType::SuchKeyword)) {
                    advanceToken();
                    ensureToken(TokenType::ThatKeyword);
                }

                parseSuchThatClause();
                if (currentTokenIndex == tokens.size() - 1) {
                    return parsingResult;
                }
                advanceToken();
            }
            else if (match(TokenType::PatternKeyword) || (match(TokenType::AndKeyword) && currentToken().getValue() == "pattern")) {
                parsePatternClause();

                if (currentTokenIndex == tokens.size() - 1) {
                    return parsingResult;
                }

                advanceToken();

            }
            else if (match(TokenType::WithKeyword) || (match(TokenType::AndKeyword) && currentToken().getValue() == "with")) {
                parseWithClause();

                if (currentTokenIndex == tokens.size() - 1) {
                    return parsingResult;
                }

                advanceToken();
            }
            else {
                throwGrammarError();
            }
        }

        if (currentTokenIndex == tokens.size() - 1) {
            return parsingResult;
        }
        throwGrammarError();
        return parsingResult;
    }
    catch (const std::invalid_argument& e) {
        // Handle the exception
        parsingResult.setErrorMessage(e.what());
        return parsingResult;
    }

}

// Parses declarations in the query.
// Processes design entities and their synonyms, and ensures correct syntax with semicolons.
void QueryParser::parseDeclarations() {
    int numberOfDeclarations = 0;
    while (!match(TokenType::SelectKeyword)) {
        parseDesignEntity();
        string assignmentType = currentToken().getValue();
        advanceToken();

        parseSynonym();
        parsingResult.addDeclaredSynonym(currentToken().getValue(), assignmentType);
        advanceToken();

        while (match(TokenType::Comma)) {
            advanceToken();
            parseSynonym();
            // check if the token value is declared as synonyms in any of the set
            if (!parsingResult.getDeclaredSynonym(currentToken().getValue()).empty()) {
                throwSemanticError();
            }
            parsingResult.addDeclaredSynonym(currentToken().getValue(), assignmentType);
            advanceToken();
        }

        ensureToken(TokenType::Semicolon);
        advanceToken();

        numberOfDeclarations++;
    }

    if (numberOfDeclarations == 0) {
        throwGrammarError();
    }
    
}

// Parses a design entity in the query.
// Ensures the current token is a design entity and advances the token.
void QueryParser::parseDesignEntity() {
    if (currentToken().getType() != TokenType::DesignEntity) {
        throwGrammarError();
    }
}


// Parses a synonym in the query.
// Ensures the current token is an identifier and advances the token.
void QueryParser::parseSynonym() {
    // check if it is an ident and if the synonym is already declared
    ensureToken(TokenType::IDENT);
}



// Parses the select clause in the query.
// Checks for the 'Select' keyword and ensures the following token is a valid identifier.
void QueryParser::parseSelectClause() {
    if (currentToken().getValue() != "Select") {
        throwGrammarError();
        
    }
    advanceToken();
    if (match(TokenType::LeftAngleBracket)) {
        advanceToken();
        while (!match(TokenType::RightAngleBracket)) {
            currentSuchThatToken = currentToken();
            size_t startIndex = currentTokenIndex;
            
            if (peekNextToken(TokenType::Dot)) {
                parseAttrRef();
            }
            else {
                ensureToken(TokenType::IDENT);
            }
            
            string concatenatedTokens;
            for (size_t i = startIndex; i <= currentTokenIndex; ++i) {
                concatenatedTokens += tokens[i].getValue();
            }
            parsingResult.setRequiredSynonym(concatenatedTokens);
            if (parsingResult.getDeclaredSynonym(currentSuchThatToken.getValue()).empty()) {
                throwSemanticError();
                
            }
            advanceToken();
            if (match(TokenType::RightAngleBracket)) {
                break;
            }
            ensureToken(TokenType::Comma);
            advanceToken();
        }
    }
    else {
        currentSuchThatToken = currentToken();
        size_t startIndex = currentTokenIndex;
        if (tokens.size() > currentTokenIndex + 1 && peekNextToken(TokenType::Dot)) {
            parseAttrRef();
        }
        else {
            if (!match(TokenType::IDENT)) {
                ensureToken(TokenType::BooleanKeyword);
            }
        }
        string concatenatedTokens;
        for (size_t i = startIndex; i <= currentTokenIndex; ++i) {
            concatenatedTokens += tokens[i].getValue();
        }
        parsingResult.setRequiredSynonym(concatenatedTokens);
        if (parsingResult.getDeclaredSynonym(currentSuchThatToken.getValue()).empty() && currentSuchThatToken.getValue() != "BOOLEAN") {
            throwSemanticError();
        }
    }
   
}


// Parses the 'such that' clause in the query.
// Ensures the correct syntax and calls the function to process relation references.
void QueryParser::parseSuchThatClause() {
    SuchThatClause clause;
    
    advanceToken();
    parseRelRef(clause);
    parsingResult.addSuchThatClause(clause);
}

// Parses relation references in a 'such that' clause.
// Determines the type of relation and calls the appropriate parsing function.
void QueryParser::parseRelRef(SuchThatClause& clause) {
    if (isStmtRefStmtRef()) {
        clause.setRelationship(currentToken());
        advanceToken();
        parseStmtRefStmtRef(clause);
    } else if (isUsesOrModifies()) {
        parseUsesOrModifies(clause);
    } else {
        throwGrammarError();
    }

}

// Checks if the current context is a statement reference to statement reference relation.
bool QueryParser::isStmtRefStmtRef() {
    if (match(TokenType::Parent) || match(TokenType::ParentT) ||
        match(TokenType::Follows) || match(TokenType::FollowsT) ||
        match(TokenType::Calls) || match(TokenType::CallsT) ||
        match(TokenType::Next) || match(TokenType::NextT)) {
        currentSuchThatToken = currentToken();
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
// set the Token type for the such that clause relationship more specifically
void QueryParser::parseUsesOrModifies(SuchThatClause& clause) {
    // need to differentiate between usesS/UsesP and modifiesS/ModifiesP
    currentSuchThatToken = currentToken();


    advanceToken();
    if (match(TokenType::Lparenthesis)) {
        advanceToken();
    }
    else {
        throwGrammarError();
    }

    if (match(TokenType::Wildcard)) {
        throwSemanticError();
    }




    try {
        parseStmtRef(); // Attempt to parse a statement reference
        // If parseStmtRef succeeds, control continues here
        if (currentSuchThatToken.getType() == TokenType::Uses) {
            currentSuchThatToken.setType(TokenType::UsesS);
        }
        else {
            currentSuchThatToken.setType(TokenType::ModifiesS);
        }
        clause.setRelationship(currentSuchThatToken);
        clause.setFirstParam(currentToken());
        advanceToken();
    }
    catch (const std::exception& e) { // If parseStmtRef fails, it will enter this catch block
        try {
            parseEntRef(); // Attempt to parse an entity reference
            // If parseEntRef succeeds, control continues here
            if (currentSuchThatToken.getType() == TokenType::Uses) {
                currentSuchThatToken.setType(TokenType::UsesP);
            }
            else {
                currentSuchThatToken.setType(TokenType::ModifiesP);
            }
            clause.setRelationship(currentSuchThatToken);
            clause.setFirstParam(currentToken());
            advanceToken();
        }
        catch (const std::exception& e) {
            // If both parseStmtRef and parseEntRef fail, it will enter this catch block
            throwGrammarError(); // Throws a grammar error if both parsing attempts fail
        }
    }





    if (match(TokenType::Comma)) {
        advanceToken();
    }
    else {
        throwGrammarError();
    }

    parseEntRef();
    clause.setSecondParam(currentToken());
    advanceToken();
    ensureToken(TokenType::Rparenthesis);
}

// Parses a statement reference to statement reference relation.
// Ensures correct syntax and processes multiple statement references.
void QueryParser::parseStmtRefStmtRef(SuchThatClause& clause) {
    if (match(TokenType::Lparenthesis)) {
        advanceToken();
    } else {
        throwGrammarError();
    }

    // stmtRef
    parseStmtRef();
    clause.setFirstParam(currentToken());
    advanceToken();


    //','
    if (match(TokenType::Comma)) {
        advanceToken();
    }
    else {
        throwGrammarError();
    }

    parseStmtRef();
    clause.setSecondParam(currentToken());
    advanceToken();

    ensureToken(TokenType::Rparenthesis);
}

// Parses a statement reference in the query.
void QueryParser::parseStmtRef() {
    if (match(TokenType::Wildcard)) {
        return;
    } else if (match(TokenType::INTEGER)) {
        if(checkValidStmtNum()) {
            return;
        }
        throwSemanticError();
    } else {
        parseStmtSynonyms();
    }


}

// Parses an entity reference in the query.
// Handles different types of entity references like quoted identifier, wildcard, or synonym.
void QueryParser::parseEntRef() {
    if (match(TokenType::QuoutIDENT) || match(TokenType::Wildcard)) {
        return;
    } else {
        parseVarSynonyms();
    }

}




// Parses the pattern clause in the query.
// Ensures the correct syntax and processes entity references and expression specifications.
void QueryParser::parsePatternClause() {
    PatternClause clause;
    ensureToken(TokenType::PatternKeyword);
    advanceToken();
    // check if it is a syn-assign
    ensureToken(TokenType::IDENT);
    clause.setRelationship(currentToken());
    parseAssignSynonyms();


    ensureToken(TokenType::Lparenthesis);

    advanceToken();
    parseEntRef();
    clause.setFirstParam(currentToken());
    

    advanceToken();
    ensureToken(TokenType::Comma);

    advanceToken();
    

    string patternType = parsingResult.getDeclaredSynonym(clause.getRelationship().getValue());
    if (patternType == "if") {
        ensureToken(TokenType::Wildcard);
        clause.setSecondParam(currentToken());
        advanceToken();
        ensureToken(TokenType::Comma);
        advanceToken();
        ensureToken(TokenType::Wildcard);
        clause.setThirdParam(currentToken());
    }
    else if (patternType == "while") {
        ensureToken(TokenType::Wildcard);
        clause.setSecondParam(currentToken());
        advanceToken();
        ensureToken(TokenType::Comma);
    }
    else {
        // This is a rudimentary approach to tokenize ExpressionSpec, probably change later
        // Store the current token index before parsing the expression spec
        size_t startIndex = currentTokenIndex;
        parseExpressionSpec();

        // Concatenate all token values from startIndex to the current index
        string concatenatedTokens;
        for (size_t i = startIndex; i <= currentTokenIndex; ++i) {
            concatenatedTokens += tokens[i].getValue();
        }
        clause.setSecondParam(Token(TokenType::ExpressionSpec, concatenatedTokens));
    }

    advanceToken();
    ensureToken(TokenType::Rparenthesis);
    parsingResult.addPatternClause(clause);
}

// Parses the expression specification in the query.
// Handles different forms of expressions like quoted constants, wildcards, or quoted expressions.
void QueryParser::parseExpressionSpec() {

    if (match(TokenType::QuoutConst) || match(TokenType::QuoutIDENT) || match(TokenType::ExpressionSpec)) {
        return;
    } else if (match(TokenType::Wildcard)) {
        if (peekNextToken(TokenType::Rparenthesis)) {
            return;
        }
        advanceToken();




        if (!match(TokenType::QuoutIDENT) && !match(TokenType::QuoutConst) && !match(TokenType::ExpressionSpec)) {
            throwGrammarError();
        }

        advanceToken();

        ensureToken(TokenType::Wildcard);

    } else if (match(TokenType::QuoutIDENT)) {
        return parseQuotedExpression();
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
        ensureToken(TokenType::Rparenthesis);
        advanceToken();
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
void QueryParser::advanceToken() {
    if (currentTokenIndex < tokens.size() - 1) {
        ++currentTokenIndex;
    }
    else {
        throwIncompleteQueryError();
    }
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
void QueryParser::throwGrammarError() {
    throw std::invalid_argument("SyntaxError");
}

// Throws a standard invalid_argument exception with a custom error message for semantic error.
void QueryParser::throwSemanticError() {
    throw std::invalid_argument("SemanticError");
}

// Throws a standard invalid_argument exception with a custom error message for incomplete error.
void QueryParser::throwIncompleteQueryError() {
    throw std::invalid_argument("Incomplete Query");
}

// Parses a variable synonym in the query.
void QueryParser::parseVarSynonyms() {
    ensureToken(TokenType::IDENT);
    // check if the token value is declared as variable synonyms in any of the set
    if (parsingResult.getDeclaredSynonym(currentToken().getValue()) != "variable") {
        throwSemanticError();
    }
}

// Parses a statement synonym in the query.
void QueryParser::parseStmtSynonyms() {
    ensureToken(TokenType::IDENT);
    if(currentSuchThatToken.getType() == TokenType::Parent || currentSuchThatToken.getType() == TokenType::ParentT) {
        if (parsingResult.getDeclaredSynonym(currentToken().getValue()) != "stmt" &&
                parsingResult.getDeclaredSynonym(currentToken().getValue()) != "assign" &&
                parsingResult.getDeclaredSynonym(currentToken().getValue()) != "while" &&
                parsingResult.getDeclaredSynonym(currentToken().getValue()) != "if" &&
                parsingResult.getDeclaredSynonym(currentToken().getValue()) != "print" &&
                parsingResult.getDeclaredSynonym(currentToken().getValue()) != "read") {
            throwSemanticError();
        }
    }

    if(currentSuchThatToken.getType() == TokenType::Follows || currentSuchThatToken.getType() == TokenType::FollowsT) {
        if (parsingResult.getDeclaredSynonym(currentToken().getValue()) != "stmt" &&
           parsingResult.getDeclaredSynonym(currentToken().getValue()) != "assign" &&
           parsingResult.getDeclaredSynonym(currentToken().getValue()) != "while" &&
           parsingResult.getDeclaredSynonym(currentToken().getValue()) != "if" &&
           parsingResult.getDeclaredSynonym(currentToken().getValue()) != "print" &&
           parsingResult.getDeclaredSynonym(currentToken().getValue()) != "read") {
            throwSemanticError();
        }
    }


    if(currentSuchThatToken.getType() == TokenType::Uses) {
        if (parsingResult.getDeclaredSynonym(currentToken().getValue()) != "stmt" &&
            parsingResult.getDeclaredSynonym(currentToken().getValue()) != "print" &&
            parsingResult.getDeclaredSynonym(currentToken().getValue()) != "while" &&
            parsingResult.getDeclaredSynonym(currentToken().getValue()) != "if" &&
            parsingResult.getDeclaredSynonym(currentToken().getValue()) != "assign"){
            throwSemanticError();
        }
    }

    if (currentSuchThatToken.getType() == TokenType::Modifies) {
        if (parsingResult.getDeclaredSynonym(currentToken().getValue()) != "stmt" &&
            parsingResult.getDeclaredSynonym(currentToken().getValue()) != "read" &&
            parsingResult.getDeclaredSynonym(currentToken().getValue()) != "while" &&
            parsingResult.getDeclaredSynonym(currentToken().getValue()) != "if" &&
            parsingResult.getDeclaredSynonym(currentToken().getValue()) != "assign"){
            throwSemanticError();
        }
    }

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

// peek the next token
bool QueryParser::peekNextToken(TokenType type) {
    if (currentTokenIndex < tokens.size() - 1) {
        return tokens[currentTokenIndex + 1].getType() == type;
    }
    return false;
}

bool QueryParser::checkValidStmtNum() {
    if (stoi(currentToken().getValue()) < 1) {
        return false;
    }
    return true;
}


void QueryParser::parseWithClause() {
    WithClause clause;
    ensureToken(TokenType::WithKeyword);
    clause.setRelationship(currentToken());
    advanceToken();

    size_t startIndex = currentTokenIndex;
    parseRef();
    string concatenatedTokens;
    for (size_t i = startIndex; i <= currentTokenIndex; ++i) {
        concatenatedTokens += tokens[i].getValue();
    }
    clause.setFirstParam(Token(TokenType::Ref, concatenatedTokens));

    advanceToken();
    ensureToken(TokenType::Equal);
    advanceToken();

    startIndex = currentTokenIndex;
    parseRef();
    concatenatedTokens = "";
    for (size_t i = startIndex; i <= currentTokenIndex; ++i) {
        concatenatedTokens += tokens[i].getValue();
    }
    clause.setSecondParam(Token(TokenType::Ref, concatenatedTokens));
    
    parsingResult.addWithClause(clause);
}

void QueryParser::parseRef() {
    if (match(TokenType::QuoutIDENT)) {
        return;
    }
    else if (match(TokenType::INTEGER)) {
        if (checkValidStmtNum()) {
            return;
        }
        throwSemanticError();
    }
    else {
        parseAttrRef();
    }

}

void QueryParser::parseAttrRef() {
    parseSynonym();
    advanceToken();
    ensureToken(TokenType::Dot);
    advanceToken();
    ensureToken(TokenType::AttrName);
}