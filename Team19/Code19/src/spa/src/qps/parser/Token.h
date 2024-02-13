// Header guards to prevent multiple inclusions of this header file.
#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

// Define an enumeration class TokenType.
// This enum class lists different types of tokens that can be recognized.
enum class TokenType {
    IDENT,    
    INTEGER,  
    Wildcard,   
    QuoutIDENT,
    Operator,
    DoubleQuote,
    Lparenthesis,
    Rparenthesis,
    Semicolon,
    Comma,
    DesignEntity,
    SelectKeyword,
    PatternKeyword,
    SuchKeyword,
    ThatKeyword,
    QuoutConst,
    Follows,
    FollowsT,
    Parent,
    ParentT,
    Uses,
    Modifies,
    ExpressionSpec,


};



// The Token class represents a token with a type and a string value.
class Token {
public:
    Token() = default;  // Default constructor
    // Constructor: creates a Token with a given type and value.
    Token(TokenType type, string value);

    // Virtual Destructor: properly destroys Token objects.
    virtual ~Token() = default;


    // getType: returns the type of the token.
    TokenType getType() const;

    // getValue: returns the string value of the token.
    string getValue() const;
    
private:
    TokenType type;    // Stores the type of the token
    string value; // Stores the string value of the token
};

// Subclasses for different token types can be defined here...



#endif
