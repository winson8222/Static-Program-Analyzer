#include "WithStrategy.h"

#include "qps/parser/Token.h" // Include for Token definition

// Standard library dependencies
#include <string>
#include <unordered_set>
#include <iostream>
#include "WithStrategy.h"

/**
 * Evaluates equality between 2 parameters.
 * Determines the relationship based on the parsing result and updates the result table accordingly.
 *
 * @param pkbReaderManager Provides access to the program knowledge base.
 * @param parsingResult Contains the parsed query details.
 * @return A shared pointer to the populated result table.
 */
std::shared_ptr<ResultTable> WithStrategy::evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult, const Clause& clause, std::shared_ptr<ResultTable>& originalResultTable) {
    auto resultTable = std::make_shared<ResultTable>();
    // Initializing PKB readers for With clause
    const WithClause* withClause = dynamic_cast<const WithClause*>(&clause);
    this->firstParam = withClause->getFirstParam();
    this->secondParam = withClause->getSecondParam();
    if (isInteger(firstParam.getValue()) && isInteger(secondParam.getValue())) {
        if (firstParam.getValue() == secondParam.getValue()) {
			resultTable->setAsTruthTable();
		}
	}
    else if (isQuotedString(firstParam.getValue()) && isQuotedString(secondParam.getValue())) {
        if (firstParam.getValue() == secondParam.getValue()) {
			resultTable->setAsTruthTable();
		}
	}
    else {

        std::unordered_set<std::string> lhsValue = processParam(firstParam, parsingResult, pkbReaderManager, originalResultTable);
        std::unordered_set<std::string> rhsValue = processParam(secondParam, parsingResult, pkbReaderManager, originalResultTable);

        std::unordered_set<std::string> intersection = findIntersection(lhsValue, rhsValue);

        if (!isQuotedString(firstParam.getValue()) && !isInteger(firstParam.getValue())) {
            pair<string, string> attributes = extractAttributes(firstParam, parsingResult, pkbReaderManager);
            string synonym = attributes.first;
            // insert column with value of synonym and rows with the intersection of the two sets
            for (string elem : intersection) {
                resultTable->insertNewRow({ {synonym, elem} });
            }
        }
        if (!isQuotedString(secondParam.getValue()) && !isInteger(secondParam.getValue())) {
            pair<string, string> attributes = extractAttributes(firstParam, parsingResult, pkbReaderManager);
            string synonym = attributes.first;
            // insert column with value of synonym and rows with the intersection of the two sets
            for (string elem : intersection) {
                resultTable->insertNewRow({ {synonym, elem} });
            }
        }
        
	}
    return resultTable;

}


/**
 * Processes first parameter of the query.
 */
std::unordered_set<std::string> WithStrategy::processParam(Token param, const ParsingResult& parsingResult, PKBReaderManager& pkbReaderManager, std::shared_ptr<ResultTable>& resultTable) {
    // check if param.getValue() is an integer or a quoted string

    if (isInteger(param.getValue())) {
        //return vector of param.getValue()
        return {param.getValue()};
    }
    else if (isQuotedString(param.getValue())) {
        // Extracts the value within the quotes
        string extractedValue = param.getValue().substr(1, param.getValue().length() - 2);
        return {extractedValue};
	}
    else if (param.getType() == TokenType::Ref) {
        pair<string, string> attributes = extractAttributes(param, parsingResult, pkbReaderManager);
        string synonym = attributes.first;
        string attribute = attributes.second;
        string synonymType = parsingResult.getDeclaredSynonym(synonym);

        if (synonymType == "stmt") {
            if (attribute == "stmt#") {
				return resultTable->getColumnValues(synonym);
			}
		}
        else if (synonymType == "read") {
            if (attribute == "varName") {
				// use pkbReaderManager to get the variable name using the statement numbers found in the resultTable
			}
            else if (attribute == "stmt#") {
                return resultTable->getColumnValues(synonym);
			}
		}
        else if (synonymType == "print") {
            if (attribute == "varName") {
                // use pkbReaderManager to get the variable name using the statement numbers found in the resultTable
			}
            else if (attribute == "stmt#") {
                return resultTable->getColumnValues(synonym);
			}
		}
        else if (synonymType == "call") {
            if (attribute == "procName") {
                // use pkbReaderManager to get the set of procedure names using the statement numbers found in the resultTable
			}
            else if (attribute == "stmt#") {
                return resultTable->getColumnValues(synonym);
			}
		}
        else if (synonymType == "while") {
            if (attribute == "stmt#") {
                return resultTable->getColumnValues(synonym);
			}
		}
        else if (synonymType == "if") {
            if (attribute == "stmt#") {
                return resultTable->getColumnValues(synonym);
			}
		}
        else if (synonymType == "assign") {
            if (attribute == "stmt#") {
                return resultTable->getColumnValues(synonym);
			}
		}
        else if (synonymType == "variable") {
            if (attribute == "varName") {
                return resultTable->getColumnValues(synonym);
			}
		}
        else if (synonymType == "constant") {
            if (attribute == "value") {
                return resultTable->getColumnValues(synonym);
			}
		}
        else if (synonymType == "procedure") {
            if (attribute == "procName") {
                return resultTable->getColumnValues(synonym);
			}
		}
        
    }
    
    string col1 = firstParam.getValue();
    
    string firstStatementType = parsingResult.getDeclaredSynonym(firstParam.getValue());

    
}

/**
 * Extracts the synonym of the parameter and the attribute of the parameter which are split by a dot.
 */
pair<string, string> WithStrategy::extractAttributes(Token param, const ParsingResult& parsingResult, PKBReaderManager& pkbReaderManager)
{
    string paramValue = param.getValue();
	size_t dotPosition = paramValue.find(".");
	string synonym = paramValue.substr(0, dotPosition);
	string attribute = paramValue.substr(dotPosition + 1);
	return make_pair(synonym, attribute);
}

// Function to check if a string is an integer
bool WithStrategy::isInteger(const std::string& str) {
    return !str.empty() && std::all_of(str.begin(), str.end(), [](char c) { return std::isdigit(c); });
}

// Function to check if a string is a quoted string
bool WithStrategy::isQuotedString(const std::string& str) {
    return str.size() >= 2 && str.front() == '"' && str.back() == '"';
}

//function that finds the intersection of two unordered sets of strings efficiently
std::unordered_set<std::string> WithStrategy::findIntersection(const std::unordered_set<std::string>& set1, const std::unordered_set<std::string>& set2) {
    // Determine the smaller and the larger set
    const auto& smallerSet = (set1.size() < set2.size()) ? set1 : set2;
    const auto& largerSet = (set1.size() < set2.size()) ? set2 : set1;

    std::unordered_set<std::string> intersection;

    // Iterate through the smaller set and add elements to the intersection
    // if they are found in the larger set
    for (const auto& element : smallerSet) {
        if (largerSet.find(element) != largerSet.end()) {
            intersection.insert(element);
        }
    }

    return intersection;
}


}