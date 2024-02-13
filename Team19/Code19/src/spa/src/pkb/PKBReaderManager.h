#pragma once

#include <memory>

#include "PKB.h"

#include "pkb/readers/entities/AssignReader.h"
#include "pkb/readers/entities/VariableReader.h"
#include "pkb/readers/entities/ProcedureReader.h"
#include "pkb/readers/entities/StatementReader.h"
#include "pkb/readers/entities/IfReader.h"
#include "pkb/readers/entities/WhileReader.h"
#include "pkb/readers/entities/CallReader.h"
#include "pkb/readers/entities/ReadReader.h"
#include "pkb/readers/entities/PrintReader.h"

class PKBReaderManager {
private:
    std::shared_ptr<PKB> pkb;

    std::shared_ptr<AssignReader> assignReader;
    std::shared_ptr<VariableReader> variableReader;
    std::shared_ptr<ProcedureReader> procedureReader;
    std::shared_ptr<StatementReader> statementReader;
    std::shared_ptr<IfReader> ifReader;
    std::shared_ptr<WhileReader> whileReader;
    std::shared_ptr<CallReader> callReader;
    std::shared_ptr<ReadReader> readReader;
    std::shared_ptr<PrintReader> printReader;

public:
    explicit PKBReaderManager(const std::shared_ptr<PKB>& pkb): pkb(pkb) {
      assignReader = std::make_shared<AssignReader>(pkb->getAssignStore());
      variableReader = std::make_shared<VariableReader>(pkb->getVariableStore());
      procedureReader = std::make_shared<ProcedureReader>(pkb->getProcedureStore());
      statementReader = std::make_shared<StatementReader>(pkb->getStatementStore());
      ifReader = std::make_shared<IfReader>(pkb->getIfStore());
      whileReader = std::make_shared<WhileReader>(pkb->getWhileStore());
      callReader = std::make_shared<CallReader>(pkb->getCallStore());
      readReader = std::make_shared<ReadReader>(pkb->getReadStore());
      printReader = std::make_shared<PrintReader>(pkb->getPrintStore());
    }

    std::shared_ptr<VariableReader> getVariableReader() {
        return variableReader;
    }

//    // Relationships
//
//    /**
//     * @brief Gets the statement number of reversed "Follows" relationships of the given statement.
//     * @param stmt: stmt in Follows(s1, stmt)
//     * @return unordered_set<int>: The set of statement numbers of all s1 in Follows(s1, stmt)
//     */
//    std::unordered_set<int> getPreFollows(int stmt) {
//      return followsStore->getRelationshipsByValue(stmt);
//    }
//
//    /**
//     * @brief Gets the statement number of "Follows" relationships of the given statement.
//     * @param stmt: stmt in Follows(stmt, s2)
//     * @return unordered_set<int>: The set of statement numbers of all s2 in Follows(stmt, s2)
//     */
//    std::unordered_set<int> getPostFollows(int stmt) {
//      return followsStore->getRelationshipsByKey(stmt);
//    }
//
//    /**
//     * @brief Gets the post statement numbers of all "Follows" relationships.
//     * @return unordered_set<int>: The set of statement numbers of s2 in Follows(s1, s2)
//     */
//    std::unordered_set<int> getAllPostFollows() {
//      return followsStore->getValues();
//    }
//
//    /**
//     * @brief Gets the preceding statement numbers of all "Follows" relationships.
//     * @return unordered_set<int>: The set of statement numbers of s1 in Follows(s1, s2)
//     */
//    std::unordered_set<int> getAllPreFollows() {
//      return followsStore->getKeys();
//    }
//
//    /**
//     * @brief Gets the statement number of reversed "Follows*" relationships of the given statement.
//     * @param stmt
//     * @return unordered_set<int>: The set of statement number of all s1 in Follows*(s1, stmt)
//     */
//    std::unordered_set<int> getPreFollowsT(int stmt) {
//      return followsTStore->getRelationshipsByValue(stmt);
//    }
//
//    /**
//     * @brief Gets the statement number of "Follows*" relationships of the given statement.
//     * @param stmt: stmt in Follows*(stmt, s2)
//     * @return: The set of statement number of all s2 in Follows*(stmt, s2)
//     */
//    std::unordered_set<int> getPostFollowsT(int stmt) {
//      return followsTStore->getRelationshipsByKey(stmt);
//    }
//
//    /**
//     * @brief Gets the post statement numbers of all "Follows*" relationships.
//     * @return unordered_set<int>: The set of statement numbers of s2 in Follows*(s1, s2)
//     */
//    std::unordered_set<int> getAllPostFollowsT() {
//      return followsTStore->getValues();
//    }
//
//    /**
//     * @brief Gets the preceding statement numbers of all "Follows*" relationships.
//     * @return unordered_set<int>: The set of statement numbers of s1 in Follows*(s1, s2)
//     */
//    std::unordered_set<int> getAllPreFollowsT() {
//      return followsTStore->getKeys();
//    }
//
//    // Entities
//
//    /**
//     * @brief Gets the statement number of all "Assign" entities.
//     * @return unordered_set<int>: Statement number of all "Assign" entities.
//     */
//    std::unordered_set<int> getAllAssigns() {
//        return assignStore->getAllEntities();
//    }
//
//    /**
//     * @brief Gets the statement number of all "Variable" entities.
//     * @return unordered_set<int>: Statement number of all "Variable" entities.
//     */
//    std::unordered_set<std::string> getAllVariables() {
//        return variableStore->getAllEntities();
//    }
};


