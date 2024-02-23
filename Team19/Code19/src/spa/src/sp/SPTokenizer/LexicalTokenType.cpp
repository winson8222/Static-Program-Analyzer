#include "LexicalTokenType.h"
#include <regex>

const std::unordered_map<std::string, LexicalTokenType> LexicalTokenTypeMapper::stringToTokenMap = {
	// Symbols
	{"{", LexicalTokenType::SYMBOL_OPEN_BRACE},
	{"}", LexicalTokenType::SYMBOL_CLOSE_BRACE},
	{"(", LexicalTokenType::SYMBOL_OPEN_PAREN},
	{")", LexicalTokenType::SYMBOL_CLOSE_PAREN},
	{";", LexicalTokenType::SYMBOL_SEMICOLON},

	// Operators
	{"=", LexicalTokenType::OPERATOR_ASSIGN},
	{"!", LexicalTokenType::OPERATOR_NOT},
	{"&&", LexicalTokenType::OPERATOR_AND},
	{"||", LexicalTokenType::OPERATOR_OR},
	{">", LexicalTokenType::OPERATOR_GREATER},
	{">=", LexicalTokenType::OPERATOR_GREATER_EQUAL},
	{"<", LexicalTokenType::OPERATOR_LESS},
	{"<=", LexicalTokenType::OPERATOR_LESS_EQUAL},
	{"==", LexicalTokenType::OPERATOR_IS_EQUAL},
	{"!=", LexicalTokenType::OPERATOR_NOT_EQUAL},
	{"+", LexicalTokenType::OPERATOR_PLUS},
	{"-", LexicalTokenType::OPERATOR_MINUS},
	{"*", LexicalTokenType::OPERATOR_MULTIPLY},
	{"/", LexicalTokenType::OPERATOR_DIVIDE},
	{"%", LexicalTokenType::OPERATOR_MODULO},

	// Keywords
	{"if", LexicalTokenType::KEYWORD_IF},
	{"then", LexicalTokenType::KEYWORD_THEN},
	{"else", LexicalTokenType::KEYWORD_ELSE},
	{"read", LexicalTokenType::KEYWORD_READ},
	{"call", LexicalTokenType::KEYWORD_CALL},
	{"print", LexicalTokenType::KEYWORD_PRINT},
	{"procedure", LexicalTokenType::KEYWORD_PROCEDURE},
	{"while", LexicalTokenType::KEYWORD_WHILE},

	{" ", LexicalTokenType::WHITESPACE},
	{"\n", LexicalTokenType::NEW_LINE}
	// Add more keywords as needed
};

const std::unordered_map<LexicalTokenType, std::string> LexicalTokenTypeMapper::tokenToStringMap = {
	// Symbols
	{LexicalTokenType::SYMBOL_OPEN_BRACE, "LEFT_BRACE"},
	{LexicalTokenType::SYMBOL_CLOSE_BRACE, "RIGHT_BRACE"},
	{LexicalTokenType::SYMBOL_OPEN_PAREN, "LEFT_PARENTHESIS"},
	{LexicalTokenType::SYMBOL_CLOSE_PAREN, "RIGHT_PARENTHESIS"},
	{LexicalTokenType::SYMBOL_SEMICOLON, "SEMICOLON"},

	// Operators
	{LexicalTokenType::OPERATOR_ASSIGN, "EQUAL_ASSIGNMENT"},
	{LexicalTokenType::OPERATOR_NOT, "NOT_EQUAL"},
	{LexicalTokenType::OPERATOR_AND, "LOGICAL_AND"},
	{LexicalTokenType::OPERATOR_OR, "LOGICAL_OR"},
	{LexicalTokenType::OPERATOR_GREATER, "GREATER_THAN"},
	{LexicalTokenType::OPERATOR_GREATER_EQUAL, "GREATER_THAN_OR_EQUAL"},
	{LexicalTokenType::OPERATOR_LESS, "LESS_THAN"},
	{LexicalTokenType::OPERATOR_LESS_EQUAL, "LESS_THAN_OR_EQUAL"},
	{LexicalTokenType::OPERATOR_IS_EQUAL, "EQUAL_TO"},
	{LexicalTokenType::OPERATOR_NOT_EQUAL, "NOT_EQUAL_TO"},
	{LexicalTokenType::OPERATOR_PLUS, "ADDITION"},
	{LexicalTokenType::OPERATOR_MINUS, "SUBTRACTION"},
	{LexicalTokenType::OPERATOR_MULTIPLY, "MULTIPLICATION"},
	{LexicalTokenType::OPERATOR_DIVIDE, "DIVISION"},
	{LexicalTokenType::OPERATOR_MODULO, "MODULO"},

	// Keywords
	{LexicalTokenType::KEYWORD_IF, "IF"},
	{LexicalTokenType::KEYWORD_THEN, "THEN"},
	{LexicalTokenType::KEYWORD_ELSE, "ELSE"},
	{LexicalTokenType::KEYWORD_READ, "READ"},
	{LexicalTokenType::KEYWORD_CALL, "CALL"},
	{LexicalTokenType::KEYWORD_PRINT, "PRINT"},
	{LexicalTokenType::KEYWORD_PROCEDURE, "PROCEDURE"},
	{LexicalTokenType::KEYWORD_WHILE, "WHILE"},

	{LexicalTokenType::NAME, "NAMES"},
	{LexicalTokenType::INTEGER, "INTEGERS"},
	{LexicalTokenType::WHITESPACE, "WHITESPACES"},
	{LexicalTokenType::NEW_LINE, "NEWLINES"}
};

const std::vector<std::pair<LexicalTokenType, std::string>> LexicalTokenTypeMapper::tokenToRegexPairs = {
	// Keywords
	{LexicalTokenType::SYMBOL_SEMICOLON, "^(;)"},

	{LexicalTokenType::KEYWORD_IF, "^(if\\b)"},
	{LexicalTokenType::KEYWORD_THEN, "^(then\\b)"},
	{LexicalTokenType::KEYWORD_ELSE, "^(else\\b)"},
	{LexicalTokenType::KEYWORD_READ, "^(read\\b)"},
	{LexicalTokenType::KEYWORD_CALL, "^(call\\b)"},
	{LexicalTokenType::KEYWORD_PRINT, "^(print\\b)"},
	{LexicalTokenType::KEYWORD_PROCEDURE, "^(procedure\\b)"},
	{LexicalTokenType::KEYWORD_WHILE, "^(while\\b)"},

	// Symbols
	{LexicalTokenType::SYMBOL_OPEN_BRACE, "^(\\{)"},
	{LexicalTokenType::SYMBOL_CLOSE_BRACE, "^(\\})"},
	{LexicalTokenType::SYMBOL_OPEN_PAREN, "^(\\()"},
	{LexicalTokenType::SYMBOL_CLOSE_PAREN, "^(\\))"},
	{LexicalTokenType::OPERATOR_IS_EQUAL, "^(==)"},
	{LexicalTokenType::OPERATOR_LESS_EQUAL, "^(<=)"},
	{LexicalTokenType::OPERATOR_GREATER_EQUAL, "^(>=)"},
	{LexicalTokenType::OPERATOR_NOT_EQUAL, "^(!=)"},

	{LexicalTokenType::OPERATOR_ASSIGN, "^(=)"},
	{LexicalTokenType::OPERATOR_NOT, "^(!)"},
	{LexicalTokenType::OPERATOR_AND, "^(&&)"},
	{LexicalTokenType::OPERATOR_OR, "^(\\|\\|)"},
	{LexicalTokenType::OPERATOR_GREATER, "^(>)"},
	{LexicalTokenType::OPERATOR_LESS, "^(<)"},
	
	{LexicalTokenType::OPERATOR_PLUS, "^(\\+)"},
	{LexicalTokenType::OPERATOR_MINUS, "^(-)"},
	{LexicalTokenType::OPERATOR_MULTIPLY, "^(\\*)"},
	{LexicalTokenType::OPERATOR_DIVIDE, "^(\\/)"},
	{LexicalTokenType::OPERATOR_MODULO, "^(%)"},

	// Other matches
	// "^([a-zA-Z]\\w*)\\b"
	{LexicalTokenType::NAME, "^([a-zA-Z][a-zA-Z0-9]*)\\b"},
	{LexicalTokenType::INTEGER,  "^(\\d+\\b)"},
	{LexicalTokenType::WHITESPACE, "^(\\s+)"}
};


LexicalTokenType LexicalTokenTypeMapper::getTokenType(std::string str) {
	auto it = stringToTokenMap.find(str);
	if (it != stringToTokenMap.end()) {
		return it->second;
	}

	// Check for valid integer pattern (\d+)
	if (std::regex_match(str, std::regex(R"(\d+)"))) {
		return LexicalTokenType::INTEGER;
	}

	// Check for valid name pattern ([a-zA-Z][a-zA-Z0-9]*)
	if (std::regex_match(str, std::regex(R"([a-zA-Z][a-zA-Z0-9]*)"))) {
		return LexicalTokenType::NAME;
	}

	return LexicalTokenType::ERROR;
}

bool LexicalTokenTypeMapper::isKeyword(LexicalTokenType token) {
	return token == LexicalTokenType::KEYWORD_PROCEDURE
		|| token == LexicalTokenType::KEYWORD_READ
		|| token == LexicalTokenType::KEYWORD_PRINT
		|| token == LexicalTokenType::KEYWORD_CALL;
}

const std::string LexicalTokenTypeMapper::printType(LexicalTokenType type) {
	auto it = tokenToStringMap.find(type);
	if (it != tokenToStringMap.end()) {
		return it->second;
	}

	return "ERROR";
}

// ai-gen start(gpt, 1, e)
// Prompt: https://platform.openai.com/playground/p/hqmTI5WojSoGp9ObQfd7Yegx?mode=chat
const bool LexicalTokenTypeMapper::isType(LexicalTokenType t1, LexicalTokenType t2) {
	std::unordered_map<LexicalTokenType, std::vector<LexicalTokenType>> lexicalTokenTypes = {
		// Symbols
		{LexicalTokenType::SYMBOL_OPEN_BRACE, {LexicalTokenType::SYMBOL_OPEN_BRACE}},
		{LexicalTokenType::SYMBOL_CLOSE_BRACE, {LexicalTokenType::SYMBOL_CLOSE_BRACE}},
		{LexicalTokenType::SYMBOL_OPEN_PAREN, {LexicalTokenType::SYMBOL_OPEN_PAREN}},
		{LexicalTokenType::SYMBOL_CLOSE_PAREN, {LexicalTokenType::SYMBOL_CLOSE_PAREN}},
		{LexicalTokenType::SYMBOL_SEMICOLON, {LexicalTokenType::SYMBOL_SEMICOLON}},

		// Operators
		{LexicalTokenType::OPERATOR_ASSIGN, {LexicalTokenType::OPERATOR_ASSIGN}},
		{LexicalTokenType::OPERATOR_NOT, {LexicalTokenType::OPERATOR_NOT}},
		{LexicalTokenType::OPERATOR_AND, {LexicalTokenType::OPERATOR_CONDITIONAL, LexicalTokenType::OPERATOR_AND}},
		{LexicalTokenType::OPERATOR_OR, {LexicalTokenType::OPERATOR_CONDITIONAL, LexicalTokenType::OPERATOR_OR}},
		{LexicalTokenType::OPERATOR_GREATER, {LexicalTokenType::OPERATOR_RELATIONAL, LexicalTokenType::OPERATOR_GREATER}},
		{LexicalTokenType::OPERATOR_GREATER_EQUAL, {LexicalTokenType::OPERATOR_RELATIONAL, LexicalTokenType::OPERATOR_GREATER_EQUAL}},
		{LexicalTokenType::OPERATOR_LESS, {LexicalTokenType::OPERATOR_RELATIONAL, LexicalTokenType::OPERATOR_LESS}},
		{LexicalTokenType::OPERATOR_LESS_EQUAL, {LexicalTokenType::OPERATOR_RELATIONAL, LexicalTokenType::OPERATOR_LESS_EQUAL}},
		{LexicalTokenType::OPERATOR_IS_EQUAL, {LexicalTokenType::OPERATOR_RELATIONAL, LexicalTokenType::OPERATOR_IS_EQUAL}},
		{LexicalTokenType::OPERATOR_NOT_EQUAL, {LexicalTokenType::OPERATOR_RELATIONAL, LexicalTokenType::OPERATOR_NOT_EQUAL}},
		{LexicalTokenType::OPERATOR_PLUS, {LexicalTokenType::OPERATOR_EXPR, LexicalTokenType::OPERATOR_PLUS}},
		{LexicalTokenType::OPERATOR_MINUS, {LexicalTokenType::OPERATOR_EXPR, LexicalTokenType::OPERATOR_MINUS}},
		{LexicalTokenType::OPERATOR_MULTIPLY, {LexicalTokenType::OPERATOR_TERM, LexicalTokenType::OPERATOR_MULTIPLY}},
		{LexicalTokenType::OPERATOR_DIVIDE, {LexicalTokenType::OPERATOR_TERM, LexicalTokenType::OPERATOR_DIVIDE}},
		{LexicalTokenType::OPERATOR_MODULO, {LexicalTokenType::OPERATOR_TERM, LexicalTokenType::OPERATOR_MODULO}},

		// Keywords
		{LexicalTokenType::KEYWORD_PROCEDURE,{LexicalTokenType::KEYWORD_PROCEDURE,LexicalTokenType::NAME}},
		{LexicalTokenType::KEYWORD_WHILE,{LexicalTokenType::KEYWORD_WHILE,LexicalTokenType::NAME}},
		{LexicalTokenType::KEYWORD_IF,{LexicalTokenType::KEYWORD_IF,LexicalTokenType::NAME}},
		{LexicalTokenType::KEYWORD_THEN,{LexicalTokenType::KEYWORD_THEN,LexicalTokenType::NAME}},
		{LexicalTokenType::KEYWORD_ELSE,{LexicalTokenType::KEYWORD_ELSE,LexicalTokenType::NAME}},
		{LexicalTokenType::KEYWORD_READ,{LexicalTokenType::KEYWORD_READ,LexicalTokenType::NAME}},
		{LexicalTokenType::KEYWORD_CALL,{LexicalTokenType::KEYWORD_CALL,LexicalTokenType::NAME}},
		{LexicalTokenType::KEYWORD_PRINT,{LexicalTokenType::KEYWORD_PRINT,LexicalTokenType::NAME}},

		// General Tokens
		{LexicalTokenType::INTEGER,{LexicalTokenType::INTEGER}},
		{LexicalTokenType::NAME,{LexicalTokenType::NAME}},
		{LexicalTokenType::WHITESPACE,{LexicalTokenType::WHITESPACE}},
		{LexicalTokenType::NEW_LINE,{LexicalTokenType::NEW_LINE}},

		// Error Token and Null Token
		{LexicalTokenType::ERROR,{LexicalTokenType::ERROR}},
		{LexicalTokenType::NULL_TOKEN,{LexicalTokenType::NULL_TOKEN}}
	};

	auto search = lexicalTokenTypes.find(t1);

	if (search != lexicalTokenTypes.end()) {
		// Key exists, search the TokenType in the vector
		auto& vec = search->second;

		if (std::find(vec.begin(), vec.end(), t2) != vec.end()) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}
// ai-gen end
