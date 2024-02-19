//
// Created by Winson Zheng on 19/2/24.
//

#include "ResultTable.h"
#include <initializer_list>

std::shared_ptr<ResultTable> ResultTable::joinOnColumns(const std::shared_ptr<ResultTable>& table2) {
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

void ResultTable::identifyColumns(const std::shared_ptr<ResultTable> &table2, std::vector<std::string> &commonColumns,
                                  std::vector<std::string> &uniqueToTable1, std::vector<std::string> &uniqueToTable2) {
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
    for (const auto &colName: commonColumns) {
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
bool ResultTable::isTableIdentical(const std::shared_ptr<ResultTable> &table2) {
    if (colSet.size() != table2->colSet.size()) {
        return false;
    }
    for (const auto & i : colSet) {
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


void ResultTable::addColumnsSet(const std::vector<std::string> &colNames) {
    for (const auto &colName : colNames) {
        insertColumn(colName);
    }
}

void ResultTable::insertAllColumns(const std::vector<std::string> &colNames) {
    colSet = colNames;
}





