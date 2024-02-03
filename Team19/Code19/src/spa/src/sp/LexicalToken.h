#pragma once
#include <string>

/* Contains classes describing SIMPLE Lexical Tokens. */
namespace LexicalTokens {
	class LexicalToken {
	public:
		virtual bool verifyToken(std::string str) const = 0;
		virtual ~LexicalToken() = default;
	};

	class Letter : public LexicalToken {
	public:
		bool verifyToken(std::string str) const override;
	};

	class Digit : public LexicalToken {
	public:
		bool verifyToken(std::string str) const override;
	};

	class Name : public LexicalToken {
	public:
		bool verifyToken(std::string str) const override;
	};

	class Integer : public LexicalToken {
	public:
		bool verifyToken(std::string str) const override;
	};
}
