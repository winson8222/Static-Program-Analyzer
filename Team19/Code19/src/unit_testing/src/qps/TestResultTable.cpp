#include "catch.hpp"
#include "../../spa/src/qps/evaluator/ResultTable.h"


using namespace std;

// a, b
// 1, 2
// join with
// c, d
// 5, 6
// result
// a, b, c, d
// 1, 2, 5, 6
TEST_CASE("Check join result of two tables with no common column") {
    ResultTable table1;
    shared_ptr<ResultTable> table2 = make_shared<ResultTable>();
    table1.insertAllColumns({"a", "b"});
    table1.insertEmptyRow();
    table1.insertValue("a", "1", 0);
    table1.insertValue("b", "2", 0);
    table2->insertAllColumns({"c", "d"});
    table2->insertEmptyRow();
    table2->insertValue("c", "5", 0);
    table2->insertValue("d", "6", 0);

    shared_ptr<ResultTable> expectedTable = make_shared<ResultTable>();
    expectedTable->insertAllColumns({"a", "b", "c", "d"});
    expectedTable->insertEmptyRow();
    expectedTable->insertValue("a", "1", 0);
    expectedTable->insertValue("b", "2", 0);
    expectedTable->insertValue("c", "5", 0);
    expectedTable->insertValue("d", "6", 0);

    shared_ptr<ResultTable> result = table1.joinOnColumns(table2);
    REQUIRE(result->getRows().size() == 1);
    REQUIRE(result->getRows()[0].at("a") == "1");
    REQUIRE(result->getRows()[0].at("b") == "2");
    REQUIRE(result->getRows()[0].at("c") == "5");
    REQUIRE(result->getRows()[0].at("d") == "6");

}

// a , b
// 1 , 2
// join with
// a , c
// 1 , 5
// result
// a , b , c
// 1 , 2 , 5
TEST_CASE("Check join result of two tables with 1 common column") {
    ResultTable table1;
    shared_ptr<ResultTable> table2 = make_shared<ResultTable>();
    table1.insertAllColumns({"a", "b"});
    table1.insertEmptyRow();
    table1.insertValue("a", "1", 0);
    table1.insertValue("b", "2", 0);
    table2->insertAllColumns({"a", "c"});
    table2->insertEmptyRow();
    table2->insertValue("c", "5", 0);
    table2->insertValue("a", "1", 0);
    shared_ptr<ResultTable> expectedTable = make_shared<ResultTable>();
    expectedTable->insertAllColumns({"a", "b", "c"});
    expectedTable->insertEmptyRow();
    expectedTable->insertEmptyRow();
    expectedTable->insertValue("a", "1", 0);
    expectedTable->insertValue("b", "2", 0);
    expectedTable->insertValue("c", "5", 0);

    shared_ptr<ResultTable> result = table1.joinOnColumns(table2);
    REQUIRE(result->getRows().size() == 1);
    REQUIRE(result->getRows()[0].at("a") == "1");
    REQUIRE(result->getRows()[0].at("b") == "2");
    REQUIRE(result->getRows()[0].at("c") == "5");

}

// a , b
// 1 , 2
// 1 , 3
// 2 , 4
// join with
// a , c
// 1 , x
// 2 , y
// 3 , z
// result
// a , b , c
// 1 , 2 , x
// 1 , 3 , x
// 2 , 4 , y
TEST_CASE("Check join result of two tables with 1 common column and mutliple rows") {
    ResultTable table1;
    shared_ptr<ResultTable> table2 = make_shared<ResultTable>();
    table1.insertAllColumns({"a", "b"});
    table1.insertEmptyRow();
    table1.insertValue("a", "1", 0);
    table1.insertValue("b", "2", 0);
    table1.insertEmptyRow();
    table1.insertValue("a", "1", 1);
    table1.insertValue("b", "3", 1);
    table1.insertEmptyRow();
    table1.insertValue("a", "2", 2);
    table1.insertValue("b", "4", 2);


    table2->insertAllColumns({"a", "c"});
    table2->insertEmptyRow();
    table2->insertValue("c", "x", 0);
    table2->insertValue("a", "1", 0);
    table2->insertEmptyRow();
    table2->insertValue("c", "y", 1);
    table2->insertValue("a", "2", 1);
    table2->insertEmptyRow();
    table2->insertValue("c", "z", 2);
    table2->insertValue("a", "3", 2);
    shared_ptr<ResultTable> expectedTable = make_shared<ResultTable>();
    expectedTable->insertAllColumns({"a", "b", "c"});
    expectedTable->insertEmptyRow();
    expectedTable->insertValue("a", "1", 0);
    expectedTable->insertValue("b", "2", 0);
    expectedTable->insertValue("c", "x", 0);
    expectedTable->insertEmptyRow();
    expectedTable->insertValue("a", "1", 1);
    expectedTable->insertValue("b", "3", 1);
    expectedTable->insertValue("c", "x", 1);
    expectedTable->insertEmptyRow();
    expectedTable->insertValue("a", "2", 2);
    expectedTable->insertValue("b", "4", 2);
    expectedTable->insertValue("c", "y", 2);

    shared_ptr<ResultTable> result = table1.joinOnColumns(table2);
    REQUIRE(result->getRows().size() == 3);
    REQUIRE(result->getRows()[0].at("a") == "1");
    REQUIRE(result->getRows()[0].at("b") == "2");
    REQUIRE(result->getRows()[0].at("c") == "x");
    REQUIRE(result->getRows()[1].at("a") == "1");
    REQUIRE(result->getRows()[1].at("b") == "3");
    REQUIRE(result->getRows()[1].at("c") == "x");
    REQUIRE(result->getRows()[2].at("a") == "2");
    REQUIRE(result->getRows()[2].at("b") == "4");
    REQUIRE(result->getRows()[2].at("c") == "y");

}


