#include "LexicalToken.h"
#include <iostream>

namespace LexicalTokens {
    bool Letter::verifyToken(std::string str) const {
        std::cout << "Letter class verifyToken" << std::endl;
        return true;
    }

    bool Digit::verifyToken(std::string str) const {
        std::cout << "Digit class verifyToken" << std::endl;
        return true;
    }

    bool Name::verifyToken(std::string str) const {
        std::cout << "Name class verifyToken" << std::endl;
        return true;
    }

    bool Integer::verifyToken(std::string str) const {
        std::cout << "Integer class verifyToken" << std::endl;
        return true;
    }

}
