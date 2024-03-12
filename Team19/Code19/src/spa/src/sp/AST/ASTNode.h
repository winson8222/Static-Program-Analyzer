#pragma once

#include <vector>
#include <memory>
#include <string>

// ai-gen start (gpt, 2, e)
// prompt: https://chat.openai.com/share/a181de60-e76f-496c-9bee-7ea80f2be651

enum class ASTNodeType {
    PROGRAMS, PROCEDURE, STATEMENT_LIST,

    // Statements
    READ, PRINT, CALL, WHILE, IF_ELSE_THEN, ASSIGN,

    // Expressions and operators
    NOT, AND, OR, GREATER, GREATER_OR_EQUAL, LESSER, LESSER_OR_EQUAL,EQUAL, NOT_EQUAL,
    ADD, SUBTRACT, MULTIPLY, DIVIDE, MODULO,

    // Entities
    VARIABLE, CONSTANT,

    OTHER,

    ERROR,
};

/**
 * @brief Represents a node in the Abstract Syntax Tree (AST).
 */
class ASTNode {
public:
    /**
     * @brief Default constructor for ASTNode.
     */
    ASTNode();

    /**
     * @brief Constructor for creating an ASTNode with specified type, line number, and value.
     *
     * @param type The type of the AST node.
     * @param lineNumber The line number associated with the AST node.
     * @param value The value associated with the AST node.
     */
    ASTNode(ASTNodeType type, int lineNumber, std::string value);
    
    /**
     * @brief Adds a child node to the current AST node.
     *
     * @param child A shared pointer to the child AST node to be added.
     */
    void addChild(std::shared_ptr<ASTNode> child);
    
    /**
     * @brief Sets the value of the current AST node.
     *
     * @param value The value to be set for the current AST node.
     */
    void setValue(std::string value);

    /**
    * @brief Computes the hash value of the current AST node.
    *
    * @return The hash value of the current AST node.
    */
    std::size_t hash() const;

    /**
     * @brief Checks if two AST nodes are equal.
     *
     * @param other The AST node to compare with.
     * @return True if the two AST nodes are equal, otherwise false.
     */
    bool operator==(const ASTNode& other) const;

    /**
     * @brief Converts the AST node to a string representation.
     *
     * @return A string representation of the AST node.
     */
    std::string toString() const;

    /**
    * @brief Converts the AST node to a string representation in Reverse Polish Notation (RPN).
    *
    * @return A string representation of the AST node in RPN.
    */
    std::string getRPNForm();

    /**
	 * @brief Sets visited field to true
	 */
    void setVisited();

    /**
    * @brief gets visited field
	*/
    bool getVisited();

    /*
    * @brief Get the type of the AST node.
    */
    ASTNodeType getType();

    /*
    * @brief Get the value of the AST node.
    */
    std::string getValue();

    /*
    * @brief Get the line number of the AST node.
    */
    int getLineNumber();

    /*
    * @brief Get the children of the AST node.
    */
    std::vector<std::shared_ptr<ASTNode>> getChildren();

    /*
    * @brief Get the specific child of the AST node.
    */
    std::shared_ptr<ASTNode> getChildByIndex(int index);

    /*
    * @brief Set the children of the AST node.
    */
    void setChildByIndex(int index, std::shared_ptr<ASTNode> child);

    /*
    * @brief Compare the type of nodes
    */
    bool equalType(ASTNodeType type);

    // To be set as private in future, probably milestone 2
    ASTNodeType type;
    std::vector<std::shared_ptr<ASTNode>> children;
    int lineNumber;
    std::string value;
    bool visited;

private:
    std::shared_ptr<ASTNode> root;

    /**
     * @brief Generates a string representation of the AST node and its children recursively.
     *
     * @param tabs The number of tabs to indent the string representation.
     * @return A string representation of the AST node and its children.
     */
    std::string recursiveString(int tabs) const;
};

/*
* @brief Hash function for ASTNode.
* This is to help with putting ASTNode on an unordered_map or unordered_set.
*/
namespace std {
    template<> struct hash<ASTNode> {
        std::size_t operator()(const ASTNode& node) const {
            // Combine hash values of type, lineNumber, and value
            return std::hash<long long>{}(node.hash());
        }
    };
}

// ai-gen end