#include "qps/parser/Tokenizer.h"
#include "catch.hpp"

using namespace std;

TEST_CASE("Modifies with valid statement and variable") {
    Tokenizer tokenizer("stmt s; variable v; Select s such that Modifies(s, v)");
    vector<Token> tokens = tokenizer.tokenize();

    REQUIRE(tokens.size() == 16);  // Expecting 16 tokens


    REQUIRE((tokens[0].getType() == TokenType::DesignEntity && tokens[0].getValue() == "stmt"));
    REQUIRE((tokens[1].getType() == TokenType::IDENT && tokens[1].getValue() == "s"));
    REQUIRE((tokens[2].getType() == TokenType::Semicolon && tokens[2].getValue() == ";"));
    REQUIRE((tokens[3].getType() == TokenType::DesignEntity && tokens[3].getValue() == "variable"));
    REQUIRE((tokens[4].getType() == TokenType::IDENT && tokens[4].getValue() == "v"));
    REQUIRE((tokens[5].getType() == TokenType::Semicolon && tokens[5].getValue() == ";"));
    REQUIRE((tokens[6].getType() == TokenType::SelectKeyword && tokens[6].getValue() == "Select"));
    REQUIRE((tokens[7].getType() == TokenType::IDENT && tokens[7].getValue() == "s"));
    REQUIRE((tokens[8].getType() == TokenType::SuchKeyword && tokens[8].getValue() == "such"));
    REQUIRE((tokens[9].getType() == TokenType::ThatKeyword && tokens[9].getValue() == "that"));
    REQUIRE((tokens[10].getType() == TokenType::Modifies && tokens[10].getValue() == "Modifies"));
    REQUIRE((tokens[11].getType() == TokenType::Lparenthesis && tokens[11].getValue() == "("));
    REQUIRE((tokens[12].getType() == TokenType::IDENT && tokens[12].getValue() == "s"));
    REQUIRE((tokens[13].getType() == TokenType::Comma && tokens[13].getValue() == ","));
    REQUIRE((tokens[14].getType() == TokenType::IDENT && tokens[14].getValue() == "v"));
    REQUIRE((tokens[15].getType() == TokenType::Rparenthesis && tokens[15].getValue() == ")"));

    REQUIRE(tokens[0].getType() == TokenType::DesignEntity);
    REQUIRE(tokens[0].getValue() == "stmt");

    REQUIRE(tokens[1].getType() == TokenType::IDENT);
    REQUIRE(tokens[1].getValue() == "s");

    REQUIRE(tokens[2].getType() == TokenType::Semicolon);
    REQUIRE(tokens[2].getValue() == ";");

    REQUIRE(tokens[3].getType() == TokenType::DesignEntity);
    REQUIRE(tokens[3].getValue() == "variable");

    REQUIRE(tokens[4].getType() == TokenType::IDENT);
    REQUIRE(tokens[4].getValue() == "v");

    REQUIRE(tokens[5].getType() == TokenType::Semicolon);
    REQUIRE(tokens[5].getValue() == ";");

    REQUIRE(tokens[6].getType() == TokenType::SelectKeyword);
    REQUIRE(tokens[6].getValue() == "Select");

    REQUIRE(tokens[7].getType() == TokenType::IDENT);
    REQUIRE(tokens[7].getValue() == "s");

    REQUIRE(tokens[8].getType() == TokenType::SuchKeyword);
    REQUIRE(tokens[8].getValue() == "such");

    REQUIRE(tokens[9].getType() == TokenType::ThatKeyword);
    REQUIRE(tokens[9].getValue() == "that");

    REQUIRE(tokens[10].getType() == TokenType::Modifies);
    REQUIRE(tokens[10].getValue() == "Modifies");

    REQUIRE(tokens[11].getType() == TokenType::Lparenthesis);
    REQUIRE(tokens[11].getValue() == "(");

    REQUIRE(tokens[12].getType() == TokenType::IDENT);
    REQUIRE(tokens[12].getValue() == "s");

    REQUIRE(tokens[13].getType() == TokenType::Comma);
    REQUIRE(tokens[13].getValue() == ",");

    REQUIRE(tokens[14].getType() == TokenType::IDENT);
    REQUIRE(tokens[14].getValue() == "v");

    REQUIRE(tokens[15].getType() == TokenType::Rparenthesis);
    REQUIRE(tokens[15].getValue() == ")");
}


TEST_CASE("Modifies with invalid statement number") {
    REQUIRE(Tokenizer("stmt s; Select s such that Modifies(-1, \"x\")").tokenize()[9].getType() ==
        TokenType::SyntaxError);
}

TEST_CASE("Uses with invalid IDENT") {
    REQUIRE(Tokenizer("stmt 1a; Select s such that Uses(-1, \"x\")").tokenize()[1].getType() ==
            TokenType::SyntaxError);
}

TEST_CASE("Follows with invalid quotes") {



    REQUIRE(Tokenizer("stmt a1; Select s such that Uses(1, \"x)").tokenize()[11].getType() ==
            TokenType::SyntaxError);
}


TEST_CASE("Modifies with quoted variable") {
    Tokenizer tokenizer("stmt s; Select s such that Modifies(s, \"existentVar\")");
    vector<Token> tokens = tokenizer.tokenize();

    REQUIRE(tokens.size() == 13);  // Expecting 13 tokens

    REQUIRE((tokens[0].getType() == TokenType::DesignEntity && tokens[0].getValue() == "stmt"));
    REQUIRE((tokens[1].getType() == TokenType::IDENT && tokens[1].getValue() == "s"));
    REQUIRE((tokens[2].getType() == TokenType::Semicolon && tokens[2].getValue() == ";"));
    REQUIRE((tokens[3].getType() == TokenType::SelectKeyword && tokens[3].getValue() == "Select"));
    REQUIRE((tokens[4].getType() == TokenType::IDENT && tokens[4].getValue() == "s"));
    REQUIRE((tokens[5].getType() == TokenType::SuchKeyword && tokens[5].getValue() == "such"));
    REQUIRE((tokens[6].getType() == TokenType::ThatKeyword && tokens[6].getValue() == "that"));
    REQUIRE((tokens[7].getType() == TokenType::Modifies && tokens[7].getValue() == "Modifies"));
    REQUIRE((tokens[8].getType() == TokenType::Lparenthesis && tokens[8].getValue() == "("));
    REQUIRE((tokens[9].getType() == TokenType::IDENT && tokens[9].getValue() == "s"));
    REQUIRE((tokens[10].getType() == TokenType::Comma && tokens[10].getValue() == ","));
    REQUIRE((tokens[11].getType() == TokenType::QuoutIDENT && tokens[11].getValue() == "\"existentVar\""));
    REQUIRE((tokens[12].getType() == TokenType::Rparenthesis && tokens[12].getValue() == ")"));

    REQUIRE(tokens[0].getType() == TokenType::DesignEntity);
    REQUIRE(tokens[0].getValue() == "stmt");

    REQUIRE(tokens[1].getType() == TokenType::IDENT);
    REQUIRE(tokens[1].getValue() == "s");

    REQUIRE(tokens[2].getType() == TokenType::Semicolon);
    REQUIRE(tokens[2].getValue() == ";");

    REQUIRE(tokens[3].getType() == TokenType::SelectKeyword);
    REQUIRE(tokens[3].getValue() == "Select");

    REQUIRE(tokens[4].getType() == TokenType::IDENT);
    REQUIRE(tokens[4].getValue() == "s");

    REQUIRE(tokens[5].getType() == TokenType::SuchKeyword);
    REQUIRE(tokens[5].getValue() == "such");

    REQUIRE(tokens[6].getType() == TokenType::ThatKeyword);
    REQUIRE(tokens[6].getValue() == "that");

    REQUIRE(tokens[7].getType() == TokenType::Modifies);
    REQUIRE(tokens[7].getValue() == "Modifies");

    REQUIRE(tokens[8].getType() == TokenType::Lparenthesis);
    REQUIRE(tokens[8].getValue() == "(");

    REQUIRE(tokens[9].getType() == TokenType::IDENT);
    REQUIRE(tokens[9].getValue() == "s");

    REQUIRE(tokens[10].getType() == TokenType::Comma);
    REQUIRE(tokens[10].getValue() == ",");

    REQUIRE(tokens[11].getType() == TokenType::QuoutIDENT);
    REQUIRE(tokens[11].getValue() == "\"existentVar\"");

    REQUIRE(tokens[12].getType() == TokenType::Rparenthesis);
    REQUIRE(tokens[12].getValue() == ")");
}


TEST_CASE("Pattern with variable and constant") {
    Tokenizer tokenizer("assign a; Select a pattern a(\"x\", \"1\")");
    vector<Token> tokens = tokenizer.tokenize();

    REQUIRE(tokens.size() == 12);  // Expecting 12 tokens

    REQUIRE((tokens[0].getType() == TokenType::DesignEntity && tokens[0].getValue() == "assign"));
    REQUIRE((tokens[1].getType() == TokenType::IDENT && tokens[1].getValue() == "a"));
    REQUIRE((tokens[2].getType() == TokenType::Semicolon && tokens[2].getValue() == ";"));
    REQUIRE((tokens[3].getType() == TokenType::SelectKeyword && tokens[3].getValue() == "Select"));
    REQUIRE((tokens[4].getType() == TokenType::IDENT && tokens[4].getValue() == "a"));
    REQUIRE((tokens[5].getType() == TokenType::PatternKeyword && tokens[5].getValue() == "pattern"));
    REQUIRE((tokens[6].getType() == TokenType::IDENT && tokens[6].getValue() == "a"));
    REQUIRE((tokens[7].getType() == TokenType::Lparenthesis && tokens[7].getValue() == "("));
    REQUIRE((tokens[8].getType() == TokenType::QuoutIDENT && tokens[8].getValue() == "\"x\""));
    REQUIRE((tokens[9].getType() == TokenType::Comma && tokens[9].getValue() == ","));
    REQUIRE((tokens[10].getType() == TokenType::QuoutConst && tokens[10].getValue() == "\"1\""));

    REQUIRE(tokens[0].getType() == TokenType::DesignEntity);
    REQUIRE(tokens[0].getValue() == "assign");

    REQUIRE(tokens[1].getType() == TokenType::IDENT);
    REQUIRE(tokens[1].getValue() == "a");

    REQUIRE(tokens[2].getType() == TokenType::Semicolon);
    REQUIRE(tokens[2].getValue() == ";");

    REQUIRE(tokens[3].getType() == TokenType::SelectKeyword);
    REQUIRE(tokens[3].getValue() == "Select");

    REQUIRE(tokens[4].getType() == TokenType::IDENT);
    REQUIRE(tokens[4].getValue() == "a");

    REQUIRE(tokens[5].getType() == TokenType::PatternKeyword);
    REQUIRE(tokens[5].getValue() == "pattern");

    REQUIRE(tokens[6].getType() == TokenType::IDENT);
    REQUIRE(tokens[6].getValue() == "a");

    REQUIRE(tokens[7].getType() == TokenType::Lparenthesis);
    REQUIRE(tokens[7].getValue() == "(");

    REQUIRE(tokens[8].getType() == TokenType::QuoutIDENT);
    REQUIRE(tokens[8].getValue() == "\"x\"");

    REQUIRE(tokens[9].getType() == TokenType::Comma);
    REQUIRE(tokens[9].getValue() == ",");

    REQUIRE(tokens[10].getType() == TokenType::QuoutConst);
    REQUIRE(tokens[10].getValue() == "\"1\"");

    REQUIRE(tokens[11].getType() == TokenType::Rparenthesis);
    REQUIRE(tokens[11].getValue() == ")");
}

TEST_CASE("quoted constant with wildcards") {
    Tokenizer tokenizer("assign a; Select a pattern a(_, _\"1\"_)");
    vector<Token> tokens = tokenizer.tokenize();

    REQUIRE(tokens.size() == 14);  // Expecting 14 tokens

    REQUIRE(tokens[0].getType() == TokenType::DesignEntity);
    REQUIRE(tokens[0].getValue() == "assign");

    REQUIRE(tokens[1].getType() == TokenType::IDENT);
    REQUIRE(tokens[1].getValue() == "a");

    REQUIRE(tokens[2].getType() == TokenType::Semicolon);
    REQUIRE(tokens[2].getValue() == ";");

    REQUIRE(tokens[3].getType() == TokenType::SelectKeyword);
    REQUIRE(tokens[3].getValue() == "Select");

    REQUIRE(tokens[4].getType() == TokenType::IDENT);
    REQUIRE(tokens[4].getValue() == "a");

    REQUIRE(tokens[5].getType() == TokenType::PatternKeyword);
    REQUIRE(tokens[5].getValue() == "pattern");

    REQUIRE(tokens[6].getType() == TokenType::IDENT);
    REQUIRE(tokens[6].getValue() == "a");

    REQUIRE(tokens[7].getType() == TokenType::Lparenthesis);
    REQUIRE(tokens[7].getValue() == "(");

    REQUIRE(tokens[8].getType() == TokenType::Wildcard);
    REQUIRE(tokens[8].getValue() == "_");

    REQUIRE(tokens[9].getType() == TokenType::Comma);
    REQUIRE(tokens[9].getValue() == ",");

    REQUIRE(tokens[10].getType() == TokenType::Wildcard);
    REQUIRE(tokens[10].getValue() == "_");

    REQUIRE(tokens[11].getType() == TokenType::QuoutConst);
    REQUIRE(tokens[11].getValue() == "\"1\"");

    REQUIRE(tokens[12].getType() == TokenType::Wildcard);
    REQUIRE(tokens[12].getValue() == "_");

    REQUIRE(tokens[13].getType() == TokenType::Rparenthesis);
    REQUIRE(tokens[13].getValue() == ")");
}

TEST_CASE("Check unconventional naming tokenization") {
    Tokenizer tokenizer("stmt stmt; Select stmt");
    vector<Token> tokens = tokenizer.tokenize();

    REQUIRE(tokens.size() == 5);  // Expecting 5 tokens

    REQUIRE(tokens[0].getType() == TokenType::DesignEntity);
    REQUIRE(tokens[0].getValue() == "stmt");

    REQUIRE(tokens[1].getType() == TokenType::IDENT);
    REQUIRE(tokens[1].getValue() == "stmt");

    REQUIRE(tokens[2].getType() == TokenType::Semicolon);
    REQUIRE(tokens[2].getValue() == ";");

    REQUIRE(tokens[3].getType() == TokenType::SelectKeyword);
    REQUIRE(tokens[3].getValue() == "Select");

    REQUIRE(tokens[4].getType() == TokenType::IDENT);
    REQUIRE(tokens[4].getValue() == "stmt");


}

TEST_CASE("Check unconventional naming tokenization 2") {
    Tokenizer tokenizer("stmt Select; Select Select");
    vector<Token> tokens = tokenizer.tokenize();

    REQUIRE(tokens.size() == 5);  // Expecting 5 tokens

    REQUIRE(tokens[0].getType() == TokenType::DesignEntity);
    REQUIRE(tokens[0].getValue() == "stmt");

    REQUIRE(tokens[1].getType() == TokenType::IDENT);
    REQUIRE(tokens[1].getValue() == "Select");

    REQUIRE(tokens[2].getType() == TokenType::Semicolon);
    REQUIRE(tokens[2].getValue() == ";");

    REQUIRE(tokens[3].getType() == TokenType::SelectKeyword);
    REQUIRE(tokens[3].getValue() == "Select");

    REQUIRE(tokens[4].getType() == TokenType::IDENT);
    REQUIRE(tokens[4].getValue() == "Select");


}


TEST_CASE("Check unconventional naming tokenization 3") {
    Tokenizer tokenizer("stmt Follows; Select Follows such that Follows(1,2)");
    vector<Token> tokens = tokenizer.tokenize();

    REQUIRE(tokens.size() == 13);  // Expecting 5 tokens

    REQUIRE(tokens[0].getType() == TokenType::DesignEntity);
    REQUIRE(tokens[0].getValue() == "stmt");

    REQUIRE(tokens[1].getType() == TokenType::IDENT);
    REQUIRE(tokens[1].getValue() == "Follows");

    REQUIRE(tokens[2].getType() == TokenType::Semicolon);
    REQUIRE(tokens[2].getValue() == ";");

    REQUIRE(tokens[3].getType() == TokenType::SelectKeyword);
    REQUIRE(tokens[3].getValue() == "Select");

    REQUIRE(tokens[4].getType() == TokenType::IDENT);
    REQUIRE(tokens[4].getValue() == "Follows");

    REQUIRE(tokens[5].getType() == TokenType::SuchKeyword);
    REQUIRE(tokens[5].getValue() == "such");

    REQUIRE(tokens[6].getType() == TokenType::ThatKeyword);
    REQUIRE(tokens[6].getValue() == "that");

    REQUIRE(tokens[7].getType() == TokenType::Follows);
    REQUIRE(tokens[7].getValue() == "Follows");

    REQUIRE(tokens[8].getType() == TokenType::Lparenthesis);
    REQUIRE(tokens[8].getValue() == "(");

    REQUIRE(tokens[9].getType() == TokenType::INTEGER);
    REQUIRE(tokens[9].getValue() == "1");

    REQUIRE(tokens[10].getType() == TokenType::Comma);
    REQUIRE(tokens[10].getValue() == ",");

    REQUIRE(tokens[11].getType() == TokenType::INTEGER);
    REQUIRE(tokens[11].getValue() == "2");

    REQUIRE(tokens[12].getType() == TokenType::Rparenthesis);
    REQUIRE(tokens[12].getValue() == ")");

}

TEST_CASE("Check unconventional naming tokenization 4") {
    Tokenizer tokenizer("stmt Follows; Select Follows such that Follows(Follows,2)");
    vector<Token> tokens = tokenizer.tokenize();

    REQUIRE(tokens.size() == 13);  // Expecting 5 tokens

    REQUIRE(tokens[0].getType() == TokenType::DesignEntity);
    REQUIRE(tokens[0].getValue() == "stmt");

    REQUIRE(tokens[1].getType() == TokenType::IDENT);
    REQUIRE(tokens[1].getValue() == "Follows");

    REQUIRE(tokens[2].getType() == TokenType::Semicolon);
    REQUIRE(tokens[2].getValue() == ";");

    REQUIRE(tokens[3].getType() == TokenType::SelectKeyword);
    REQUIRE(tokens[3].getValue() == "Select");

    REQUIRE(tokens[4].getType() == TokenType::IDENT);
    REQUIRE(tokens[4].getValue() == "Follows");

    REQUIRE(tokens[5].getType() == TokenType::SuchKeyword);
    REQUIRE(tokens[5].getValue() == "such");

    REQUIRE(tokens[6].getType() == TokenType::ThatKeyword);
    REQUIRE(tokens[6].getValue() == "that");

    REQUIRE(tokens[7].getType() == TokenType::Follows);
    REQUIRE(tokens[7].getValue() == "Follows");

    REQUIRE(tokens[8].getType() == TokenType::Lparenthesis);
    REQUIRE(tokens[8].getValue() == "(");

    REQUIRE(tokens[9].getType() == TokenType::IDENT);
    REQUIRE(tokens[9].getValue() == "Follows");

    REQUIRE(tokens[10].getType() == TokenType::Comma);
    REQUIRE(tokens[10].getValue() == ",");

    REQUIRE(tokens[11].getType() == TokenType::INTEGER);
    REQUIRE(tokens[11].getValue() == "2");

    REQUIRE(tokens[12].getType() == TokenType::Rparenthesis);
    REQUIRE(tokens[12].getValue() == ")");

}

TEST_CASE("Check Tokenisation of quotedconstant >= 10") {
    Tokenizer tokenizer("assign a; Select a pattern a(_, _\"10\"_)");
    vector<Token> tokens = tokenizer.tokenize();

    std::vector<Token> tokensExpected = {
            Token(TokenType::DesignEntity, "assign"),
            Token(TokenType::IDENT, "a"),
            Token(TokenType::Semicolon, ";"),
            Token(TokenType::SelectKeyword, "Select"),
            Token(TokenType::IDENT, "a"),
            Token(TokenType::PatternKeyword, "pattern"),
            Token(TokenType::IDENT, "a"),
            Token(TokenType::Lparenthesis, "("),
            Token(TokenType::Wildcard, "_"),
            Token(TokenType::Comma, ","),
            Token(TokenType::Wildcard, "_"),
            Token(TokenType::QuoutConst, "\"10\""),
            Token(TokenType::Wildcard, "_"),
            Token(TokenType::Rparenthesis, ")")

    };

    REQUIRE(tokens.size() == 14);  // Expecting 14 tokens
    REQUIRE((tokens[0].getType() == TokenType::DesignEntity && tokens[0].getValue() == "assign"));
    REQUIRE((tokens[1].getType() == TokenType::IDENT && tokens[1].getValue() == "a"));
    REQUIRE((tokens[2].getType() == TokenType::Semicolon && tokens[2].getValue() == ";"));
    REQUIRE((tokens[3].getType() == TokenType::SelectKeyword && tokens[3].getValue() == "Select"));
    REQUIRE((tokens[4].getType() == TokenType::IDENT && tokens[4].getValue() == "a"));
    REQUIRE((tokens[5].getType() == TokenType::PatternKeyword && tokens[5].getValue() == "pattern"));
    REQUIRE((tokens[6].getType() == TokenType::IDENT && tokens[6].getValue() == "a"));
    REQUIRE((tokens[7].getType() == TokenType::Lparenthesis && tokens[7].getValue() == "("));
    REQUIRE((tokens[8].getType() == TokenType::Wildcard && tokens[8].getValue() == "_"));
    REQUIRE((tokens[9].getType() == TokenType::Comma && tokens[9].getValue() == ","));
    REQUIRE((tokens[10].getType() == TokenType::Wildcard && tokens[10].getValue() == "_"));
    REQUIRE((tokens[11].getType() == TokenType::QuoutConst && tokens[11].getValue() == "\"10\""));
    REQUIRE((tokens[12].getType() == TokenType::Wildcard && tokens[12].getValue() == "_"));
    REQUIRE((tokens[13].getType() == TokenType::Rparenthesis && tokens[13].getValue() == ")"));

}


TEST_CASE("Check if Tokenisation of quotedconstant < 10 is correct") {
    Tokenizer tokenizer("assign a; Select a pattern a(\"z\", _\"1\"_)");
    vector<Token> tokens = tokenizer.tokenize();

    std::vector<Token> tokensExpected = {
            Token(TokenType::DesignEntity, "assign"),
            Token(TokenType::IDENT, "a"),
            Token(TokenType::Semicolon, ";"),
            Token(TokenType::SelectKeyword, "Select"),
            Token(TokenType::IDENT, "a"),
            Token(TokenType::PatternKeyword, "pattern"),
            Token(TokenType::IDENT, "a"),
            Token(TokenType::Lparenthesis, "("),
            Token(TokenType::QuoutIDENT, "\"z\""),
            Token(TokenType::Comma, ","),
            Token(TokenType::Wildcard, "_"),
            Token(TokenType::QuoutConst, "\"1\""),
            Token(TokenType::Wildcard, "_"),
            Token(TokenType::Rparenthesis, ")")

    };

    REQUIRE(tokens.size() == 14);  // Expecting 14 tokens
    REQUIRE((tokens[0].getType() == TokenType::DesignEntity && tokens[0].getValue() == "assign"));
    REQUIRE((tokens[1].getType() == TokenType::IDENT && tokens[1].getValue() == "a"));
    REQUIRE((tokens[2].getType() == TokenType::Semicolon && tokens[2].getValue() == ";"));
    REQUIRE((tokens[3].getType() == TokenType::SelectKeyword && tokens[3].getValue() == "Select"));
    REQUIRE((tokens[4].getType() == TokenType::IDENT && tokens[4].getValue() == "a"));
    REQUIRE((tokens[5].getType() == TokenType::PatternKeyword && tokens[5].getValue() == "pattern"));
    REQUIRE((tokens[6].getType() == TokenType::IDENT && tokens[6].getValue() == "a"));
    REQUIRE((tokens[7].getType() == TokenType::Lparenthesis && tokens[7].getValue() == "("));
    REQUIRE((tokens[8].getType() == TokenType::QuoutIDENT && tokens[8].getValue() == "\"z\""));
    REQUIRE((tokens[9].getType() == TokenType::Comma && tokens[9].getValue() == ","));
    REQUIRE((tokens[10].getType() == TokenType::Wildcard && tokens[10].getValue() == "_"));
    REQUIRE((tokens[11].getType() == TokenType::QuoutConst && tokens[11].getValue() == "\"1\""));
    REQUIRE((tokens[12].getType() == TokenType::Wildcard && tokens[12].getValue() == "_"));
    REQUIRE((tokens[13].getType() == TokenType::Rparenthesis && tokens[13].getValue() == ")"));

}

TEST_CASE("Check if Tokenisation of 2 clauses is correct") {
    // Initialize tokenizer with the input string
    Tokenizer tokenizer("assign a; Select a such that Follows(1, 2) pattern a(_, _)");
    vector<Token> tokens = tokenizer.tokenize();

    // Check the total number of tokens
    REQUIRE(tokens.size() == 20);  // Expecting 20 tokens

    // Check the first set of tokens
    REQUIRE(tokens[0].getType() == TokenType::DesignEntity);
    REQUIRE(tokens[0].getValue() == "assign");
    REQUIRE(tokens[1].getType() == TokenType::IDENT);
    REQUIRE(tokens[1].getValue() == "a");
    REQUIRE(tokens[2].getType() == TokenType::Semicolon);
    REQUIRE(tokens[2].getValue() == ";");
    REQUIRE(tokens[3].getType() == TokenType::SelectKeyword);
    REQUIRE(tokens[3].getValue() == "Select");
    REQUIRE(tokens[4].getType() == TokenType::IDENT);
    REQUIRE(tokens[4].getValue() == "a");

    // Check 'such that' tokens
    REQUIRE(tokens[5].getType() == TokenType::SuchKeyword);
    REQUIRE(tokens[5].getValue() == "such");
    REQUIRE(tokens[6].getType() == TokenType::ThatKeyword);
    REQUIRE(tokens[6].getValue() == "that");

    // Check 'Follows' function tokens
    REQUIRE(tokens[7].getType() == TokenType::Follows);
    REQUIRE(tokens[7].getValue() == "Follows");
    REQUIRE(tokens[8].getType() == TokenType::Lparenthesis);
    REQUIRE(tokens[8].getValue() == "(");
    REQUIRE(tokens[9].getType() == TokenType::INTEGER);
    REQUIRE(tokens[9].getValue() == "1");
    REQUIRE(tokens[10].getType() == TokenType::Comma);
    REQUIRE(tokens[10].getValue() == ",");
    REQUIRE(tokens[11].getType() == TokenType::INTEGER);
    REQUIRE(tokens[11].getValue() == "2");
    REQUIRE(tokens[12].getType() == TokenType::Rparenthesis);
    REQUIRE(tokens[12].getValue() == ")");

    // Check 'pattern' tokens
    REQUIRE(tokens[13].getType() == TokenType::PatternKeyword);
    REQUIRE(tokens[13].getValue() == "pattern");
    REQUIRE(tokens[14].getType() == TokenType::IDENT);
    REQUIRE(tokens[14].getValue() == "a");
    REQUIRE(tokens[15].getType() == TokenType::Lparenthesis);
    REQUIRE(tokens[15].getValue() == "(");
    REQUIRE(tokens[16].getType() == TokenType::Wildcard);
    REQUIRE(tokens[16].getValue() == "_");
    REQUIRE(tokens[17].getType() == TokenType::Comma);
    REQUIRE(tokens[17].getValue() == ",");
    REQUIRE(tokens[18].getType() == TokenType::Wildcard);
    REQUIRE(tokens[18].getValue() == "_");
    REQUIRE(tokens[19].getType() == TokenType::Rparenthesis);
    REQUIRE(tokens[19].getValue() == ")");
}



TEST_CASE("Check if Tokenisation of quouted identifier for long names is correct") {
    Tokenizer tokenizer("assign a; Select a such that Modifies(a, _) pattern a(_, _\"abc\"_)");
    vector<Token> tokens = tokenizer.tokenize();

    // Check the total number of tokens
    REQUIRE(tokens.size() == 22);  // Expecting 22 tokens

    // Check the first set of tokens
    REQUIRE(tokens[0].getType() == TokenType::DesignEntity);
    REQUIRE(tokens[0].getValue() == "assign");
    REQUIRE(tokens[1].getType() == TokenType::IDENT);
    REQUIRE(tokens[1].getValue() == "a");
    REQUIRE(tokens[2].getType() == TokenType::Semicolon);
    REQUIRE(tokens[2].getValue() == ";");
    REQUIRE(tokens[3].getType() == TokenType::SelectKeyword);
    REQUIRE(tokens[3].getValue() == "Select");
    REQUIRE(tokens[4].getType() == TokenType::IDENT);
    REQUIRE(tokens[4].getValue() == "a");

    // Check 'such that' tokens
    REQUIRE(tokens[5].getType() == TokenType::SuchKeyword);
    REQUIRE(tokens[5].getValue() == "such");
    REQUIRE(tokens[6].getType() == TokenType::ThatKeyword);
    REQUIRE(tokens[6].getValue() == "that");

    // Check 'Modifies' function tokens
    REQUIRE(tokens[7].getType() == TokenType::Modifies);
    REQUIRE(tokens[7].getValue() == "Modifies");
    REQUIRE(tokens[8].getType() == TokenType::Lparenthesis);
    REQUIRE(tokens[8].getValue() == "(");
    REQUIRE(tokens[9].getType() == TokenType::IDENT);
    REQUIRE(tokens[9].getValue() == "a");
    REQUIRE(tokens[10].getType() == TokenType::Comma);
    REQUIRE(tokens[10].getValue() == ",");
    REQUIRE(tokens[11].getType() == TokenType::Wildcard);
    REQUIRE(tokens[11].getValue() == "_");
    REQUIRE(tokens[12].getType() == TokenType::Rparenthesis);
    REQUIRE(tokens[12].getValue() == ")");

    // Check 'pattern' tokens
    REQUIRE(tokens[13].getType() == TokenType::PatternKeyword);
    REQUIRE(tokens[13].getValue() == "pattern");
    REQUIRE(tokens[14].getType() == TokenType::IDENT);
    REQUIRE(tokens[14].getValue() == "a");
    REQUIRE(tokens[15].getType() == TokenType::Lparenthesis);
    REQUIRE(tokens[15].getValue() == "(");
    REQUIRE(tokens[16].getType() == TokenType::Wildcard);
    REQUIRE(tokens[16].getValue() == "_");
    REQUIRE(tokens[17].getType() == TokenType::Comma);
    REQUIRE(tokens[17].getValue() == ",");
    REQUIRE(tokens[18].getType() == TokenType::Wildcard);
    REQUIRE(tokens[18].getValue() == "_");
    REQUIRE(tokens[19].getType() == TokenType::QuoutIDENT);
    REQUIRE(tokens[19].getValue() == "\"abc\"");
    REQUIRE(tokens[20].getType() == TokenType::Wildcard);
    REQUIRE(tokens[20].getValue() == "_");
    REQUIRE(tokens[21].getType() == TokenType::Rparenthesis);
    REQUIRE(tokens[21].getValue() == ")");
}
//
//stmt s1, s2;
//Select s1 so that Follows(s1, s2)









//TEST_CASE("Check if Tokenisation of expression spec") {
//    Tokenizer tokenizer("assign a; Select a pattern a(\"z\", _\"x + 1\"_)");
//    vector<Token> tokens = tokenizer.tokenize();
//
//
//    REQUIRE(tokens.size() == 14);  // Expecting 14 tokens
//    REQUIRE((tokens[0].getType() == TokenType::DesignEntity && tokens[0].getValue() == "assign"));
//    REQUIRE((tokens[1].getType() == TokenType::IDENT && tokens[1].getValue() == "a"));
//    REQUIRE((tokens[2].getType() == TokenType::Semicolon && tokens[2].getValue() == ";"));
//    REQUIRE((tokens[3].getType() == TokenType::SelectKeyword && tokens[3].getValue() == "Select"));
//    REQUIRE((tokens[4].getType() == TokenType::IDENT && tokens[4].getValue() == "a"));
//    REQUIRE((tokens[5].getType() == TokenType::PatternKeyword && tokens[5].getValue() == "pattern"));
//    REQUIRE((tokens[6].getType() == TokenType::IDENT && tokens[6].getValue() == "a"));
//    REQUIRE((tokens[7].getType() == TokenType::Lparenthesis && tokens[7].getValue() == "("));
//    REQUIRE((tokens[8].getType() == TokenType::QuoutIDENT && tokens[8].getValue() == "\"z\""));
//    REQUIRE((tokens[9].getType() == TokenType::Comma && tokens[9].getValue() == ","));
//    REQUIRE((tokens[10].getType() == TokenType::Wildcard && tokens[10].getValue() == "_"));
//    REQUIRE((tokens[11].getType() == TokenType::QuoutConst && tokens[11].getValue() == "\"1\""));
//    REQUIRE((tokens[12].getType() == TokenType::Wildcard && tokens[12].getValue() == "_"));
//    REQUIRE((tokens[13].getType() == TokenType::Rparenthesis && tokens[13].getValue() == ")"));
//
//}





