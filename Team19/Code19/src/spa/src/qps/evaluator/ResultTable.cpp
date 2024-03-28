//
// Created by Winson Zheng on 19/2/24.
//

#include "ResultTable.h"
#include <initializer_list>
#include <algorithm>   // For std::sort, std::set_intersection, std::set_difference
#include <iterator>    // For std::back_inserter
#include <stdexcept>   // For std::exception or specific exception types

std::shared_ptr<ResultTable> ResultTable::joinOnColumns(const std::shared_ptr<ResultTable>& table2) {
    // if table 2 is empty and is a truth table, return a copy of table1
    // this is used for cases when joining a table with a true clause like Follows(1,2)
    if (table2->isTruthTable && table2->rows.empty()) {
        auto result = std::make_shared<ResultTable>(*this);
        return result;
    }
    // Opposite case where table 1 is empty and is a truth table, return a copy of table2
    if (this->isTruthTable && this->rows.empty()) {
        // Return a copy of table2
        auto result = std::make_shared<ResultTable>(*table2);
        return result;
    }
    
    //build a new empty table
    auto result = std::make_shared<ResultTable>();
    std::vector<std::string> commonColumns, uniqueToTable1, uniqueToTable2;


    // find common columns and unique columns
    identifyColumns(table2, commonColumns, uniqueToTable1, uniqueToTable2);
    // set the columns of the new table
    result->addColumnsSet(commonColumns);
    result->addColumnsSet(uniqueToTable2);
    result->addColumnsSet(uniqueToTable1);


    // Iterate through rows of table1
    for (auto& row1 : rows) {
        // Iterate through rows of table2
        for (auto& row2 : table2->rows) {
            // Check if common columns match (Implementation of `commonColumnsMatch` not shown)
            if (commonColumnsMatch(row1, row2, commonColumns)) {
                // Merge rows (Implementation of `mergeRows` not shown)
                std::unordered_map<std::string, std::string> mergedRow = mergeRows(row1, row2, commonColumns, uniqueToTable2);
                result->insertNewRow(mergedRow);
            }
        }
    }

    return result;


}

std::shared_ptr<ResultTable> ResultTable::excludeOnColumns(const std::shared_ptr<ResultTable>& table2) {
    // Create a new result table
    auto result = std::make_shared<ResultTable>();

    // Identify common columns between the two tables and columns unique to each table
    std::vector<std::string> commonColumns;
    std::vector<std::string> uniqueToTable1;
    std::vector<std::string> uniqueToTable2;
    identifyColumns(table2, commonColumns, uniqueToTable1, uniqueToTable2);

    // Set up the columns of the result table
    result->addColumnsSet(this->colSet);

    // Iterate through rows of this table to check against all rows in table2
    for (auto& row1 : this->rows) {
        bool excludeRow = false;
        for (auto& row2 : table2->rows) {
            // If the common columns match between a row in this table and a row in table2, exclude the row
            if (commonColumnsMatch(row1, row2, commonColumns)) {
                excludeRow = true;
                break; // A matching row was found, so this row is excluded
            }
        }
        // If the row from this table has no matches in table2, include it in the result
        if (!excludeRow) {
            result->insertNewRow(row1);
        }
    }

    return result;

}



// this function merge the rows of two tables where the common columns match
std::unordered_map<std::string, std::string> ResultTable::mergeRows(const std::unordered_map<std::string, std::string>& row1,
    const std::unordered_map<std::string, std::string>& row2,
    const std::vector<std::string>& commonColumns,
    const std::vector<std::string>& uniqueToTable2) {
    std::unordered_map<std::string, std::string> mergedRowMap;

    // Add all values from row1
    for (const auto& [key, value] : row1) {
        mergedRowMap[key] = value;
    }


    // Add unique column values from row2 that was not in table1
    for (const auto& colName : uniqueToTable2) {
        if (row2.find(colName) != row2.end()) {
            mergedRowMap[colName] = row2.at(colName);
        }
    }

    return mergedRowMap;
}


// this function identify common and unique columns

void ResultTable::identifyColumns(const std::shared_ptr<ResultTable>& table2, std::vector<std::string>& commonColumns,
    std::vector<std::string>& uniqueToTable1, std::vector<std::string>& uniqueToTable2) {
    // Step 1: Convert unordered_sets to vectors
    std::vector<std::string> cols1(this->colSet.begin(), this->colSet.end());
    std::vector<std::string> cols2(table2->colSet.begin(), table2->colSet.end());

    // Step 2: Sort the vectors to prepare for set operations
    std::sort(cols1.begin(), cols1.end());
    std::sort(cols2.begin(), cols2.end());

    // Temporary containers for set operations
    std::vector<std::string> tempCommonColumns;
    std::vector<std::string> tempUniqueToTable1;
    std::vector<std::string> tempUniqueToTable2;

    // Step 3: Perform set operations
    std::set_intersection(cols1.begin(), cols1.end(),
        cols2.begin(), cols2.end(),
        std::back_inserter(tempCommonColumns));

    std::set_difference(cols1.begin(), cols1.end(),
        cols2.begin(), cols2.end(),
        std::back_inserter(tempUniqueToTable1));

    std::set_difference(cols2.begin(), cols2.end(),
        cols1.begin(), cols1.end(),
        std::back_inserter(tempUniqueToTable2));

    // Update references
    commonColumns = std::move(tempCommonColumns);
    uniqueToTable1 = std::move(tempUniqueToTable1);
    uniqueToTable2 = std::move(tempUniqueToTable2);
}

bool ResultTable::commonColumnsMatch(const std::unordered_map<std::string, std::string>& row1,
    const std::unordered_map<std::string, std::string>& row2,
    const std::vector<std::string>& commonColumns) {
    for (const auto& colName : commonColumns) {
        // Find the column in both rows. If the column doesn't exist in either row, consider it a mismatch.
        auto it1 = row1.find(colName);
        auto it2 = row2.find(colName);

        // If the column is not found in either row or the values don't match, return false
        if (it1 == row1.end() || it2 == row2.end() || it1->second != it2->second) {
            return false;
        }
    }
    // All common columns matched
    return true;
}

// insert a whole exisitng row into the table
void ResultTable::insertNewRow(const std::unordered_map<std::string, std::string>& row) {
    // check if the row has the same size as the number of col
    if (row.size() != colSet.size()) {
        throw std::exception();
    }
    rows.push_back(row);
}

void ResultTable::insertColumn(const std::string& colName) {
    colSet.push_back(colName);
}

void ResultTable::insertEmptyRow() {
    rows.push_back(std::unordered_map<std::string, std::string>());
}

void ResultTable::insertValue(const std::string& colName, const std::string& value, const int rowNumber) {
    // check if the column exists
    if (std::find(colSet.begin(), colSet.end(), colName) == colSet.end()) {
        throw std::exception();
    }
    rows[rowNumber][colName] = value;
}

std::vector<std::string> ResultTable::getColSet() const {
    return colSet;
}

std::vector<std::unordered_map<std::string, std::string>> ResultTable::getRows() const {
    return rows;
}


// function for testing purpose
bool ResultTable::isTableIdentical(const std::shared_ptr<ResultTable>& table2) {
    if (colSet.size() != table2->colSet.size()) {
        return false;
    }
    for (const auto& i : colSet) {
        // the order of the columns does not matters
        if (std::find(table2->colSet.begin(), table2->colSet.end(), i) == table2->colSet.end()) {
            return false;
        }
    }

    if (rows.size() != table2->rows.size()) {
        return false;
    }
    for (int i = 0; i < rows.size(); i++) {
        // the order of the rows matters
        if (rows[i] != table2->rows[i]) {
            return false;
        }
    }
    return true;
}


void ResultTable::addColumnsSet(const std::vector<std::string>& colNames) {
    for (const auto& colName : colNames) {
        insertColumn(colName);
    }
}

void ResultTable::insertNewColumn(const std::string &colName, const std::vector<std::string> &values) {
    if (values.size() != rows.size()) {
        throw std::exception();
    }
    insertColumn(colName);

    for (int i = 0; i < values.size(); i++) {
        insertValue(colName, values[i], i);
    }
}

void ResultTable::insertAllColumns(const std::vector<std::string>& colNames) {
    colSet = colNames;
}

std::unordered_set<std::string> ResultTable::getColumnValues(const std::string& columnName) {
    std::unordered_set<std::string> uniqueColumnValues;

    // Check if the column name exists in the column set
    if (std::find(colSet.begin(), colSet.end(), columnName) == colSet.end()) {
        return {}; // Return an empty vector directly
    }

    // Iterate through each row and extract the value for the given column
    for (const auto& row : rows) {
        auto it = row.find(columnName);
        if (it != row.end()) {
            uniqueColumnValues.insert(it->second);
        }
        // If you still want to consider rows where the column name is not found,
        // you can insert an empty string into uniqueColumnValues here, but typically,
        // you might just skip it.
    }

    // Convert the unordered_set back to a vector to return
    //std::vector<std::string> columnValues(uniqueColumnValues.begin(), uniqueColumnValues.end());

    return uniqueColumnValues;
}

void ResultTable::setAsTruthTable()
{
    isTruthTable = true;
}

bool ResultTable::isTableTrue()
{
    return isTruthTable;
}



bool ResultTable::hasColumn(const std::string& columnName) const {
    // Search for the column name in colSet
    auto it = std::find(colSet.begin(), colSet.end(), columnName);
    // Return true if the column is found, false otherwise
    return it != colSet.end();
}

bool ResultTable::isEmpty() {
    return rows.empty();
}

bool ResultTable::isTableFalse() {
    return !isTruthTable && isEmpty();
}

void ResultTable::setTableFalse() {
    isTruthTable = false;
}

void ResultTable::populateWithTwoColumns(std::string col1, std::string col2, std::unordered_set <std::string> values,
                                         std::unordered_set <std::string> values2) {
    for (const auto& entityA : values) {
        for (const auto& entityB : values2) {
            std::unordered_map<std::string, std::string> newRow;
            newRow[col1] = entityA;
            newRow[col2] = entityB;
            this->insertNewRow(newRow);
        }
    }
}


void ResultTable::populateWithOneColumn(std::string col1, std::unordered_set<std::string> values) {
    for (const auto& entity : values) {
        std::unordered_map<std::string, std::string> newRow;
        newRow[col1] = entity;
        this->insertNewRow(newRow);
    }
}
