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

TEST_CASE("Check unconventional naming tokenization 5") {
    Tokenizer tokenizer("assign BOOLEAN; Select BOOLEAN pattern BOOLEAN(_,_)");
    vector<Token> tokens = tokenizer.tokenize();

    REQUIRE(tokens.size() == 12);  // Expecting 5 tokens

    REQUIRE(tokens[0].getType() == TokenType::DesignEntity);
    REQUIRE(tokens[0].getValue() == "assign");

    REQUIRE(tokens[1].getType() == TokenType::IDENT);
    REQUIRE(tokens[1].getValue() == "BOOLEAN");

    REQUIRE(tokens[2].getType() == TokenType::Semicolon);
    REQUIRE(tokens[2].getValue() == ";");

    REQUIRE(tokens[3].getType() == TokenType::SelectKeyword);
    REQUIRE(tokens[3].getValue() == "Select");

    REQUIRE(tokens[4].getType() == TokenType::IDENT);
    REQUIRE(tokens[4].getValue() == "BOOLEAN");

    REQUIRE(tokens[5].getType() == TokenType::PatternKeyword);
    REQUIRE(tokens[5].getValue() == "pattern");

    REQUIRE(tokens[6].getType() == TokenType::IDENT);
    REQUIRE(tokens[6].getValue() == "BOOLEAN");

    REQUIRE(tokens[7].getType() == TokenType::Lparenthesis);
    REQUIRE(tokens[7].getValue() == "(");

    REQUIRE(tokens[8].getType() == TokenType::Wildcard);
    REQUIRE(tokens[8].getValue() == "_");

    REQUIRE(tokens[9].getType() == TokenType::Comma);
    REQUIRE(tokens[9].getValue() == ",");

    REQUIRE(tokens[10].getType() == TokenType::Wildcard);
    REQUIRE(tokens[10].getValue() == "_");

    REQUIRE(tokens[11].getType() == TokenType::Rparenthesis);
    REQUIRE(tokens[11].getValue() == ")");


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


TEST_CASE("procedure p, q; Select <p.stmt#, q.procName> such that Calls (p, q)") {
    // Initialize tokenizer with the input string
    Tokenizer tokenizer("procedure p, q; Select <p.stmt#, q.procName> such that Calls (p, q)");
    vector<Token> tokens = tokenizer.tokenize();

    // Check the total number of tokens
    REQUIRE(tokens.size() == 23);  // Expecting 22 tokens

    // Check the first set of tokens
    REQUIRE(tokens[0].getType() == TokenType::DesignEntity);
    REQUIRE(tokens[0].getValue() == "procedure");
    REQUIRE(tokens[1].getType() == TokenType::IDENT);
    REQUIRE(tokens[1].getValue() == "p");
    REQUIRE(tokens[2].getType() == TokenType::Comma);
    REQUIRE(tokens[2].getValue() == ",");
    REQUIRE(tokens[3].getType() == TokenType::IDENT);
    REQUIRE(tokens[3].getValue() == "q");
    REQUIRE(tokens[4].getType() == TokenType::Semicolon);
    REQUIRE(tokens[4].getValue() == ";");
    REQUIRE(tokens[5].getType() == TokenType::SelectKeyword);
    REQUIRE(tokens[5].getValue() == "Select");
    REQUIRE(tokens[6].getType() == TokenType::LeftAngleBracket);
    REQUIRE(tokens[6].getValue() == "<");
    REQUIRE(tokens[7].getType() == TokenType::IDENT);
    REQUIRE(tokens[7].getValue() == "p");
    REQUIRE(tokens[8].getType() == TokenType::Dot);
    REQUIRE(tokens[8].getValue() == ".");
    REQUIRE(tokens[9].getType() == TokenType::AttrName);
    REQUIRE(tokens[9].getValue() == "stmt#");
    REQUIRE(tokens[10].getType() == TokenType::Comma);
    REQUIRE(tokens[10].getValue() == ",");
    REQUIRE(tokens[11].getType() == TokenType::IDENT);
    REQUIRE(tokens[11].getValue() == "q");
    REQUIRE(tokens[12].getType() == TokenType::Dot);
    REQUIRE(tokens[12].getValue() == ".");
    REQUIRE(tokens[13].getType() == TokenType::AttrName);
    REQUIRE(tokens[13].getValue() == "procName");
    REQUIRE(tokens[14].getType() == TokenType::RightAngleBracket);
    REQUIRE(tokens[14].getValue() == ">");
    REQUIRE(tokens[15].getType() == TokenType::SuchKeyword);
    REQUIRE(tokens[15].getValue() == "such");
    REQUIRE(tokens[16].getType() == TokenType::ThatKeyword);
    REQUIRE(tokens[16].getValue() == "that");
    REQUIRE(tokens[17].getType() == TokenType::Calls);
    REQUIRE(tokens[17].getValue() == "Calls");
    REQUIRE(tokens[18].getType() == TokenType::Lparenthesis);
    REQUIRE(tokens[18].getValue() == "(");
    REQUIRE(tokens[19].getType() == TokenType::IDENT);
    REQUIRE(tokens[19].getValue() == "p");
    REQUIRE(tokens[20].getType() == TokenType::Comma);
    REQUIRE(tokens[20].getValue() == ",");
    REQUIRE(tokens[21].getType() == TokenType::IDENT);
    REQUIRE(tokens[21].getValue() == "q");
    REQUIRE(tokens[22].getType() == TokenType::Rparenthesis);
    REQUIRE(tokens[22].getValue() == ")");
}

TEST_CASE("assign a; while w; Select a pattern a(\"x\", _) such that Parent*(w, a) such that Next*(1, a)") {
    // Initialize tokenizer with the input string
    Tokenizer tokenizer("assign a; while w; Select a pattern a(\"x\", _) such that Parent*(w, a) such that Next*(1, a)");
    vector<Token> tokens = tokenizer.tokenize();

    // Check the total number of tokens
    REQUIRE(tokens.size() == 31);  // Expecting 27 tokens

    // Check each token against the expected output
    REQUIRE(tokens[0].getType() == TokenType::DesignEntity);
    REQUIRE(tokens[0].getValue() == "assign");
    REQUIRE(tokens[1].getType() == TokenType::IDENT);
    REQUIRE(tokens[1].getValue() == "a");
    REQUIRE(tokens[2].getType() == TokenType::Semicolon);
    REQUIRE(tokens[2].getValue() == ";");
    REQUIRE(tokens[3].getType() == TokenType::DesignEntity);
    REQUIRE(tokens[3].getValue() == "while");
    REQUIRE(tokens[4].getType() == TokenType::IDENT);
    REQUIRE(tokens[4].getValue() == "w");
    REQUIRE(tokens[5].getType() == TokenType::Semicolon);
    REQUIRE(tokens[5].getValue() == ";");
    REQUIRE(tokens[6].getType() == TokenType::SelectKeyword);
    REQUIRE(tokens[6].getValue() == "Select");
    REQUIRE(tokens[7].getType() == TokenType::IDENT);
    REQUIRE(tokens[7].getValue() == "a");
    REQUIRE(tokens[8].getType() == TokenType::PatternKeyword);
    REQUIRE(tokens[8].getValue() == "pattern");
    REQUIRE(tokens[9].getType() == TokenType::IDENT);
    REQUIRE(tokens[9].getValue() == "a");
    REQUIRE(tokens[10].getType() == TokenType::Lparenthesis);
    REQUIRE(tokens[10].getValue() == "(");
    REQUIRE(tokens[11].getType() == TokenType::QuoutIDENT);
    REQUIRE(tokens[11].getValue() == "\"x\"");
    REQUIRE(tokens[12].getType() == TokenType::Comma);
    REQUIRE(tokens[12].getValue() == ",");
    REQUIRE(tokens[13].getType() == TokenType::Wildcard);
    REQUIRE(tokens[13].getValue() == "_");
    REQUIRE(tokens[14].getType() == TokenType::Rparenthesis);
    REQUIRE(tokens[14].getValue() == ")");
    REQUIRE(tokens[15].getType() == TokenType::SuchKeyword);
    REQUIRE(tokens[15].getValue() == "such");
    REQUIRE(tokens[16].getType() == TokenType::ThatKeyword);
    REQUIRE(tokens[16].getValue() == "that");
    REQUIRE(tokens[17].getType() == TokenType::ParentT);
    REQUIRE(tokens[17].getValue() == "Parent*");
    REQUIRE(tokens[18].getType() == TokenType::Lparenthesis);
    REQUIRE(tokens[18].getValue() == "(");
    REQUIRE(tokens[19].getType() == TokenType::IDENT);
    REQUIRE(tokens[19].getValue() == "w");
    REQUIRE(tokens[20].getType() == TokenType::Comma);
    REQUIRE(tokens[20].getValue() == ",");
    REQUIRE(tokens[21].getType() == TokenType::IDENT);
    REQUIRE(tokens[21].getValue() == "a");
    REQUIRE(tokens[22].getType() == TokenType::Rparenthesis);
    REQUIRE(tokens[22].getValue() == ")");
    REQUIRE(tokens[23].getType() == TokenType::SuchKeyword);
    REQUIRE(tokens[23].getValue() == "such");
    REQUIRE(tokens[24].getType() == TokenType::ThatKeyword);
    REQUIRE(tokens[24].getValue() == "that");
    REQUIRE(tokens[25].getType() == TokenType::NextT);
    REQUIRE(tokens[25].getValue() == "Next*");
    REQUIRE(tokens[26].getType() == TokenType::Lparenthesis);
    REQUIRE(tokens[26].getValue() == "(");
    REQUIRE(tokens[27].getType() == TokenType::INTEGER);
    REQUIRE(tokens[27].getValue() == "1");
    REQUIRE(tokens[28].getType() == TokenType::Comma);
    REQUIRE(tokens[28].getValue() == ",");
    REQUIRE(tokens[29].getType() == TokenType::IDENT);
    REQUIRE(tokens[29].getValue() == "a");
    REQUIRE(tokens[30].getType() == TokenType::Rparenthesis);
    REQUIRE(tokens[30].getValue() == ")");
}


TEST_CASE("assign a; while w; Select a such that Modifies (a, \"x\") and Next* (1, a)") {
    // Initialize tokenizer with the input string
    Tokenizer tokenizer("assign a; while w; Select a such that Modifies(a, \"x\") and Next*(1, a)");
    vector<Token> tokens = tokenizer.tokenize();

    // Check the total number of tokens
    REQUIRE(tokens.size() == 23);  // Expecting 21 tokens

    // Check each token against the expected output
    REQUIRE(tokens[0].getType() == TokenType::DesignEntity);
    REQUIRE(tokens[0].getValue() == "assign");
    REQUIRE(tokens[1].getType() == TokenType::IDENT);
    REQUIRE(tokens[1].getValue() == "a");
    REQUIRE(tokens[2].getType() == TokenType::Semicolon);
    REQUIRE(tokens[2].getValue() == ";");
    REQUIRE(tokens[3].getType() == TokenType::DesignEntity);
    REQUIRE(tokens[3].getValue() == "while");
    REQUIRE(tokens[4].getType() == TokenType::IDENT);
    REQUIRE(tokens[4].getValue() == "w");
    REQUIRE(tokens[5].getType() == TokenType::Semicolon);
    REQUIRE(tokens[5].getValue() == ";");
    REQUIRE(tokens[6].getType() == TokenType::SelectKeyword);
    REQUIRE(tokens[6].getValue() == "Select");
    REQUIRE(tokens[7].getType() == TokenType::IDENT);
    REQUIRE(tokens[7].getValue() == "a");
    REQUIRE(tokens[8].getType() == TokenType::SuchKeyword);
    REQUIRE(tokens[8].getValue() == "such");
    REQUIRE(tokens[9].getType() == TokenType::ThatKeyword);
    REQUIRE(tokens[9].getValue() == "that");
    REQUIRE(tokens[10].getType() == TokenType::Modifies);
    REQUIRE(tokens[10].getValue() == "Modifies");
    REQUIRE(tokens[11].getType() == TokenType::Lparenthesis);
    REQUIRE(tokens[11].getValue() == "(");
    REQUIRE(tokens[12].getType() == TokenType::IDENT);
    REQUIRE(tokens[12].getValue() == "a");
    REQUIRE(tokens[13].getType() == TokenType::Comma);
    REQUIRE(tokens[13].getValue() == ",");
    REQUIRE(tokens[14].getType() == TokenType::QuoutIDENT);
    REQUIRE(tokens[14].getValue() == "\"x\"");
    REQUIRE(tokens[15].getType() == TokenType::Rparenthesis);
    REQUIRE(tokens[15].getValue() == ")");
    REQUIRE(tokens[16].getType() == TokenType::AndKeyword);
    REQUIRE(tokens[16].getValue() == "such that");
    REQUIRE(tokens[17].getType() == TokenType::NextT);
    REQUIRE(tokens[17].getValue() == "Next*");
    REQUIRE(tokens[18].getType() == TokenType::Lparenthesis);
    REQUIRE(tokens[18].getValue() == "(");
    REQUIRE(tokens[19].getType() == TokenType::INTEGER);
    REQUIRE(tokens[19].getValue() == "1");
    REQUIRE(tokens[20].getType() == TokenType::Comma);
    REQUIRE(tokens[20].getValue() == ",");
    REQUIRE(tokens[21].getType() == TokenType::IDENT);
    REQUIRE(tokens[21].getValue() == "a");
    REQUIRE(tokens[22].getType() == TokenType::Rparenthesis);
    REQUIRE(tokens[22].getValue() == ")");
}

TEST_CASE("stmt s; Select BOOLEAN such that Follows(3, 4)") {
    // Initialize tokenizer with the input string
    Tokenizer tokenizer("stmt s; Select BOOLEAN such that Follows(3, 4)");
    vector<Token> tokens = tokenizer.tokenize();

    // Check the total number of tokens
    REQUIRE(tokens.size() == 13);  // Expecting 12 tokens

    // Validate each token against the expected output
    REQUIRE(tokens[0].getType() == TokenType::DesignEntity);
    REQUIRE(tokens[0].getValue() == "stmt");
    REQUIRE(tokens[1].getType() == TokenType::IDENT);
    REQUIRE(tokens[1].getValue() == "s");
    REQUIRE(tokens[2].getType() == TokenType::Semicolon);
    REQUIRE(tokens[2].getValue() == ";");
    REQUIRE(tokens[3].getType() == TokenType::SelectKeyword);
    REQUIRE(tokens[3].getValue() == "Select");
    REQUIRE(tokens[4].getType() == TokenType::BooleanKeyword);
    REQUIRE(tokens[4].getValue() == "BOOLEAN");
    REQUIRE(tokens[5].getType() == TokenType::SuchKeyword);
    REQUIRE(tokens[5].getValue() == "such");
    REQUIRE(tokens[6].getType() == TokenType::ThatKeyword);
    REQUIRE(tokens[6].getValue() == "that");
    REQUIRE(tokens[7].getType() == TokenType::Follows);
    REQUIRE(tokens[7].getValue() == "Follows");
    REQUIRE(tokens[8].getType() == TokenType::Lparenthesis);
    REQUIRE(tokens[8].getValue() == "(");
    REQUIRE(tokens[9].getType() == TokenType::INTEGER);
    REQUIRE(tokens[9].getValue() == "3");
    REQUIRE(tokens[10].getType() == TokenType::Comma);
    REQUIRE(tokens[10].getValue() == ",");
    REQUIRE(tokens[11].getType() == TokenType::INTEGER);
    REQUIRE(tokens[11].getValue() == "4");
    REQUIRE(tokens[12].getType() == TokenType::Rparenthesis);
    REQUIRE(tokens[12].getValue() == ")");
}

TEST_CASE("procedure p, q;Select p such that Calls(p, q) with q.procName = 'Third'") {
    // Initialize tokenizer with the input string
    Tokenizer tokenizer("procedure p, q; Select p such that Calls(p, q) with q.procName = \"Third\"");
    vector<Token> tokens = tokenizer.tokenize();

    // Check the total number of tokens
    REQUIRE(tokens.size() == 21);  // Expecting 22 tokens

    // Validate each token against the expected output
    REQUIRE(tokens[0].getType() == TokenType::DesignEntity);
    REQUIRE(tokens[0].getValue() == "procedure");
    REQUIRE(tokens[1].getType() == TokenType::IDENT);
    REQUIRE(tokens[1].getValue() == "p");
    REQUIRE(tokens[2].getType() == TokenType::Comma);
    REQUIRE(tokens[2].getValue() == ",");
    REQUIRE(tokens[3].getType() == TokenType::IDENT);
    REQUIRE(tokens[3].getValue() == "q");
    REQUIRE(tokens[4].getType() == TokenType::Semicolon);
    REQUIRE(tokens[4].getValue() == ";");
    REQUIRE(tokens[5].getType() == TokenType::SelectKeyword);
    REQUIRE(tokens[5].getValue() == "Select");
    REQUIRE(tokens[6].getType() == TokenType::IDENT);
    REQUIRE(tokens[6].getValue() == "p");
    REQUIRE(tokens[7].getType() == TokenType::SuchKeyword);
    REQUIRE(tokens[7].getValue() == "such");
    REQUIRE(tokens[8].getType() == TokenType::ThatKeyword);
    REQUIRE(tokens[8].getValue() == "that");
    REQUIRE(tokens[9].getType() == TokenType::Calls);
    REQUIRE(tokens[9].getValue() == "Calls");
    REQUIRE(tokens[10].getType() == TokenType::Lparenthesis);
    REQUIRE(tokens[10].getValue() == "(");
    REQUIRE(tokens[11].getType() == TokenType::IDENT);
    REQUIRE(tokens[11].getValue() == "p");
    REQUIRE(tokens[12].getType() == TokenType::Comma);
    REQUIRE(tokens[12].getValue() == ",");
    REQUIRE(tokens[13].getType() == TokenType::IDENT);
    REQUIRE(tokens[13].getValue() == "q");
    REQUIRE(tokens[14].getType() == TokenType::Rparenthesis);
    REQUIRE(tokens[14].getValue() == ")");
    REQUIRE(tokens[15].getType() == TokenType::WithKeyword);
    REQUIRE(tokens[15].getValue() == "with");
    REQUIRE(tokens[16].getType() == TokenType::IDENT);
    REQUIRE(tokens[16].getValue() == "q");
    REQUIRE(tokens[17].getType() == TokenType::Dot);
    REQUIRE(tokens[17].getValue() == ".");
    REQUIRE(tokens[18].getType() == TokenType::AttrName);
    REQUIRE(tokens[18].getValue() == "procName");
    REQUIRE(tokens[19].getType() == TokenType::Equal);
    REQUIRE(tokens[19].getValue() == "=");
    REQUIRE(tokens[20].getType() == TokenType::QuoutIDENT);
    REQUIRE(tokens[20].getValue() == "\"Third\"");
    
}


TEST_CASE("Tokenization of spaces in quoutes") {
    Tokenizer tokenizer("assign a; Select a pattern a(_, _\" x\"_)");
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
            Token(TokenType::QuoutIDENT, "\"x\""),
            Token(TokenType::Wildcard, "_"),
            Token(TokenType::Rparenthesis, ")")

    };

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

    REQUIRE(tokens[11].getType() == TokenType::QuoutIDENT);
    REQUIRE(tokens[11].getValue() == "\"x\"");

    REQUIRE(tokens[12].getType() == TokenType::Wildcard);
    REQUIRE(tokens[12].getValue() == "_");

    REQUIRE(tokens[13].getType() == TokenType::Rparenthesis);
    REQUIRE(tokens[13].getValue() == ")");



}

TEST_CASE("Testing Select Select") {
    Tokenizer tokenizer("assign Select; Select Select pattern Select(_, _)");
    vector<Token> tokens = tokenizer.tokenize();

    REQUIRE(tokens.size() == 12);  // Expecting 14 tokens
    REQUIRE(tokens[0].getType() == TokenType::DesignEntity);
    REQUIRE(tokens[0].getValue() == "assign");

    REQUIRE(tokens[1].getType() == TokenType::IDENT);
    REQUIRE(tokens[1].getValue() == "Select");

    REQUIRE(tokens[2].getType() == TokenType::Semicolon);
    REQUIRE(tokens[2].getValue() == ";");

    REQUIRE(tokens[3].getType() == TokenType::SelectKeyword);
    REQUIRE(tokens[3].getValue() == "Select");

    REQUIRE(tokens[4].getType() == TokenType::IDENT);
    REQUIRE(tokens[4].getValue() == "Select");

    REQUIRE(tokens[5].getType() == TokenType::PatternKeyword);
    REQUIRE(tokens[5].getValue() == "pattern");

    REQUIRE(tokens[6].getType() == TokenType::IDENT);
    REQUIRE(tokens[6].getValue() == "Select");

    REQUIRE(tokens[7].getType() == TokenType::Lparenthesis);
    REQUIRE(tokens[7].getValue() == "(");

    REQUIRE(tokens[8].getType() == TokenType::Wildcard);
    REQUIRE(tokens[8].getValue() == "_");

    REQUIRE(tokens[9].getType() == TokenType::Comma);
    REQUIRE(tokens[9].getValue() == ",");

    REQUIRE(tokens[10].getType() == TokenType::Wildcard);
    REQUIRE(tokens[10].getValue() == "_");


    REQUIRE(tokens[11].getType() == TokenType::Rparenthesis);
    REQUIRE(tokens[11].getValue() == ")");

}

TEST_CASE("Testing Pattern with expressionSpec") {
    Tokenizer tokenizer("assign a; Select a pattern a(_, \"x+1+r\")");
    vector<Token> tokens = tokenizer.tokenize();

    REQUIRE(tokens.size() == 12);  // Expecting 11 tokens
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
    REQUIRE(tokens[10].getType() == TokenType::ExpressionSpec);
    REQUIRE(tokens[10].getValue() == "\"x+1+r\"");
    REQUIRE(tokens[11].getType() == TokenType::Rparenthesis);
    REQUIRE(tokens[11].getValue() == ")");

}

TEST_CASE("Testing with clause with attributes") {
    Tokenizer tokenizer("stmt s; assign a; Select s with s.stmt# = a.stmt#");
    vector<Token> tokens = tokenizer.tokenize();

    REQUIRE(tokens.size() == 16);  // Expecting 13 tokens
    REQUIRE(tokens[0].getType() == TokenType::DesignEntity);
    REQUIRE(tokens[0].getValue() == "stmt");

    REQUIRE(tokens[1].getType() == TokenType::IDENT);
    REQUIRE(tokens[1].getValue() == "s");

    REQUIRE(tokens[2].getType() == TokenType::Semicolon);
    REQUIRE(tokens[2].getValue() == ";");

    REQUIRE(tokens[3].getType() == TokenType::DesignEntity);
    REQUIRE(tokens[3].getValue() == "assign");

    REQUIRE(tokens[4].getType() == TokenType::IDENT);
    REQUIRE(tokens[4].getValue() == "a");

    REQUIRE(tokens[5].getType() == TokenType::Semicolon);
    REQUIRE(tokens[5].getValue() == ";");

    REQUIRE(tokens[6].getType() == TokenType::SelectKeyword);
    REQUIRE(tokens[6].getValue() == "Select");

    REQUIRE(tokens[7].getType() == TokenType::IDENT);
    REQUIRE(tokens[7].getValue() == "s");

    REQUIRE(tokens[8].getType() == TokenType::WithKeyword);
    REQUIRE(tokens[8].getValue() == "with");

    REQUIRE(tokens[9].getType() == TokenType::IDENT);
    REQUIRE(tokens[9].getValue() == "s");

    REQUIRE(tokens[10].getType() == TokenType::Dot);
    REQUIRE(tokens[10].getValue() == ".");

    REQUIRE(tokens[11].getType() == TokenType::AttrName);
    REQUIRE(tokens[11].getValue() == "stmt#");

    REQUIRE(tokens[12].getType() == TokenType::Equal);
    REQUIRE(tokens[12].getValue() == "=");

    REQUIRE(tokens[13].getType() == TokenType::IDENT);
    REQUIRE(tokens[13].getValue() == "a");

    REQUIRE(tokens[14].getType() == TokenType::Dot);
    REQUIRE(tokens[14].getValue() == ".");

    REQUIRE(tokens[15].getType() == TokenType::AttrName);
    REQUIRE(tokens[15].getValue() == "stmt#"); 
}


TEST_CASE("quoted constant with wildcards and not") {
    Tokenizer tokenizer("assign a; Select a pattern not a(_, _\"1\"_)");
    vector<Token> tokens = tokenizer.tokenize();

    REQUIRE(tokens.size() == 15);  // Expecting 14 tokens

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

    REQUIRE(tokens[6].getType() == TokenType::NotKeyword);
    REQUIRE(tokens[6].getValue() == "not");

    REQUIRE(tokens[7].getType() == TokenType::IDENT);
    REQUIRE(tokens[7].getValue() == "a");

    REQUIRE(tokens[8].getType() == TokenType::Lparenthesis);
    REQUIRE(tokens[8].getValue() == "(");

    REQUIRE(tokens[9].getType() == TokenType::Wildcard);
    REQUIRE(tokens[9].getValue() == "_");

    REQUIRE(tokens[10].getType() == TokenType::Comma);
    REQUIRE(tokens[10].getValue() == ",");

    REQUIRE(tokens[11].getType() == TokenType::Wildcard);
    REQUIRE(tokens[11].getValue() == "_");

    REQUIRE(tokens[12].getType() == TokenType::QuoutConst);
    REQUIRE(tokens[12].getValue() == "\"1\"");

    REQUIRE(tokens[13].getType() == TokenType::Wildcard);
    REQUIRE(tokens[13].getValue() == "_");

    REQUIRE(tokens[14].getType() == TokenType::Rparenthesis);
    REQUIRE(tokens[14].getValue() == ")");
}

TEST_CASE("stmt s; Select BOOLEAN such that not Follows(3, 4)") {
    // Initialize tokenizer with the input string
    Tokenizer tokenizer("stmt s; Select BOOLEAN such that not Follows(3, 4)");
    vector<Token> tokens = tokenizer.tokenize();

    // Check the total number of tokens
    REQUIRE(tokens.size() == 14);  // Expecting 12 tokens

    // Validate each token against the expected output
    REQUIRE(tokens[0].getType() == TokenType::DesignEntity);
    REQUIRE(tokens[0].getValue() == "stmt");
    REQUIRE(tokens[1].getType() == TokenType::IDENT);
    REQUIRE(tokens[1].getValue() == "s");
    REQUIRE(tokens[2].getType() == TokenType::Semicolon);
    REQUIRE(tokens[2].getValue() == ";");
    REQUIRE(tokens[3].getType() == TokenType::SelectKeyword);
    REQUIRE(tokens[3].getValue() == "Select");
    REQUIRE(tokens[4].getType() == TokenType::BooleanKeyword);
    REQUIRE(tokens[4].getValue() == "BOOLEAN");
    REQUIRE(tokens[5].getType() == TokenType::SuchKeyword);
    REQUIRE(tokens[5].getValue() == "such");
    REQUIRE(tokens[6].getType() == TokenType::ThatKeyword);
    REQUIRE(tokens[6].getValue() == "that");
    REQUIRE(tokens[7].getType() == TokenType::NotKeyword);
    REQUIRE(tokens[7].getValue() == "not");
    REQUIRE(tokens[8].getType() == TokenType::Follows);
    REQUIRE(tokens[8].getValue() == "Follows");
    REQUIRE(tokens[9].getType() == TokenType::Lparenthesis);
    REQUIRE(tokens[9].getValue() == "(");
    REQUIRE(tokens[10].getType() == TokenType::INTEGER);
    REQUIRE(tokens[10].getValue() == "3");
    REQUIRE(tokens[11].getType() == TokenType::Comma);
    REQUIRE(tokens[11].getValue() == ",");
    REQUIRE(tokens[12].getType() == TokenType::INTEGER);
    REQUIRE(tokens[12].getValue() == "4");
    REQUIRE(tokens[13].getType() == TokenType::Rparenthesis);
    REQUIRE(tokens[13].getValue() == ")");
}

TEST_CASE("assign a; Select a such that Follows(3, a) not Parent(a, 5) pattern a(v, _\"2\"_) and not a(_, _)") {
    // Initialize tokenizer with the input string
    Tokenizer tokenizer("assign a; Select a such that Follows(3, a) and not Parent(a, 5) pattern a(v, _\"2\"_) and not a(_, _)");
    vector<Token> tokens = tokenizer.tokenize();

    // Check the total number of tokens
    REQUIRE(tokens.size() == 38);  // Expecting 30 tokens

    // Validate each token against the expected output
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
    REQUIRE(tokens[5].getType() == TokenType::SuchKeyword);
    REQUIRE(tokens[5].getValue() == "such");
    REQUIRE(tokens[6].getType() == TokenType::ThatKeyword);
    REQUIRE(tokens[6].getValue() == "that");
    REQUIRE(tokens[7].getType() == TokenType::Follows);
    REQUIRE(tokens[7].getValue() == "Follows");
    REQUIRE(tokens[8].getType() == TokenType::Lparenthesis);
    REQUIRE(tokens[8].getValue() == "(");
    REQUIRE(tokens[9].getType() == TokenType::INTEGER);
    REQUIRE(tokens[9].getValue() == "3");
    REQUIRE(tokens[10].getType() == TokenType::Comma);
    REQUIRE(tokens[10].getValue() == ",");
    REQUIRE(tokens[11].getType() == TokenType::IDENT);
    REQUIRE(tokens[11].getValue() == "a");
    REQUIRE(tokens[12].getType() == TokenType::Rparenthesis);
    REQUIRE(tokens[12].getValue() == ")");
    REQUIRE(tokens[13].getType() == TokenType::AndKeyword);
    // finish the all of the rest for me
    REQUIRE(tokens[14].getType() == TokenType::NotKeyword);
    REQUIRE(tokens[14].getValue() == "not");
    REQUIRE(tokens[15].getType() == TokenType::Parent);
    REQUIRE(tokens[15].getValue() == "Parent");
    REQUIRE(tokens[16].getType() == TokenType::Lparenthesis);
    REQUIRE(tokens[16].getValue() == "(");
    REQUIRE(tokens[17].getType() == TokenType::IDENT);
    REQUIRE(tokens[17].getValue() == "a");
    REQUIRE(tokens[18].getType() == TokenType::Comma);
    REQUIRE(tokens[18].getValue() == ",");
    REQUIRE(tokens[19].getType() == TokenType::INTEGER);
    REQUIRE(tokens[19].getValue() == "5");
    REQUIRE(tokens[20].getType() == TokenType::Rparenthesis);
    REQUIRE(tokens[20].getValue() == ")");
    REQUIRE(tokens[21].getType() == TokenType::PatternKeyword);
    REQUIRE(tokens[21].getValue() == "pattern");
    REQUIRE(tokens[22].getType() == TokenType::IDENT);
    REQUIRE(tokens[22].getValue() == "a");
    REQUIRE(tokens[23].getType() == TokenType::Lparenthesis);
    REQUIRE(tokens[23].getValue() == "(");
    REQUIRE(tokens[24].getType() == TokenType::IDENT);
    REQUIRE(tokens[24].getValue() == "v");
    REQUIRE(tokens[25].getType() == TokenType::Comma);
    REQUIRE(tokens[25].getValue() == ",");
    REQUIRE(tokens[26].getType() == TokenType::Wildcard);
    REQUIRE(tokens[26].getValue() == "_");
    REQUIRE(tokens[27].getType() == TokenType::QuoutConst);
    REQUIRE(tokens[27].getValue() == "\"2\"");
    REQUIRE(tokens[28].getType() == TokenType::Wildcard);
    REQUIRE(tokens[28].getValue() == "_");
    REQUIRE(tokens[29].getType() == TokenType::Rparenthesis);
    REQUIRE(tokens[29].getValue() == ")");
    REQUIRE(tokens[30].getType() == TokenType::AndKeyword);
    REQUIRE(tokens[30].getValue() == "pattern");
    REQUIRE(tokens[31].getType() == TokenType::NotKeyword);
    REQUIRE(tokens[31].getValue() == "not");
    REQUIRE(tokens[32].getType() == TokenType::IDENT);
    REQUIRE(tokens[32].getValue() == "a");
    REQUIRE(tokens[33].getType() == TokenType::Lparenthesis);
    REQUIRE(tokens[33].getValue() == "(");
    REQUIRE(tokens[34].getType() == TokenType::Wildcard);
    REQUIRE(tokens[34].getValue() == "_");
    REQUIRE(tokens[35].getType() == TokenType::Comma);
    REQUIRE(tokens[35].getValue() == ",");
    REQUIRE(tokens[36].getType() == TokenType::Wildcard);
    REQUIRE(tokens[36].getValue() == "_");
    REQUIRE(tokens[37].getType() == TokenType::Rparenthesis);
    REQUIRE(tokens[37].getValue() == ")");




}


TEST_CASE("stmt s; assign a; constant c; Select BOOLEAN such that Follows(3, 4) and Parent(5, 6) with a.stmt# = s.stmt# not c.value = \"abc\"") {
    // Initialize tokenizer with the input string
    Tokenizer tokenizer(
            "stmt s; assign a; constant c; Select BOOLEAN such that Follows(3, 4) and Parent(5, 6) with a.stmt# = s.stmt# and not c.value = \"abc\"");
    vector<Token> tokens = tokenizer.tokenize();

    // Check the total number of tokens
    REQUIRE(tokens.size() == 41);  // The exact token count should be determined based on parsing rules

    // Validate each token against the expected output
    REQUIRE(tokens[0].getType() == TokenType::DesignEntity);
    REQUIRE(tokens[0].getValue() == "stmt");

    REQUIRE(tokens[1].getType() == TokenType::IDENT);
    REQUIRE(tokens[1].getValue() == "s");

    REQUIRE(tokens[2].getType() == TokenType::Semicolon);

    REQUIRE(tokens[3].getType() == TokenType::DesignEntity);
    REQUIRE(tokens[3].getValue() == "assign");

    REQUIRE(tokens[4].getType() == TokenType::IDENT);
    REQUIRE(tokens[4].getValue() == "a");

    REQUIRE(tokens[5].getType() == TokenType::Semicolon);

    REQUIRE(tokens[6].getType() == TokenType::DesignEntity);
    REQUIRE(tokens[6].getValue() == "constant");

    REQUIRE(tokens[7].getType() == TokenType::IDENT);
    REQUIRE(tokens[7].getValue() == "c");

    REQUIRE(tokens[8].getType() == TokenType::Semicolon);

    REQUIRE(tokens[9].getType() == TokenType::SelectKeyword);
    REQUIRE(tokens[9].getValue() == "Select");

    REQUIRE(tokens[10].getType() == TokenType::BooleanKeyword);
    REQUIRE(tokens[10].getValue() == "BOOLEAN");

    REQUIRE(tokens[11].getType() == TokenType::SuchKeyword);

    REQUIRE(tokens[12].getType() == TokenType::ThatKeyword);

    REQUIRE(tokens[13].getType() == TokenType::Follows);
    REQUIRE(tokens[13].getValue() == "Follows");

    REQUIRE(tokens[14].getType() == TokenType::Lparenthesis);

    REQUIRE(tokens[15].getType() == TokenType::INTEGER);
    REQUIRE(tokens[15].getValue() == "3");

    REQUIRE(tokens[16].getType() == TokenType::Comma);

    REQUIRE(tokens[17].getType() == TokenType::INTEGER);
    REQUIRE(tokens[17].getValue() == "4");

    REQUIRE(tokens[18].getType() == TokenType::Rparenthesis);

    REQUIRE(tokens[19].getType() == TokenType::AndKeyword);

    REQUIRE(tokens[20].getType() == TokenType::Parent);
    REQUIRE(tokens[20].getValue() == "Parent");

    REQUIRE(tokens[21].getType() == TokenType::Lparenthesis);

    REQUIRE(tokens[22].getType() == TokenType::INTEGER);
    REQUIRE(tokens[22].getValue() == "5");

    REQUIRE(tokens[23].getType() == TokenType::Comma);

    REQUIRE(tokens[24].getType() == TokenType::INTEGER);
    REQUIRE(tokens[24].getValue() == "6");

    REQUIRE(tokens[25].getType() == TokenType::Rparenthesis);

    REQUIRE(tokens[26].getType() == TokenType::WithKeyword);

    REQUIRE(tokens[27].getType() == TokenType::IDENT);
    REQUIRE(tokens[27].getValue() == "a");
    REQUIRE(tokens[28].getType() == TokenType::Dot);
    REQUIRE(tokens[29].getType() == TokenType::AttrName);
    REQUIRE(tokens[29].getValue() == "stmt#");
    REQUIRE(tokens[30].getType() == TokenType::Equal);
    REQUIRE(tokens[31].getType() == TokenType::IDENT);
    REQUIRE(tokens[31].getValue() == "s");
    REQUIRE(tokens[32].getType() == TokenType::Dot);
    REQUIRE(tokens[33].getType() == TokenType::AttrName);
    REQUIRE(tokens[33].getValue() == "stmt#");
    REQUIRE(tokens[34].getType() == TokenType::AndKeyword);
    REQUIRE(tokens[35].getType() == TokenType::NotKeyword);
    REQUIRE(tokens[36].getType() == TokenType::IDENT);
    REQUIRE(tokens[36].getValue() == "c");
    REQUIRE(tokens[37].getType() == TokenType::Dot);
    REQUIRE(tokens[38].getType() == TokenType::AttrName);
    REQUIRE(tokens[38].getValue() == "value");
    REQUIRE(tokens[39].getType() == TokenType::Equal);
    REQUIRE(tokens[40].getType() == TokenType::QuoutIDENT);
    REQUIRE(tokens[40].getValue() == "\"abc\"");

}

TEST_CASE("Select stmts with adjusted conditions and additional clause") {
    Tokenizer tokenizer("stmt s; Select s such that not Follows(s, 4) and not Parent(s, 5) and Modifies(s, \"x\") and not Modifies(s, \"y\") Uses(s, \"z\")");
    vector<Token> tokens = tokenizer.tokenize();

    REQUIRE(tokens.size() == 43);  // Adjust the expected number based on how your tokenizer handles this query
    REQUIRE(tokens[0].getType() == TokenType::DesignEntity);
    REQUIRE(tokens[0].getValue() == "stmt");
    REQUIRE(tokens[1].getType() == TokenType::IDENT);
    REQUIRE(tokens[1].getValue() == "s");
    REQUIRE(tokens[2].getType() == TokenType::Semicolon);
    REQUIRE(tokens[3].getType() == TokenType::SelectKeyword);
    REQUIRE(tokens[3].getValue() == "Select");
    REQUIRE(tokens[4].getType() == TokenType::IDENT);
    REQUIRE(tokens[4].getValue() == "s");
    REQUIRE(tokens[5].getType() == TokenType::SuchKeyword);
    REQUIRE(tokens[6].getType() == TokenType::ThatKeyword);
    REQUIRE(tokens[7].getType() == TokenType::NotKeyword);
    REQUIRE(tokens[8].getType() == TokenType::Follows);
    REQUIRE(tokens[9].getType() == TokenType::Lparenthesis);
    REQUIRE(tokens[10].getType() == TokenType::IDENT);
    REQUIRE(tokens[10].getValue() == "s");
    REQUIRE(tokens[11].getType() == TokenType::Comma);
    REQUIRE(tokens[12].getType() == TokenType::INTEGER);
    REQUIRE(tokens[12].getValue() == "4");
    REQUIRE(tokens[13].getType() == TokenType::Rparenthesis);
    REQUIRE(tokens[14].getType() == TokenType::AndKeyword);
    REQUIRE(tokens[15].getType() == TokenType::NotKeyword);
    REQUIRE(tokens[16].getType() == TokenType::Parent);
    REQUIRE(tokens[17].getType() == TokenType::Lparenthesis);
    REQUIRE(tokens[18].getType() == TokenType::IDENT);
    REQUIRE(tokens[18].getValue() == "s");
    REQUIRE(tokens[19].getType() == TokenType::Comma);
    REQUIRE(tokens[20].getType() == TokenType::INTEGER);
    REQUIRE(tokens[20].getValue() == "5");
    REQUIRE(tokens[21].getType() == TokenType::Rparenthesis);
    REQUIRE(tokens[22].getType() == TokenType::AndKeyword);
    REQUIRE(tokens[23].getType() == TokenType::Modifies);
    REQUIRE(tokens[24].getType() == TokenType::Lparenthesis);
    REQUIRE(tokens[25].getType() == TokenType::IDENT);
    REQUIRE(tokens[25].getValue() == "s");
    REQUIRE(tokens[26].getType() == TokenType::Comma);
    REQUIRE(tokens[27].getType() == TokenType::QuoutIDENT);
    REQUIRE(tokens[27].getValue() == "\"x\"");
    REQUIRE(tokens[28].getType() == TokenType::Rparenthesis);
    REQUIRE(tokens[29].getType() == TokenType::AndKeyword);
    REQUIRE(tokens[30].getType() == TokenType::NotKeyword);
    REQUIRE(tokens[31].getType() == TokenType::Modifies);
    REQUIRE(tokens[32].getType() == TokenType::Lparenthesis);
    REQUIRE(tokens[33].getType() == TokenType::IDENT);
    REQUIRE(tokens[33].getValue() == "s");
    REQUIRE(tokens[34].getType() == TokenType::Comma);
    REQUIRE(tokens[35].getType() == TokenType::QuoutIDENT);
    REQUIRE(tokens[35].getValue() == "\"y\"");
    REQUIRE(tokens[36].getType() == TokenType::Rparenthesis);
    REQUIRE(tokens[37].getType() == TokenType::Uses);
    REQUIRE(tokens[38].getType() == TokenType::Lparenthesis);
    REQUIRE(tokens[39].getType() == TokenType::IDENT);
    REQUIRE(tokens[39].getValue() == "s");
    REQUIRE(tokens[40].getType() == TokenType::Comma);
    REQUIRE(tokens[41].getType() == TokenType::QuoutIDENT);
    REQUIRE(tokens[41].getValue() == "\"z\"");
    REQUIRE(tokens[42].getType() == TokenType::Rparenthesis);

}
