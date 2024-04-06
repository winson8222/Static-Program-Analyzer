#pragma once

#include <string>
#include <vector>
#include <unordered_set>

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
    UsesS,
    UsesP,
    Modifies,
    ModifiesS,
    ModifiesP,
    ExpressionSpec,
    PartialExpressionSpec,
    SyntaxError,
    //M2
    Calls,
    CallsT,
    Next,
    NextT,
    Affects,
    WithKeyword,
    AttrName,
    Dot,
    Tuple,
    AndKeyword,
    BooleanKeyword,
    Equal,
    LeftAngleBracket,
    RightAngleBracket,
    Ref,
    Elem,
    NotKeyword

};

// The Token class represents a token with a type and a string value.
class Token {
public:
    Token() = default;  // Default constructor
    // Constructor: creates a Token with a given type and value.
    Token(TokenType type, std::string value);

    // Virtual Destructor: properly destroys Token objects.
    virtual ~Token() = default;


    // getType: returns the type of the token.
    TokenType getType() const;

    // getValue: returns the string value of the token.
    std::string getValue() const;

    void setType(TokenType type);
    bool isEqual(Token& token) ;

private:
    TokenType type;    // Stores the type of the token
    std::string value; // Stores the string value of the token
};
