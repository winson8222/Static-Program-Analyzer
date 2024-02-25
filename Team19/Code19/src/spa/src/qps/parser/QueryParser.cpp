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

    if(!parseDeclarations()) {
        return parsingResult;
    }


    if(!parseSelectClause()) {
        return parsingResult;
    }
    if (currentTokenIndex == tokens.size() - 1) {
        return parsingResult;
    }
    if (!advanceToken()) {
        return parsingResult;
    }

    // check if there is a such that or pattern clause with such that coming first
    if (match(TokenType::SuchKeyword)) {
        if(!parseSuchThatClause()) {
            return parsingResult;
        }

        if (currentTokenIndex == tokens.size() - 1) {
            return parsingResult;
        }

        if (!advanceToken()) {
            return parsingResult;
        }
        if(!parsePatternClause()) {
            return parsingResult;
        }
        
    }

    if (match(TokenType::PatternKeyword)) {
        if(!parsePatternClause()) {
            return parsingResult;
        }

        if (currentTokenIndex == tokens.size() - 1) {
            return parsingResult;
        }

        if (!advanceToken()) {
            return parsingResult;
        }

        if (match(TokenType::SuchKeyword)) {
            if(!parseSuchThatClause()) {
                return parsingResult;
            }
        } else {
            parsingResult.setErrorMessage(getGrammarError());
            return parsingResult;
        }
    }
    if (currentTokenIndex == tokens.size() - 1) {
        return parsingResult;
    }
    return parsingResult;
}

// Parses declarations in the query.
// Processes design entities and their synonyms, and ensures correct syntax with semicolons.
bool QueryParser::parseDeclarations() {
    int numberOfDeclarations = 0;
    while (!match(TokenType::SelectKeyword)) {
        if(!parseDesignEntity()) {
            return false;
        }
        string assignmentType = currentToken().getValue();
        if (!advanceToken()) {
            return false;
        }

        if(!parseSynonym()) {
            parsingResult.setErrorMessage(getGrammarError());
            return false;
        }
        parsingResult.addDeclaredSynonym(currentToken().getValue(), assignmentType);
        if (!advanceToken()) {
            return false;
        }

        while (match(TokenType::Comma)) {
            if (!advanceToken()) {
                return false;
            }
            if(!parseSynonym()){
                parsingResult.setErrorMessage(getGrammarError());
                return false;
            }
            parsingResult.addDeclaredSynonym(currentToken().getValue(), assignmentType);
            if (!advanceToken()) {
                return false;
            }
        }

        if(!ensureToken(TokenType::Semicolon)){
            return false;
        }
        if (!advanceToken()) {
            return false;
        }


        numberOfDeclarations++;
    }

    if (numberOfDeclarations == 0) {
        parsingResult.setErrorMessage(getGrammarError());
        return false;
    }
    return true;
    
}

// Parses a design entity in the query.
// Ensures the current token is a design entity and advances the token.
bool QueryParser::parseDesignEntity() {
    if (currentToken().getType() == TokenType::DesignEntity) {
        return true;
    }
    else {
		parsingResult.setErrorMessage(getGrammarError());
        return false;
    }
}


// Parses a synonym in the query.
// Ensures the current token is an identifier and advances the token.
bool QueryParser::parseSynonym() {
    // check if it is an ident and if the synonym is already declared
    if (!ensureToken(TokenType::IDENT)) {
        return false;
    }
    // check if the token value is declared as synonyms in any of the set
    if (!parsingResult.getDeclaredSynonym(currentToken().getValue()).empty()) {
        parsingResult.setErrorMessage(getSemanticError());
        return false;
    }
    return true;

}



// Parses the select clause in the query.
// Checks for the 'Select' keyword and ensures the following token is a valid identifier.
bool QueryParser::parseSelectClause() {
    if (currentToken().getValue() != "Select") {
        parsingResult.setErrorMessage(getGrammarError());
        return false;
    }
    if(!advanceToken()) {
        return false;
    }
    // check after select if it is a synonym
    if(!ensureToken(TokenType::IDENT)) {
        return false;
    }
    //check if the token value is declared as synonyms in any of the set
    if (parsingResult.getDeclaredSynonym(currentToken().getValue()).empty()) {
        parsingResult.setErrorMessage(getSemanticError());
        return false;
    }


    parsingResult.setRequiredSynonym(currentToken().getValue());
    return true;

}




// Parses the 'such that' clause in the query.
// Ensures the correct syntax and calls the function to process relation references.
bool QueryParser::parseSuchThatClause() {
    if (!advanceToken()) {
        return false;
    }
    if(!ensureToken(TokenType::ThatKeyword)) {
        return false;
    }
    if (!advanceToken()) {
        return false;
    }

    return parseRelRef();
}

// Parses relation references in a 'such that' clause.
// Determines the type of relation and calls the appropriate parsing function.
bool QueryParser::parseRelRef() {
    if (isStmtRefStmtRef()) {
        parsingResult.setSuchThatClauseRelationship(currentToken());
        if (!advanceToken()) {
            return false;
        }
        if(!parseStmtRefStmtRef()) {
            return false;
        }
        return true;
    } else if (isUsesOrModifies()) {
        if(!parseUsesOrModifies()) {
            return false;
        }
        return true;
    } else {
        parsingResult.setErrorMessage(getGrammarError());
        return false;
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
// set the Token type for the such that clause relationship more specifically
bool QueryParser::parseUsesOrModifies() {
    // need to differentiate between usesS/UsesP and modifiesS/ModifiesP
    currentSuchThatToken = currentToken();


    if (!advanceToken()) {
        return false;
    }
    if (match(TokenType::Lparenthesis)) {
        if (!advanceToken()) {
            return false;
        }
    }
    else {
        parsingResult.setErrorMessage(getGrammarError());
        return false;
    }

    if (match(TokenType::Wildcard)) {
        parsingResult.setErrorMessage(getSemanticError());
        return false;
    }




    if (parseStmtRef()) {
        if (currentSuchThatToken.getType() == TokenType::Uses) {
            currentSuchThatToken.setType(TokenType::UsesS);
            parsingResult.setSuchThatClauseRelationship(currentSuchThatToken);
        } else {
            currentSuchThatToken.setType(TokenType::ModifiesS);
            parsingResult.setSuchThatClauseRelationship(currentSuchThatToken);
        }
        parsingResult.setSuchThatClauseFirstParam(currentToken());
        if (!advanceToken()) {
            return false;
        }

    } else if (parseEntRef()) {
        if (currentSuchThatToken.getType() == TokenType::Uses) {
            currentSuchThatToken.setType(TokenType::UsesP);
            parsingResult.setSuchThatClauseRelationship(currentSuchThatToken);
        } else {
            currentSuchThatToken.setType(TokenType::ModifiesP);
            parsingResult.setSuchThatClauseRelationship(currentSuchThatToken);
        }
        parsingResult.setSuchThatClauseFirstParam(currentToken());
        if (!advanceToken()) {
            return false;
        }

    } else {
        parsingResult.setErrorMessage(getGrammarError());
    }




    if (match(TokenType::Comma)) {
        if (!advanceToken()) {
            return false;
        }
    }
    else {
        parsingResult.setErrorMessage(getGrammarError());
        return false;
    }

    if(!parseEntRef()) {
        return false;
    }

    parsingResult.setSuchThatClauseSecondParam(currentToken());
    if (!advanceToken()) {
        return false;
    }
    if(!ensureToken(TokenType::Rparenthesis)) {
        return false;
    }
    return true;
}

// Parses a statement reference to statement reference relation.
// Ensures correct syntax and processes multiple statement references.
bool QueryParser::parseStmtRefStmtRef() {
    if (match(TokenType::Lparenthesis)) {
        if (!advanceToken()) {
            return false;
        }
    } else {
        parsingResult.setErrorMessage(getGrammarError());
        return false;
    }

    // stmtRef
    if(!parseStmtRef()){
        return false;
    }
    parsingResult.setSuchThatClauseFirstParam(currentToken());
    if (!advanceToken()) {
        return false;
    }


    //','
    if (match(TokenType::Comma)) {
        if (!advanceToken()) {
            return false;
        }
    }
    else {
        parsingResult.setErrorMessage(getGrammarError());
        return false;
    }

    if(!parseStmtRef()) {
        return false;
    }
    parsingResult.setSuchThatClauseSecondParam(currentToken());
    if (!advanceToken()) {
        return false;
    }

    if(!ensureToken(TokenType::Rparenthesis)) {
        return false;
    }
    return true;
}

// Parses a statement reference in the query.
bool QueryParser::parseStmtRef() {
    if (match(TokenType::Wildcard)) {
        return true;
    } else if (match(TokenType::INTEGER)) {
        if(checkValidStmtNum()) {
            return true;
        }
        parsingResult.setErrorMessage(getSemanticError());
        return false;
    } else {
        if(!parseStmtSynonyms()) {
            parsingResult.setErrorMessage(getGrammarError());
            return false;
        }
        return true;
    }


}

// Parses an entity reference in the query.
// Handles different types of entity references like quoted identifier, wildcard, or synonym.
bool QueryParser::parseEntRef() {
    if (match(TokenType::QuoutIDENT) || match(TokenType::Wildcard)) {
        return true;
    } else {
        if(!parseVarSynonyms()){
            parsingResult.setErrorMessage(getSemanticError());
            return false;
        }
        return true;
    }

}




// Parses the pattern clause in the query.
// Ensures the correct syntax and processes entity references and expression specifications.
bool QueryParser::parsePatternClause() {

    if(!ensureToken(TokenType::PatternKeyword)) {
        return false;
    }
    if (!advanceToken()) {
        return false;
    }
    // check if it is a syn-assign
    if(!ensureToken(TokenType::IDENT)) {
        return false;
    }
    parsingResult.setPatternClauseRelationship(currentToken());
    if(!parseAssignSynonyms()){
        return false;
    }


    if(!ensureToken(TokenType::Lparenthesis)) {
        return false;
    }

    if (!advanceToken()) {
        return false;
    }
    if(!parseEntRef()) {
        return false;
    }
    parsingResult.setPatternClauseFirstParam(currentToken());

    if (!advanceToken()) {
        return false;
    }
    if(!ensureToken(TokenType::Comma)) {
        return false;
    }

    if (!advanceToken()) {
        return false;
    }
    // This is a rudimentary approach to tokenize ExpressionSpec, probably change later
    // Store the current token index before parsing the expression spec
    size_t startIndex = currentTokenIndex;

    if(!parseExpressionSpec()) {
        parsingResult.setErrorMessage(getGrammarError());
        return false;
    }

    // Concatenate all token values from startIndex to the current index
    string concatenatedTokens;
    for (size_t i = startIndex; i <= currentTokenIndex; ++i) {
        concatenatedTokens += tokens[i].getValue();
    }
    parsingResult.setPatternClauseSecondParam(Token(TokenType::ExpressionSpec, concatenatedTokens));

    if (!advanceToken()) {
        return false;
    }
    if(!ensureToken(TokenType::Rparenthesis)){
        return false;
    }
    return true;
}

// Parses the expression specification in the query.
// Handles different forms of expressions like quoted constants, wildcards, or quoted expressions.
bool QueryParser::parseExpressionSpec() {

    if (match(TokenType::QuoutConst) || match(TokenType::QuoutIDENT) || match(TokenType::ExpressionSpec)) {
        return true;
    } else if (match(TokenType::Wildcard)) {
        if (peekNextToken(TokenType::Rparenthesis)) {
            return true;
        }
        if (!advanceToken()) {
            return false;
        }




        if (!match(TokenType::QuoutIDENT) && !match(TokenType::QuoutConst) && !match(TokenType::ExpressionSpec)) {
            parsingResult.setErrorMessage(getGrammarError());
            return false;
        }

        if (!advanceToken()) {
            return false;
        }

        if(!ensureToken(TokenType::Wildcard)){
            return false;
        }
        return true;

    } else if (match(TokenType::QuoutIDENT)) {
        return parseQuotedExpression();
    } else {
        parsingResult.setErrorMessage(getGrammarError());
        return false;
    }


}

// Parses a quoted expression in the query.
// Processes the expression enclosed in double quotes.
bool QueryParser::parseQuotedExpression() {
    if (!advanceToken()) {
        return false;
    }
    if(!parseExpression()) {
        parsingResult.setErrorMessage(getGrammarError());
        return false;
    }
    if(!ensureToken(TokenType::DoubleQuote)) {
        return false;
    }
    return true;


}

// Parses an expression in the query.
// Processes terms and operators within the expression.
bool QueryParser::parseExpression() {
    if(!parseTerm()) {
        return false;
    }

    while (match(TokenType::Operator)) {
        if (currentToken().getValue() == "+" || currentToken().getValue() == "-") {
            if (!advanceToken()) {
                return false;
            }
        } else {
            parsingResult.setErrorMessage(getGrammarError());
            return false;
        }
        if (!advanceToken()) {
            return false;
        }
        if(!parseTerm()) {
            return false;
        }
    }
    return true;
}

// Parses a term in an expression.
// Processes factors and operators within the term.
bool QueryParser::parseTerm() {
    if(!parseFactor()) {
        parsingResult.setErrorMessage(getGrammarError());
        return false;
    }

    while (match(TokenType::Operator)) {
        if (currentToken().getValue() == "*" || currentToken().getValue() == "/"
        || currentToken().getValue() == "%") {
            if (!advanceToken()) {
                return false;
            }
        }
        if(!parseFactor()) {
            parsingResult.setErrorMessage(getGrammarError());
            return false;
        }
    }
    return true;
}

// Parses a factor in a term.
// Handles parentheses, variable names, and constant values.
bool QueryParser::parseFactor() {
    if (match(TokenType::Lparenthesis)) {
        if (!advanceToken()) {
            return false;
        }
        if(!parseExpression()) {
            parsingResult.setErrorMessage(getGrammarError());
            return false;
        }
        if (!ensureToken(TokenType::Rparenthesis)) {
            return false;
        }
        if (!advanceToken()) {
            return false;
        }
        return true;

    } else if (isVarName()) {
        if (!advanceToken()) {
            return false;
        }
        return true;
    } else if (isConstValue()) {
        if (!advanceToken()) {
            return false;
        }
        return true;
    } else {
        parsingResult.setErrorMessage(getGrammarError());
        return false;
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
    parsingResult.setErrorMessage("Incomplete Query");
    return false;
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
bool QueryParser::ensureToken(TokenType expected) {
    if (!match(expected)) {
        parsingResult.setErrorMessage(getGrammarError());
        return false;
    }
    return true;
}

// Throws a standard invalid_argument exception with a custom error message for grammar error.
string QueryParser::getGrammarError() {
    //return "incorrect grammar at: " + currentToken().getValue();
    return "SyntaxError";
}

// Throws a standard invalid_argument exception with a custom error message for semantic error.
string QueryParser::getSemanticError() {
    //return "semantic error at: " + currentToken().getValue();
    return "SemanticError";
}

// Parses a variable synonym in the query.
bool QueryParser::parseVarSynonyms() {
    if (!ensureToken(TokenType::IDENT)) {
        return false;
    }
    // check if the token value is declared as variable synonyms in any of the set
    if (parsingResult.getDeclaredSynonym(currentToken().getValue()) != "variable") {
        parsingResult.setErrorMessage(getSemanticError());
        return false;
    }
    return true;


}

// Parses a statement synonym in the query.
bool QueryParser::parseStmtSynonyms() {
    if(!ensureToken(TokenType::IDENT)){
        return false;
    }

    if(currentSuchThatToken.getType() == TokenType::Uses) {
        if (parsingResult.getDeclaredSynonym(currentToken().getValue()) != "stmt" &&
            parsingResult.getDeclaredSynonym(currentToken().getValue()) != "print" &&
            parsingResult.getDeclaredSynonym(currentToken().getValue()) != "while" &&
            parsingResult.getDeclaredSynonym(currentToken().getValue()) != "if" &&
            parsingResult.getDeclaredSynonym(currentToken().getValue()) != "procedure" &&
            parsingResult.getDeclaredSynonym(currentToken().getValue()) != "assign"){
            parsingResult.setErrorMessage(getSemanticError());
            return false;
        }
    }

    if (currentSuchThatToken.getType() == TokenType::Modifies) {
        if (parsingResult.getDeclaredSynonym(currentToken().getValue()) != "stmt" &&
            parsingResult.getDeclaredSynonym(currentToken().getValue()) != "read" &&
            parsingResult.getDeclaredSynonym(currentToken().getValue()) != "while" &&
            parsingResult.getDeclaredSynonym(currentToken().getValue()) != "if" &&
            parsingResult.getDeclaredSynonym(currentToken().getValue()) != "procedure" &&
            parsingResult.getDeclaredSynonym(currentToken().getValue()) != "assign"){
            parsingResult.setErrorMessage(getSemanticError());
            return false;
        }
    }

    return true;

}


// Parses an assignment synonym in the query.
bool QueryParser::parseAssignSynonyms() {
    if(!ensureToken(TokenType::IDENT)) {
        return false;
    }
    if (parsingResult.getDeclaredSynonym(currentToken().getValue()) != "assign") {
        parsingResult.setErrorMessage(getSemanticError());
        return false;
    }
    if (!advanceToken()) {
        return false;
    }
    return true;
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


