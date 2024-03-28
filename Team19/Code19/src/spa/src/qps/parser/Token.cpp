#include "Token.h"

using namespace std;

// Initializes a Token object with a given type and value.
// @param type: The type of the token, from the TokenType enum.
// @param value: The string value of the token.
Token::Token(TokenType type, string value)
: type(type), value(std::move(value)) {}  // Initializer list used for efficiency.

// Returns the type of the token.
// @return TokenType: The type of this token.
TokenType Token::getType() const {
    return type; 
}

// Returns the string value of the token.
// @return string: The value of this token.
string Token::getValue() const {
    return value; 
}

// Implementations for subclasses would go here...

void Token::setType(TokenType type) {
    this->type = type;
}
