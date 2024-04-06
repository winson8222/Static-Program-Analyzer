#include "LexicalToken.h"
#include <stdexcept>

LexicalToken::LexicalToken(LexicalTokenType type) {
    this->type = type;
    this->value = "";
}

LexicalToken::LexicalToken(LexicalTokenType t, std::string value) {
    this->type = t;
    this->value = value;
}

const LexicalToken& LexicalToken::getNullToken() {
    static const LexicalToken nullToken(LexicalTokenType::NULL_TOKEN);
    return nullToken;
}

std::string LexicalToken::getValue() const {
    return this->value;
}

LexicalTokenType LexicalToken::getTokenType() {
    return this->type;
}

bool LexicalToken::isType(LexicalTokenType type) {
    return LexicalTokenTypeMapper::isType(this->getTokenType(), type);
}

void LexicalToken::assertToken(LexicalTokenType type) {
    if (!this->isType(type)) {
        throw std::runtime_error("Error: Expected " + LexicalTokenTypeMapper::printType(type) + " but got " + 
            LexicalTokenTypeMapper::printType(this->getTokenType()));
    }
}
