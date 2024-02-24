#include "catch.hpp"
#include "qps/evaluator/ResultTable.h"


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
    table1.insertAllColumns({ "a", "b" });
    table1.insertEmptyRow();
    table1.insertValue("a", "1", 0);
    table1.insertValue("b", "2", 0);
    table2->insertAllColumns({ "c", "d" });
    table2->insertEmptyRow();
    table2->insertValue("c", "5", 0);
    table2->insertValue("d", "6", 0);

    shared_ptr<ResultTable> expectedTable = make_shared<ResultTable>();
    expectedTable->insertAllColumns({ "a", "b", "c", "d" });
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
    REQUIRE(result->getColumnValues("a") == std::unordered_set<std::string>({"1"}));

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
    table1.insertAllColumns({ "a", "b" });
    table1.insertEmptyRow();
    table1.insertValue("a", "1", 0);
    table1.insertValue("b", "2", 0);
    table2->insertAllColumns({ "a", "c" });
    table2->insertEmptyRow();
    table2->insertValue("c", "5", 0);
    table2->insertValue("a", "1", 0);
    shared_ptr<ResultTable> expectedTable = make_shared<ResultTable>();
    expectedTable->insertAllColumns({ "a", "b", "c" });
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
    table1.insertAllColumns({ "a", "b" });
    table1.insertEmptyRow();
    table1.insertValue("a", "1", 0);
    table1.insertValue("b", "2", 0);
    table1.insertEmptyRow();
    table1.insertValue("a", "1", 1);
    table1.insertValue("b", "3", 1);
    table1.insertEmptyRow();
    table1.insertValue("a", "2", 2);
    table1.insertValue("b", "4", 2);


    table2->insertAllColumns({ "a", "c" });
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
    expectedTable->insertAllColumns({ "a", "b", "c" });
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


// s3 , v1
// 5 , y
// 5 , z
// 7 , x
// 8 , y
// 2 , y
// join with
// s3 
// 6 
// 5 
// 7 
// result
// s3 , v1
// 5 , y 
// 5 , z 
// 7 , x 
TEST_CASE("Result of two tables with common column and mutliple rows (lecture example)") {
    ResultTable table1;
    shared_ptr<ResultTable> table2 = make_shared<ResultTable>();
    table1.insertAllColumns({ "s3", "v1" });
    table1.insertEmptyRow();
    table1.insertValue("s3", "5", 0);
    table1.insertValue("v1", "y", 0);
    table1.insertEmptyRow();
    table1.insertValue("s3", "5", 1);
    table1.insertValue("v1", "z", 1);
    table1.insertEmptyRow();
    table1.insertValue("s3", "7", 2);
    table1.insertValue("v1", "x", 2);
    table1.insertEmptyRow();
    table1.insertValue("s3", "8", 3);
    table1.insertValue("v1", "y", 3);
    table1.insertEmptyRow();
    table1.insertValue("s3", "2", 4);
    table1.insertValue("v1", "y", 4);


    table2->insertAllColumns({ "s3" });
    table2->insertEmptyRow();
    table2->insertValue("s3", "6", 0);
    table2->insertEmptyRow();
    table2->insertValue("s3", "5", 1);
    table2->insertEmptyRow();
    table2->insertValue("s3", "7", 2);

    shared_ptr<ResultTable> expectedTable = make_shared<ResultTable>();
    expectedTable->insertAllColumns({ "s3", "v1" });
    expectedTable->insertEmptyRow();
    expectedTable->insertValue("s3", "5", 0);
    expectedTable->insertValue("v1", "y", 0);
    expectedTable->insertEmptyRow();
    expectedTable->insertValue("s3", "5", 1);
    expectedTable->insertValue("v1", "z", 1);
    expectedTable->insertEmptyRow();
    expectedTable->insertValue("s3", "7", 2);
    expectedTable->insertValue("v1", "x", 2);

    shared_ptr<ResultTable> result = table1.joinOnColumns(table2);
    REQUIRE(result->getRows().size() == 3);
    REQUIRE(result->getRows()[0].at("s3") == "5");
    REQUIRE(result->getRows()[0].at("v1") == "y");
    REQUIRE(result->getRows()[1].at("s3") == "5");
    REQUIRE(result->getRows()[1].at("v1") == "z");
    REQUIRE(result->getRows()[2].at("s3") == "7");
    REQUIRE(result->getRows()[2].at("v1") == "x");

}

// s3 , v1
// 5 , y 
// 5 , z 
// 7 , x 
// join with
// s1 , s2 
// 6 , 20
// 3 , 4
// 10 , 15
// 8 , 11 
// result
// s3 , v1 , s1 , s2
// 5 , y , 6 , 20
// 5 , z , 6, 20
// 7 , x , 6, 20
// 5 , y , 3 , 4
// 5 , z , 3 , 4
// 7 , x , 3 , 4
// 5 , y , 10 , 15
// 5 , z , 10 , 15
// 7 , x , 10 , 15
// 5 , y , 8 , 11
// 5 , z , 8 , 11
// 7 , x , 8 , 11
TEST_CASE("Result of joining two tables without a common column (Cartesian Product)") {
    ResultTable table1;
    shared_ptr<ResultTable> table2 = make_shared<ResultTable>();

    // Setup table1 with columns s3 and v1
    table1.insertAllColumns({ "s3", "v1" });
    table1.insertEmptyRow();
    table1.insertValue("s3", "5", 0);
    table1.insertValue("v1", "y", 0);
    table1.insertEmptyRow();
    table1.insertValue("s3", "5", 1);
    table1.insertValue("v1", "z", 1);
    table1.insertEmptyRow();
    table1.insertValue("s3", "7", 2);
    table1.insertValue("v1", "x", 2);

    // Setup table2 with columns s1 and s2
    table2->insertAllColumns({ "s1", "s2" });
    table2->insertEmptyRow();
    table2->insertValue("s1", "6", 0);
    table2->insertValue("s2", "20", 0);
    table2->insertEmptyRow();
    table2->insertValue("s1", "3", 1);
    table2->insertValue("s2", "4", 1);
    table2->insertEmptyRow();
    table2->insertValue("s1", "10", 2);
    table2->insertValue("s2", "15", 2);
    table2->insertEmptyRow();
    table2->insertValue("s1", "8", 3);
    table2->insertValue("s2", "11", 3);

    // Expected result after join
    shared_ptr<ResultTable> expectedTable = make_shared<ResultTable>();
    expectedTable->insertAllColumns({ "s3", "v1", "s1", "s2" });
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            expectedTable->insertEmptyRow();
            expectedTable->insertValue("s3", table1.getRows()[i].at("s3"), i * 4 + j);
            expectedTable->insertValue("v1", table1.getRows()[i].at("v1"), i * 4 + j);
            expectedTable->insertValue("s1", table2->getRows()[j].at("s1"), i * 4 + j);
            expectedTable->insertValue("s2", table2->getRows()[j].at("s2"), i * 4 + j);
        }
    }

    // Perform the join operation
    shared_ptr<ResultTable> result = table1.joinOnColumns(table2);

    // Assertions to verify the join result
    REQUIRE(result->getRows().size() == 12);
    for (int i = 0; i < 12; i++) {
        REQUIRE(result->getRows()[i].at("s3") == expectedTable->getRows()[i].at("s3"));
        REQUIRE(result->getRows()[i].at("v1") == expectedTable->getRows()[i].at("v1"));
        REQUIRE(result->getRows()[i].at("s1") == expectedTable->getRows()[i].at("s1"));
        REQUIRE(result->getRows()[i].at("s2") == expectedTable->getRows()[i].at("s2"));
    }
}
