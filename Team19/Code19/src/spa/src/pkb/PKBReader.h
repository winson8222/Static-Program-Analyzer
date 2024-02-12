#pragma

#include <memory>

#include "PKB.h"

class PKBReader {
private:
    std::shared_ptr<PKB> pkb;

    std::shared_ptr<FollowsStore> followsStore;
    std::shared_ptr<FollowsTStore> followsTStore;

    std::shared_ptr<ParentStore> parentStore;
    std::shared_ptr<ParentTStore> parentTStore;

    std::shared_ptr<UsesPStore> usesPStore;
    std::shared_ptr<UsesSStore> usesSStore;

    std::shared_ptr<ModifiesPStore> modifiesPStore;
    std::shared_ptr<ModifiesSStore> modifiesSStore;

    std::shared_ptr<AssignStore> assignStore;
    std::shared_ptr<VariableStore> variableStore;
    std::shared_ptr<ConstantStore> constantStore;
    std::shared_ptr<ProcedureStore> procedureStore;
    std::shared_ptr<StatementStore> statementStore;
    std::shared_ptr<IfStore> ifStore;
    std::shared_ptr<WhileStore> whileStore;
    std::shared_ptr<CallStore> callStore;
    std::shared_ptr<ReadStore> readStore;
    std::shared_ptr<PrintStore> printStore;

public:
    explicit PKBReader(const std::shared_ptr<PKB>& pkb): pkb(pkb) {
        followsStore = pkb->getFollowsStore();
        followsTStore = pkb->getFollowsTStore();

        parentStore = pkb->getParentStore();
        parentTStore = pkb->getParentTStore();

        usesPStore = pkb->getUsesPStore();
        usesSStore = pkb->getUsesSStore();

        modifiesPStore = pkb->getModifiesPStore();
        modifiesSStore = pkb->getModifiesSStore();

        assignStore = pkb->getAssignStore();
        variableStore = pkb->getVariableStore();
        constantStore = pkb->getConstantStore();
        procedureStore = pkb->getProcedureStore();
        statementStore = pkb->getStatementStore();
        ifStore = pkb->getIfStore();
        whileStore = pkb->getWhileStore();
        callStore = pkb->getCallStore();
        readStore = pkb->getReadStore();
        printStore = pkb->getPrintStore();
    }
    // Relationships

    /**
     * @brief Gets the statement number of reversed "Follows" relationships of the given statement.
     * @param stmt: stmt in Follows(s1, stmt)
     * @return unordered_set<int>: The set of statement numbers of all s1 in Follows(s1, stmt)
     */
    std::unordered_set<int> getPreFollows(int stmt) {
      return followsStore->getRelationshipsByValue(stmt);
    }


    /**
     * @brief Gets the statement number of "Follows" relationships of the given statement.
     * @param stmt: stmt in Follows(stmt, s2)
     * @return unordered_set<int>: The set of statement numbers of all s2 in Follows(stmt, s2)
     */
    std::unordered_set<int> getPostFollows(int stmt) {
      return followsStore->getRelationshipsByKey(stmt);
    }

    /**
     * @brief Gets the post statement numbers of all "Follows" relationships.
     * @return unordered_set<int>: The set of statement numbers of s2 in Follows(s1, s2)
     */
    std::unordered_set<int> getAllPostFollows() {
      return followsStore->getValues();
    }

    /**
     * @brief Gets the preceding statement numbers of all "Follows" relationships.
     * @return unordered_set<int>: The set of statement numbers of s1 in Follows(s1, s2)
     */
    std::unordered_set<int> getAllPreFollows() {
      return followsStore->getKeys();
    }

    /**
     * @brief Gets the statement number of reversed "Follows*" relationships of the given statement.
     * @param stmt
     * @return unordered_set<int>: The set of statement number of all s1 in Follows*(s1, stmt)
     */
    std::unordered_set<int> getPreFollowsT(int stmt) {
      return followsTStore->getRelationshipsByValue(stmt);
    }

    /**
     * @brief Gets the statement number of "Follows*" relationships of the given statement.
     * @param stmt: stmt in Follows*(stmt, s2)
     * @return: The set of statement number of all s2 in Follows*(stmt, s2)
     */
    std::unordered_set<int> getPostFollowsT(int stmt) {
      return followsTStore->getRelationshipsByKey(stmt);
    }

    /**
     * @brief Gets the post statement numbers of all "Follows*" relationships.
     * @return unordered_set<int>: The set of statement numbers of s2 in Follows*(s1, s2)
     */
    std::unordered_set<int> getAllPostFollowsT() {
      return followsTStore->getValues();
    }

    /**
     * @brief Gets the preceding statement numbers of all "Follows*" relationships.
     * @return unordered_set<int>: The set of statement numbers of s1 in Follows*(s1, s2)
     */
    std::unordered_set<int> getAllPreFollowsT() {
      return followsTStore->getKeys();
    }

    // Entities

    /**
     * @brief Gets the statement number of all "Assign" entities.
     * @return unordered_set<int>: Statement number of all "Assign" entities.
     */
    std::unordered_set<int> getAllAssigns() {
        return assignStore->getAllEntities();
    }

    /**
     * @brief Gets the statement number of all "Variable" entities.
     * @return unordered_set<int>: Statement number of all "Variable" entities.
     */
    std::unordered_set<std::string> getAllVariables() {
        return variableStore->getAllEntities();
    }


    /**
     * @brief Gets all Statement numbers
     * @return unordered_set<int>: Statement number of all "Statement" entities.
     */
    std::unordered_set<int> getAllStmts() {
        return statementStore->getAllEntities();
    }

    /**
     * @brief Gets all procedure names
     */
    std::unordered_set<std::string> getAllProcedures() {
        return procedureStore->getAllEntities();
    }
};


