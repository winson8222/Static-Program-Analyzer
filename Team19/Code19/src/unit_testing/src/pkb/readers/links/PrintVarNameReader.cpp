#include "catch.hpp"

#include "pkb/stores/links/types/PrintVarNameStore.h"
#include "pkb/readers/links/PrintVarNameReader.h"

TEST_CASE("pkb/readers/links/PrintVarNameReader") {
    SECTION("PrintVarNameReader can be created") {
        std::shared_ptr<PrintVarNameStore> printVarNameStore = std::make_shared<PrintVarNameStore>();
        PrintVarNameReader printVarNameReader(printVarNameStore);
    }

    SECTION("PrintVarNameReader can get printers") {
        std::shared_ptr<PrintVarNameStore> printVarNameStore = std::make_shared<PrintVarNameStore>();
        PrintVarNameReader printVarNameReader(printVarNameStore);
        printVarNameStore->addLink(1, "foo");
        printVarNameStore->addLink(2, "foo");
        printVarNameStore->addLink(3, "foo");
        REQUIRE(printVarNameReader.getPrints("foo") == std::unordered_set<int>({1, 2, 3}));
    }

    SECTION("PrintVarNameReader can get printed procedure name") {
        std::shared_ptr<PrintVarNameStore> printVarNameStore = std::make_shared<PrintVarNameStore>();
        PrintVarNameReader printVarNameReader(printVarNameStore);
        printVarNameStore->addLink(1, "foo");
        REQUIRE(printVarNameReader.getPrintVariableName(1) == "foo");
    }

    SECTION("PrintVarNameReader can check if a statement prints a procedure") {
        std::shared_ptr<PrintVarNameStore> printVarNameStore = std::make_shared<PrintVarNameStore>();
        PrintVarNameReader printVarNameReader(printVarNameStore);
        printVarNameStore->addLink(1, "foo");
        REQUIRE(printVarNameReader.isPrinted(1, "foo"));
    }

    SECTION("PrintVarNameReader can check if it is empty") {
        std::shared_ptr<PrintVarNameStore> printVarNameStore = std::make_shared<PrintVarNameStore>();
        PrintVarNameReader printVarNameReader(printVarNameStore);
        REQUIRE(printVarNameReader.isEmpty());
    }

    SECTION("PrintVarNameReader can check if doesn't exist") {
        std::shared_ptr<PrintVarNameStore> printVarNameStore = std::make_shared<PrintVarNameStore>();
        PrintVarNameReader printVarNameReader(printVarNameStore);
        REQUIRE_FALSE(printVarNameReader.isPrinted(1, "foo"));
    }

    SECTION("getPrintedProcedureName returns empty set if statement does not print any procedure") {
        std::shared_ptr<PrintVarNameStore> printVarNameStore = std::make_shared<PrintVarNameStore>();
        PrintVarNameReader printVarNameReader(printVarNameStore);
        REQUIRE_THROWS(printVarNameReader.getPrintVariableName(1));
    }
}
