#pragma once
#include <string>

/*	Contains classes describing SIMPLE Lexical Tokens.
*/ 
namespace LexicalTokens {
	class LexicalToken {
		public:
			virtual bool verifyToken(std::string str);
			virtual ~LexicalToken() = default;
	};

	class Letter : public LexicalToken {
		public:
			bool verifyToken(std::string str) const override;
		};
	};
};