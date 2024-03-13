#pragma once

#include <string>
#include <utility>
#include <vector>
#include <unordered_map>

#include "sp/AST/ASTNode.h"

// ai-gen start (gpt, 2, e)
// prompt: GitHub Copilot

/*
* @brief Utility class for AST
* 
* This class contains static methods that are used to determine node types/design types
* of AST nodes. It also contains methods to check if a node is a statement, expression,
* or basically any entity types
*/
class ASTUtility {
public:
    /**
     * @brief Check the type of AST node by string
     * @param accepting an enum object of AST Node
     * @return the string representation of the AST Node type
     */
    static std::unordered_map<ASTNodeType, std::string> getASTNodeType;

    /**
     * @brief Check if accepting AST node is a statement
     * @return true if AST is either assign, call, if-else-then, print, read, or while,
     * and false otherwise
     */
    static bool nodeIsStatement(ASTNodeType t);

    /**
    * @brief Check if accepting AST node is an expression
    * @return true if AST node is ">" or ">=" or "<" or "<=" or "==" or "!=", and false otherwise.
     */
    static bool nodeIsRelExpression(ASTNodeType t);

    /*
    * @brief Check if accepting AST node is a conditional expression
    * @return true if AST node is "!" or "&&" or "||", and false otherwise.
    */
    static bool nodeIsCondExpression(ASTNodeType t);

    /*
    * @brief Check if accepting AST node is a valid operator
    * @return true if AST node is "+" or "-" or "*" or "/" or "%", and false otherwise.
    */
    static bool nodeIsValidOperator(ASTNodeType t);

    /*
    * @brief Check if accepting AST node is a valid relational factor
    * @return true if AST node is a variable or constant, and false otherwise.
    */
    static bool nodeIsValidRelFactor(ASTNodeType t);

    /*
    * @brief Check if accepting AST node is a valid expression
    * @return true if AST node consists of: valid relational expression,
    * conditioanl expression, valid operator, or valid relational factor, and false otherwise.
    */
    static bool nodeCanFormValidExpression(ASTNodeType t);

    /*
    * @brief Check if accepting AST node is a program
    * @return true if AST node is a program, and false otherwise.
    */
    static bool nodeIsProgram(ASTNodeType t);

    /*
    * @brief Check if accepting AST node is a procedure
    * @return true if AST node is a procedure, and false otherwise.
    */
    static bool nodeIsProcedure(ASTNodeType t);

    /*
    * @brief Check if accepting AST node is a statement list
    * @return true if AST node is a statement list, and false otherwise.
    */
    static bool nodeIsStatementList(ASTNodeType t);

    /*
    * @brief Check if accepting AST node is an if-else statement
    * @return true if AST node is an if-else statement, and false otherwise.
    */
    static bool nodeIsIfElse(ASTNodeType t);

    /*
    * @brief Check if accepting AST node is a call statement
    * @return true if AST node is a call statement, and false otherwise.
	*/
    static bool nodeIsCall(ASTNodeType t);

    /*
    * Method to compare two AST node types together
    * @param t1 the first AST node type
    * @param t2 the second AST node type
    * @return true if the two AST node types are the same, and false otherwise.
    */
    static bool nodeIsTarget(ASTNodeType t1, ASTNodeType t2);

    /*
    * @brief Check if the accepting AST node can "uses" a variable
    * @return true if can and false otherwise
    */
    static bool nodeStatementCanUses(ASTNodeType t);

    /*
    * @brief Check if the accepting AST node can "modifies" a variable
    * @return true if can and false otherwise
    */
    static bool nodeStatementCanModifies(ASTNodeType t);
};

// ai-gen end