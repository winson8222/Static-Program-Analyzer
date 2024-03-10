#include "catch.hpp"
#include "sp/Parser/SimpleLineManager.h"

TEST_CASE("Testing SimpleLineManager class", "[SimpleLineManager]") {
    SimpleLineManager lineManager;

    SECTION("InitialState") {
        REQUIRE(lineManager.getLine() == 0);
    }

    SECTION("Interweaving methods") {
        REQUIRE(lineManager.getLine() == 0);

        lineManager.nextLine();
        REQUIRE(lineManager.getLine() == 1);

        int programLineNumber = lineManager.getProgramLineNumber();
        REQUIRE(programLineNumber == -1);

        lineManager.nextLine();
        REQUIRE(lineManager.getLine() == 2);

        lineManager.nextLine();
        lineManager.nextLine();
        lineManager.nextLine();
        lineManager.nextLine();
        lineManager.nextLine();

        REQUIRE(lineManager.getLine() == 7);
    }
}
