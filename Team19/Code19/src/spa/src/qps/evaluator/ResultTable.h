#pragma
//
// Created by Winson Zheng on 19/2/24.
//

#ifndef SPA_RESULTABLE_H
#define SPA_RESULTABLE_H
#include <vector>
#include <string>
#include <memory>
#include <functional>
#include <unordered_set>
#include <unordered_map>


class ResultTable {
private:
    // this represents the column names
    std::vector<std::string> colSet;

    // this represents the rows
    std::vector<std::unordered_map<std::string, std::string>> rows;

    // this represents if there is an result or not, if not then the result is empty and no need to join
    bool noResults = false;

    //the unique values of each column
    std::vector<std::string> uniqueColumns;

    // this is the join function
public:

    static std::unordered_map<std::string, std::string> mergeRows(const std::unordered_map<std::string, std::string>& row1,
                                                    const std::unordered_map<std::string, std::string>& row2,
                                                    const std::vector<std::string>& commonColumns,
                                                    const std::vector<std::string>& uniqueToTable2);

    static bool commonColumnsMatch(const std::unordered_map<std::string, std::string>& row1,
                                   const std::unordered_map<std::string, std::string>& row2,
                                   const std::vector<std::string>& commonColumns);

    // this is the function to get all the table content
    std::vector<std::unordered_map<std::string, std::string>> getRows() const;

    // this is the function to get all the column names
    std::vector<std::string> getColSet() const;

    // this is the insert function to insert an existing row
    void insertRow(const std::unordered_map<std::string, std::string>& row);

    // this is the function to insert a column
    void insertColumn(const std::string& colName);

    void insertAllColumns(const std::vector<std::string>& colNames);

    // this function insert a column value to a specific row
    void insertValue(const std::string& colName, const std::string& value, const int rowNumber);

    // this function get the entire empty row at rowNumber
    void insertNewRow();

    // this function join the table on columns, combining the columns and merging the rows
    std::shared_ptr<ResultTable> joinOnColumns(const std::shared_ptr<ResultTable>& table2);

    // identify common and unique columns
    void identifyColumns(const std::shared_ptr<ResultTable>& table2,
                         std::vector<std::string>& commonColumns,
                         std::vector<std::string>& uniqueToTable1,
                         std::vector<std::string>& uniqueToTable2);

    bool isTableIdentical(const std::shared_ptr<ResultTable>& table2);
};


#endif //SPA_RESULTABLE_H
