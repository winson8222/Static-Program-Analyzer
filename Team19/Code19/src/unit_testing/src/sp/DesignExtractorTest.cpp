#include "sp/DesignExtractor/DesignExtractor.h"
#include "pkb/PKBManager.h"
#include "pkb/PKBWriter.h"
#include "catch.hpp"
#include <fstream>
#include <iostream>
#include <filesystem>
#include <vector>

TEST_CASE("Basic system tests for DesignExtractor", "[DesignExtractor::extract]") {
    const std::string testFileName = "../../../../../tests/sp/TokenizerTest/sourcefile1.txt";
    REQUIRE(std::filesystem::exists(testFileName));

    PKBManager pkbManager;
    std::shared_ptr<PKBWriter> pkbWriter = pkbManager.getPKBWriter();
}
