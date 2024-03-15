#include "catch.hpp"

#include "pkb/stores/links/types/ReadVarNameStore.h"
#include "pkb/readers/links/ReadVarNameReader.h"

TEST_CASE("pkb/readers/links/ReadVarNameReader") {
    SECTION("ReadVarNameReader can be created") {
        std::shared_ptr<ReadVarNameStore> readVarNameStore = std::make_shared<ReadVarNameStore>();
        ReadVarNameReader readVarNameReader(readVarNameStore);
    }

    SECTION("ReadVarNameReader can get readers") {
        std::shared_ptr<ReadVarNameStore> readVarNameStore = std::make_shared<ReadVarNameStore>();
        ReadVarNameReader readVarNameReader(readVarNameStore);
        readVarNameStore->addLink(1, "foo");
        readVarNameStore->addLink(2, "foo");
        readVarNameStore->addLink(3, "foo");
        REQUIRE(readVarNameReader.getReaders("foo") == std::unordered_set<int>({1, 2, 3}));
    }

    SECTION("ReadVarNameReader can get read procedure name") {
        std::shared_ptr<ReadVarNameStore> readVarNameStore = std::make_shared<ReadVarNameStore>();
        ReadVarNameReader readVarNameReader(readVarNameStore);
        readVarNameStore->addLink(1, "foo");
        REQUIRE(readVarNameReader.getReadVariableName(1) == std::unordered_set<std::string>({"foo"}));
    }

    SECTION("ReadVarNameReader can check if a statement reads a procedure") {
        std::shared_ptr<ReadVarNameStore> readVarNameStore = std::make_shared<ReadVarNameStore>();
        ReadVarNameReader readVarNameReader(readVarNameStore);
        readVarNameStore->addLink(1, "foo");
        REQUIRE(readVarNameReader.isRead(1, "foo"));
    }

    SECTION("ReadVarNameReader can check if it is empty") {
        std::shared_ptr<ReadVarNameStore> readVarNameStore = std::make_shared<ReadVarNameStore>();
        ReadVarNameReader readVarNameReader(readVarNameStore);
        REQUIRE(readVarNameReader.isEmpty());
    }

    SECTION("ReadVarNameReader can check if doesn't exist") {
        std::shared_ptr<ReadVarNameStore> readVarNameStore = std::make_shared<ReadVarNameStore>();
        ReadVarNameReader readVarNameReader(readVarNameStore);
        REQUIRE_FALSE(readVarNameReader.isRead(1, "foo"));
    }

    SECTION("getReadedProcedureName returns empty set if statement does not read any procedure") {
        std::shared_ptr<ReadVarNameStore> readVarNameStore = std::make_shared<ReadVarNameStore>();
        ReadVarNameReader readVarNameReader(readVarNameStore);
        REQUIRE_THROWS(readVarNameReader.getReadVariableName(1));
    }
}
