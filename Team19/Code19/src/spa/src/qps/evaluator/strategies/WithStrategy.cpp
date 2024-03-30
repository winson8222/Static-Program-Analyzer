#include "qps/evaluator/strategies/WithStrategy.h"
#include "qps/parser/Token.h" // Include for Token definition
#include <map>

// Standard library dependencies


/**
 * Evaluates equality between 2 parameters.
 * Determines the relationship based on the parsing result and updates the result table accordingly.
 *
 * @param pkbReaderManager Provides access to the program knowledge base.
 * @param parsingResult Contains the parsed query details.
 * @return A shared pointer to the populated result table.
 */
std::shared_ptr<ResultTable> WithStrategy::evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult, const Clause& clause, const std::shared_ptr<ResultTable>& originalResultTable) {
        auto resultTable = std::make_shared<ResultTable>();
        // Initializing PKB readers for With clause
        const WithClause* withClause = dynamic_cast<const WithClause*>(&clause);
        this->firstParam = withClause->getFirstParam();
        this->secondParam = withClause->getSecondParam();
        this->parsingResult = parsingResult;
    
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
            std::unordered_set<std::string> lhsValue = processParam(firstParam, pkbReaderManager, originalResultTable);
            std::unordered_set<std::string> rhsValue = processParam(secondParam, pkbReaderManager, originalResultTable);
            std::vector<std::string> intersection = findIntersection(lhsValue, rhsValue);
            if (isAttrRef(firstParam) && isAttrRef(secondParam)) {
                populateWithIntersection(intersection, pkbReaderManager, resultTable, firstParam, secondParam);
            }
            else if (isAttrRef(firstParam)) {
                populateWithFirstParam(resultTable, pkbReaderManager, firstParam, secondParam);
            } else if (isAttrRef(secondParam)) {
                populateWithSecondParam(resultTable, pkbReaderManager, firstParam, secondParam);
            } else {
                if (!intersection.empty()) {
                    resultTable->setAsTruthTable();
                }
            }


             
        }
        return resultTable;
}

std::unordered_set<std::string> WithStrategy::retrieveIntStringLinks(std::string synonym, const std::shared_ptr<ResultTable>& resultTable, const std::shared_ptr<ILinkReader<int, std::string>> linkReader) {
    if (resultTable->hasColumn(synonym)) {
        std::unordered_set<std::string> callStmts = resultTable->getColumnValues(synonym);
        std::unordered_set<std::string> callProcNames;
        for (const std::string& stmt : callStmts) {
            callProcNames.insert(linkReader->getLinked(std::stoi(stmt)));
        }
        return callProcNames;
    }
    else {
        return linkReader->getAllLinked();
    }
}

std::unordered_set<std::string> WithStrategy::retrieveIntEntities(std::string synonym, const std::shared_ptr<ResultTable>& resultTable, const std::shared_ptr<IEntityReader<int>>& entityReader) {
    if (resultTable->hasColumn(synonym)) {
        return resultTable->getColumnValues(synonym);
    }
    else {
        unordered_set<int> list = entityReader->getAllEntities();
        unordered_set<string> entities;
        convertIntSetToStringSet(list, entities);
        return entities;
    }
}

std::unordered_set<std::string> WithStrategy::retrieveStringEntities(std::string synonym, const std::shared_ptr<ResultTable>& resultTable, const std::shared_ptr<IEntityReader<std::string>>& entityReader) {
    if (resultTable->hasColumn(synonym)) {
        return resultTable->getColumnValues(synonym);
    }
    else {
        return entityReader->getAllEntities();
    }
}

std::shared_ptr<ResultTable> WithStrategy::evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult, const Clause& clause) {
    return std::shared_ptr<ResultTable>();
}


/**
 * Processes first parameter of the query.
 */
std::unordered_set<std::string> WithStrategy::processParam(Token param, PKBReaderManager& pkbReaderManager, const std::shared_ptr<ResultTable>& resultTable) {
    // check if param.getValue() is an integer or a quoted string
    std::shared_ptr<ReadVarNameReader> readVarNameReader = pkbReaderManager.getReadVarNameReader();
    std::shared_ptr<PrintVarNameReader> printVarNameReader = pkbReaderManager.getPrintVarNameReader();
    std::shared_ptr<CallProcNameReader> callProcNameReader = pkbReaderManager.getCallProcNameReader();
    

    std::shared_ptr<StatementReader> statementReader = pkbReaderManager.getStatementReader();
    std::shared_ptr<ReadReader> readReader = pkbReaderManager.getReadReader();
    std::shared_ptr<PrintReader> printReader = pkbReaderManager.getPrintReader();
    std::shared_ptr<CallReader> callReader = pkbReaderManager.getCallReader();
    std::shared_ptr<WhileReader> whileReader = pkbReaderManager.getWhileReader();
    std::shared_ptr<IfReader> ifReader = pkbReaderManager.getIfReader();
    std::shared_ptr<AssignReader> assignReader = pkbReaderManager.getAssignReader();
    std::shared_ptr<VariableReader> variableReader = pkbReaderManager.getVariableReader();
    std::shared_ptr<ConstantReader> constantReader = pkbReaderManager.getConstantReader();
    std::shared_ptr<ProcedureReader> procedureReader = pkbReaderManager.getProcedureReader();

    if (isInteger(param.getValue())) {
        //return vector of param.getValue()
        return {param.getValue()};
    }
    else if (isQuotedString(param.getValue())) {
        // Extracts the value within the quotes
        size_t QUOTE_OFFSET = 1;
        size_t QUOTE_PAIR_LENGTH = 2;
        string extractedValue = param.getValue().substr(QUOTE_OFFSET, param.getValue().length() - QUOTE_PAIR_LENGTH);
        return {extractedValue};
	}
    else if (param.getType() == TokenType::Ref) {
        pair<string, string> attributes = extractAttributes(param);
        string synonym = attributes.first;
        string attribute = attributes.second;
        string synonymType = parsingResult.getDeclaredSynonym(synonym);

        if (synonymType == "stmt" && attribute == "stmt#") {
            return retrieveIntEntities(synonym, resultTable, statementReader);
		}
        else if (synonymType == "read" && attribute == "varName") {
            return retrieveIntStringLinks(synonym, resultTable, readVarNameReader);
		}
        else if (synonymType == "read" && attribute == "stmt#") {
            return retrieveIntEntities(synonym, resultTable, readReader);
		}
        else if (synonymType == "print" && attribute == "varName") {
            return retrieveIntStringLinks(synonym, resultTable, printVarNameReader);
		}
        else if (synonymType == "print" && attribute == "stmt#") {
            return retrieveIntEntities(synonym, resultTable, printReader);
		}
        else if (synonymType == "call" && attribute == "procName") {
            return retrieveIntStringLinks(synonym, resultTable, callProcNameReader);
        }
        else if (synonymType == "call" && attribute == "stmt#") {
            return retrieveIntEntities(synonym, resultTable, callReader);
		}
        else if (synonymType == "while" && attribute == "stmt#") {
            return retrieveIntEntities(synonym, resultTable, whileReader);
		}
        else if (synonymType == "if" && attribute == "stmt#") {
            return retrieveIntEntities(synonym, resultTable, ifReader);
		}
        else if (synonymType == "assign" && attribute == "stmt#") {
                return retrieveIntEntities(synonym, resultTable, assignReader);
		}
        else if (synonymType == "variable" && attribute == "varName") {
            return retrieveStringEntities(synonym, resultTable, variableReader);
		}
        else if (synonymType == "constant" && attribute == "value") {
            return retrieveIntEntities(synonym, resultTable, constantReader);
		}
        else if (synonymType == "procedure" && attribute == "procName") {
            return retrieveStringEntities(synonym, resultTable, procedureReader);
		}
    }
    return std::unordered_set<std::string>();
}

/**
 * Extracts the synonym of the parameter and the attribute of the parameter which are split by a dot.
 */
pair<string, string> WithStrategy::extractAttributes(Token param)
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
std::vector<std::string> WithStrategy::findIntersection(const std::unordered_set<std::string>& set1, const std::unordered_set<std::string>& set2) {
    // Determine the smaller and the larger set
    const auto& smallerSet = (set1.size() < set2.size()) ? set1 : set2;
    const auto& largerSet = (set1.size() < set2.size()) ? set2 : set1;

    std::vector<std::string> intersection;

    // Iterate through the smaller set and add elements to the intersection
    // if they are found in the larger set
    for (const auto& element : smallerSet) {
        if (largerSet.find(element) != largerSet.end()) {
            intersection.push_back(element);
        }
    }

    return intersection;
}

bool WithStrategy::isIntegerStored(string synyonymType, string attribute)
{
    if ((synyonymType == "read" || synyonymType == "print" || synyonymType == "call")
        && (attribute == "varName" || attribute == "procName"))
    {
        return true;
	}
    return false;
}

vector<std::string> WithStrategy::mapStringSetToIntSet(PKBReaderManager& pkbReaderManager, const vector<string>& stringSet, string& synonymType)
{
    // function that takes in the string set and retrieves all the linked statements for each string within the set
    // and returns a set of integers
    vector<int> intSet;
    if (synonymType == "read")
    {
		auto readVarNameReader = pkbReaderManager.getReadVarNameReader();
        for (string varName : stringSet)
        {
			unordered_set<int> linkedStmts = readVarNameReader->getLinker(varName);
            intSet.insert(intSet.end(), linkedStmts.begin(), linkedStmts.end());
            
		}
	}
    else if (synonymType == "print")
    {
		auto printVarNameReader = pkbReaderManager.getPrintVarNameReader();
        for (string varName : stringSet)
        {
			unordered_set<int> linkedStmts = printVarNameReader->getLinker(varName);
            intSet.insert(intSet.end(), linkedStmts.begin(), linkedStmts.end());
		}
	}
    else if (synonymType == "call")
    {
		auto callProcNameReader = pkbReaderManager.getCallProcNameReader();
        for (string procName : stringSet)
        {
			unordered_set<int> linkedStmts = callProcNameReader->getLinker(procName);
            intSet.insert(intSet.end(), linkedStmts.begin(), linkedStmts.end());
		}
	}
    vector<string> mappedIntSet;
    for (int i : intSet) {
        mappedIntSet.push_back(std::to_string(i));
    }
	return mappedIntSet;
}

//std::vector<pair<string, string>> WithStrategy::populateResultTable(
//    const std::shared_ptr<ResultTable>& resultTable,
//    const std::vector<std::string>& intersection, Token param, PKBReaderManager& pkbReaderManager)
//{
//    std::vector<pair<string, string>> rows;
//    if (!isQuotedString(param.getValue()) && !isInteger(param.getValue())) {
//
//        pair<string, string> attributes = extractAttributes(param);
//        string synonym = attributes.first;
//        string attribute = attributes.second;
//        string synonymType = parsingResult.getDeclaredSynonym(synonym);
//        if (!resultTable->hasColumn(synonym)) {
//            resultTable->insertColumn(synonym);
//        }
//        if (isIntegerStored(synonymType, attribute)) {
//            vector<string> mappedIntersection = mapStringSetToIntSet(pkbReaderManager, intersection, synonymType);
//            // insert column with value of synonym and rows with the intersection of the two sets
//            for (string elem : mappedIntersection) {
//                rows.push_back(make_pair(synonym, elem));
//            }
//        }
//        else {
//            for (string elem : intersection) {
//                rows.push_back(make_pair(synonym, elem));
//            }
//        }
//
//
//    }
//    return rows;
//}

std::string WithStrategy::getAttrRefType(const Token& token) {
    std::pair<std::string, std::string> attRef = extractAttributes(token);
    // concat the first and second together
    string synonymType = parsingResult.getDeclaredSynonym(attRef.first);
    return synonymType + "." + attRef.second;
}


void WithStrategy::populateWithIntersection(const std::vector<std::string>& intersection, PKBReaderManager& pkbReaderManager, const std::shared_ptr<ResultTable>& resultTable,
                                            const Token& firstParam, const Token& secondParam)
{
    if (intersection.empty()) {
        return;
    }
    std::string firstParamValue = firstParam.getValue();
    std::string secondParamValue = secondParam.getValue();
    if (firstParamValue == secondParamValue) {
        resultTable->setAsTruthTable();
        return;
    }
    std::pair<std::string, std::string> firstParamAttributes = extractAttributes(firstParam);
    std::pair<std::string, std::string> secondParamAttributes = extractAttributes(secondParam);
    std::string firstSynonym = firstParamAttributes.first;
    std::string secondSynonym = secondParamAttributes.first;
    resultTable->insertAllColumns({firstSynonym, secondSynonym});

    std::string firstAttrRefType = getAttrRefType(firstParam);
    std::string secondAttrRefType = getAttrRefType(secondParam);
    for (const std::string& attrValue : intersection) {
        std::unordered_set<std::string> allPossibleFirstParam;
        auto it = refToOriginalValueMap.find(firstAttrRefType);
        if (it != refToOriginalValueMap.end()) {
            // find all possible values of firstParam (non attr)
            allPossibleFirstParam = it->second(attrValue, pkbReaderManager);
        } else {
            continue;
        }

        std::unordered_set<std::string> allPossibleSecondParam;
        it = refToOriginalValueMap.find(secondAttrRefType);
        if (it != refToOriginalValueMap.end()) {
            // find all possible values of secondParam (non attr)
            allPossibleSecondParam = it->second(attrValue, pkbReaderManager);
        } else {
            continue;
        }

        // insert into result table
        for (const std::string& firstParamValue : allPossibleFirstParam) {
            for (const std::string& secondParamValue : allPossibleSecondParam) {
                std::pair<std::string, std::string> firstCol = {firstSynonym, firstParamValue};
                std::pair<std::string, std::string> secondCol = {secondSynonym, secondParamValue};
                QueryEvaluationStrategy::insertRowToTable(firstCol, secondCol, resultTable);
            }
        }
    }


}


void WithStrategy::populateWithFirstParam(const std::shared_ptr<ResultTable> &resultTable,
                                          PKBReaderManager &pkbReaderManager, const Token &firstParam,
                                          const Token &secondParam) {

    std::string firstParamValue = firstParam.getValue();

    std::string secondParamValue = extractQuotedExpression(secondParam);
    std::pair<std::string, std::string> firstParamAttributes = extractAttributes(firstParam);
    std::string firstSynonym = firstParamAttributes.first;
    std::string firstAttrRefType = getAttrRefType(firstParam);
    auto it = refToOriginalValueMap.find(firstAttrRefType);
    resultTable->insertColumn(firstSynonym);
    if (it != refToOriginalValueMap.end()) {
        std::unordered_set<std::string> allPossibleFirstParam = it->second(secondParamValue, pkbReaderManager);

        QueryEvaluationStrategy::insertRowsWithSingleColumn(firstSynonym, allPossibleFirstParam, resultTable);

    }

}

void WithStrategy::populateWithSecondParam(const std::shared_ptr<ResultTable> &resultTable,
                                           PKBReaderManager &pkbReaderManager, const Token &firstParam,
                                           const Token &secondParam) {
    std::string firstParamValue = extractQuotedExpression(firstParam);
    std::string secondParamValue = secondParam.getValue();
    std::pair<std::string, std::string> secondParamAttributes = extractAttributes(secondParam);
    std::string secondSynonym = secondParamAttributes.first;
    std::string secondAttrRefType = getAttrRefType(secondParam);
    auto it = refToOriginalValueMap.find(secondAttrRefType);
    resultTable->insertColumn(secondSynonym);
    if (it != refToOriginalValueMap.end()) {
        std::unordered_set<std::string> allPossibleSecondParam = it->second(firstParamValue, pkbReaderManager);
        QueryEvaluationStrategy::insertRowsWithSingleColumn(secondSynonym, allPossibleSecondParam, resultTable);
    }
}


bool WithStrategy::isAttrRef(Token token) {
    const std::string& value = token.getValue();
    return value.find('.') != std::string::npos;
}
