#include "catch.hpp"
#include "../../spa/src/qps/evaluator/ResultTable.h"


using namespace std;

TEST_CASE("Check join result of two tables with no common columns") {
    ResultTable table1;
    shared_ptr<ResultTable> table2 = make_shared<ResultTable>();
    table1.insertValue("a", "1", 0);
    table1.insertValue("b", "2", 0);
    table2->insertValue("c", "5", 0);
    table2->insertValue("d", "6", 0);

    shared_ptr<ResultTable> expectedTable = make_shared<ResultTable>();
    expectedTable->insertValue("a", "1", 0);
    expectedTable->insertValue("b", "2", 0);
    expectedTable->insertValue("c", "5", 0);
    expectedTable->insertValue("d", "6", 0);
    expectedTable->insertAllColumns({"a", "b", "c", "d"});
    shared_ptr<ResultTable> result = table1.joinOnColumns(table2);
    REQUIRE(result->getRows().size() == 2);
    REQUIRE(result->getRows()[0].at("a") == "1");
    REQUIRE(result->getRows()[0].at("b") == "2");
    REQUIRE(result->getRows()[0].at("c") == "5");
    REQUIRE(result->getRows()[0].at("d") == "6");

}
