#include "catch.hpp"
#include "pkb/templates/TemplateMapSet.h"

TEST_CASE("pkb/templates/TemplateMapSet") {
    SECTION("addKeyValue") {
        TemplateMapSet<int, int> templateMapSet;
        templateMapSet.addKeyValue(1, 2);
        templateMapSet.addKeyValue(1, 3);
        templateMapSet.addKeyValue(2, 3);
        auto expected = std::unordered_map<int, std::unordered_set<int>>{
                {1, {2, 3}},
                {2, {3}}
        };
        REQUIRE(templateMapSet.getMapSet() == expected);
    }
    SECTION("getMapSet") {
        TemplateMapSet<int, int> templateMapSet;
        auto expected = std::unordered_map<int, std::unordered_set<int>>{};
        REQUIRE(templateMapSet.getMapSet() == expected);
        templateMapSet.addKeyValue(1, 2);
        templateMapSet.addKeyValue(1, 3);
        templateMapSet.addKeyValue(2, 3);
        expected = std::unordered_map<int, std::unordered_set<int>>{
                {1, {2, 3}},
                {2, {3}}
        };
        REQUIRE(templateMapSet.getMapSet() == expected);
    }

    SECTION("hasKeyValue") {
        TemplateMapSet<int, int> templateMapSet;
        templateMapSet.addKeyValue(1, 2);
        templateMapSet.addKeyValue(1, 3);
        templateMapSet.addKeyValue(2, 3);
        REQUIRE(templateMapSet.hasKeyValue(1, 2));
        REQUIRE(templateMapSet.hasKeyValue(1, 3));
        REQUIRE(templateMapSet.hasKeyValue(2, 3));
        REQUIRE_FALSE(templateMapSet.hasKeyValue(1, 4));
        REQUIRE_FALSE(templateMapSet.hasKeyValue(2, 1));
    }

    SECTION("getKeys") {
        TemplateMapSet<int, int> templateMapSet;
        templateMapSet.addKeyValue(1, 2);
        templateMapSet.addKeyValue(1, 3);
        templateMapSet.addKeyValue(2, 3);
        auto expected = std::unordered_set<int>{1, 2};
        REQUIRE(templateMapSet.getKeys() == expected);
    }

    SECTION("getValues") {
        TemplateMapSet<int, int> templateMapSet;
        templateMapSet.addKeyValue(1, 2);
        templateMapSet.addKeyValue(1, 3);
        templateMapSet.addKeyValue(2, 3);
        auto expected = std::unordered_set<int>{2, 3};
        REQUIRE(templateMapSet.getValues() == expected);
    }

    SECTION("getValuesByKey") {
        TemplateMapSet<int, int> templateMapSet;
        templateMapSet.addKeyValue(1, 2);
        templateMapSet.addKeyValue(1, 3);
        templateMapSet.addKeyValue(2, 3);
        auto expected = std::unordered_set<int>{2, 3};
        REQUIRE(templateMapSet.getValuesByKey(1) == expected);
        expected = std::unordered_set<int>{3};
        REQUIRE(templateMapSet.getValuesByKey(2) == expected);
    }

    SECTION("hasKey") {
        TemplateMapSet<int, int> templateMapSet;
        templateMapSet.addKeyValue(1, 2);
        templateMapSet.addKeyValue(1, 3);
        templateMapSet.addKeyValue(2, 3);
        REQUIRE(templateMapSet.hasKey(1));
        REQUIRE(templateMapSet.hasKey(2));
        REQUIRE_FALSE(templateMapSet.hasKey(3));
    }

    SECTION("remove") {
        TemplateMapSet<int, int> templateMapSet;
        templateMapSet.addKeyValue(1, 2);
        templateMapSet.addKeyValue(1, 3);
        templateMapSet.addKeyValue(2, 3);
        templateMapSet.remove(1);
        auto expected = std::unordered_map<int, std::unordered_set<int>>{
                {2, {3}}
        };
        REQUIRE(templateMapSet.getMapSet() == expected);
    }

    SECTION("clear") {
        TemplateMapSet<int, int> templateMapSet;
        templateMapSet.addKeyValue(1, 2);
        templateMapSet.addKeyValue(1, 3);
        templateMapSet.addKeyValue(2, 3);
        templateMapSet.clear();
        auto expected = std::unordered_map<int, std::unordered_set<int>>{};
        REQUIRE(templateMapSet.getMapSet() == expected);
    }
}