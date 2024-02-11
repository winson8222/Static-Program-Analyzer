#pragma

#include "PKB.h"
#include "pkb/writers/VariableWriter.h"

class PKBWriterManager {
private:
    std::shared_ptr<PKB> pkb;
//    std::shared_ptr<FollowsStore> followsStore;
//    std::shared_ptr<FollowsTStore> followsTStore;
//
//    std::shared_ptr<ParentStore> parentStore;
//    std::shared_ptr<ParentTStore> parentTStore;
//
//    std::shared_ptr<UsesPStore> usesPStore;
//    std::shared_ptr<UsesSStore> usesSStore;
//
//    std::shared_ptr<ModifiesPStore> modifiesPStore;
//    std::shared_ptr<ModifiesSStore> modifiesSStore;
//
//    std::shared_ptr<AssignStore> assignStore;
//    std::shared_ptr<VariableStore> variableStore;
//    std::shared_ptr<ConstantStore> constantStore;
//    std::shared_ptr<ProcedureStore> procedureStore;
//    std::shared_ptr<StatementStore> statementStore;
//    std::shared_ptr<IfStore> ifStore;
//    std::shared_ptr<WhileStore> whileStore;
//    std::shared_ptr<CallStore> callStore;
//    std::shared_ptr<ReadStore> readStore;
//    std::shared_ptr<PrintStore> printStore;

    std::shared_ptr<VariableWriter> variableWriter;

public:
    explicit PKBWriterManager(const std::shared_ptr<PKB>& pkb): pkb(pkb) {
//      followsStore = pkb->getFollowsStore();
//      followsTStore = pkb->getFollowsTStore();
//      parentStore = pkb->getParentStore();
//      parentTStore = pkb->getParentTStore();
//
//      usesPStore = pkb->getUsesPStore();
//      usesSStore = pkb->getUsesSStore();
//
//      modifiesPStore = pkb->getModifiesPStore();
//      modifiesSStore = pkb->getModifiesSStore();
//
//      assignStore = pkb->getAssignStore();
//      variableStore = pkb->getVariableStore();
//      constantStore = pkb->getConstantStore();
//      procedureStore = pkb->getProcedureStore();
//      statementStore = pkb->getStatementStore();
//      ifStore = pkb->getIfStore();
//      whileStore = pkb->getWhileStore();
//      callStore = pkb->getCallStore();
//      readStore = pkb->getReadStore();
//      printStore = pkb->getPrintStore();

      variableWriter = std::make_shared<VariableWriter>(pkb->getVariableStore());
    }
    // Entities
    std::shared_ptr<VariableWriter> getVariableWriter() {
      return variableWriter;
    }
//    /**
//     * @brief Inserts a "Constant" entity into the PKB.
//     * @param constant: The integer value of the constant.
//     */
//    void insertConstant(int &constant) {
//      constantStore->addEntity(constant);
//    }
//
//    /**
//     * @brief Inserts a "Variable" Entity into the PKB.
//     * @param variable: The name of the variable.
//     */
//    void insertVariable(std::string &variable) {
//      variableStore->addEntity(variable);
//    }
//
//    /**
//     * @brief Inserts a "Procedure" Entity into the PKB.
//     * @param procedure: The name of the procedure.
//     */
//    void insertProcedure(std::string &procedure) {
//      procedureStore->addEntity(procedure);
//    }
//
//    /**
//     * @brief Inserts a "Statement" Entity into the PKB.
//     * @param stmtNum: The statement number.
//     */
//    void insertStatement(int &stmtNum) {
//      statementStore->addEntity(stmtNum);
//    }
//
//    /**
//     * @brief Inserts an "If" Entity into the PKB.
//     * @param stmtNum: The statement number of the "If" Entity.
//     */
//    void insertIf(int &stmtNum) {
//      ifStore->addEntity(stmtNum);
//    }
//
//    /**
//     * @brief Inserts a "While" Entity into the PKB.
//     * @param stmtNum: The statement number of the "While" Entity.
//     */
//    void insertWhile(int &stmtNum) {
//      whileStore->addEntity(stmtNum);
//    }
//
//    /**
//     * @brief Inserts a "Call" Entity into the PKB.
//     * @param stmtNum: The statement number of the "Call" Entity.
//     */
//    void insertCall(int &stmtNum) {
//      callStore->addEntity(stmtNum);
//    }
//
//    /**
//     * @brief Inserts an "Assign" Entity into the PKB.
//     * @param stmtNum: The statement number of the "Assign" Entity.
//     */
//    void insertAssign(int &stmtNum) {
//      assignStore->addEntity(stmtNum);
//    }
//
//    /**
//     * @brief Inserts a "Read" Entity into the PKB.
//     * @param stmtNum: The statement number of the "Read" Entity.
//     */
//    void insertRead(int &stmtNum) {
//      readStore->addEntity(stmtNum);
//    }
//
//    /**
//     * @brief Inserts a "Print" Entity into the PKB.
//     * @param stmtNum: The statement number of the "Print" Entity.
//     */
//    void insertPrint(int &stmtNum) {
//      printStore->addEntity(stmtNum);
//    }
//
//    // Relationships
//    /**
//     * @brief Inserts a Follows relationship "Follows(stmt1, stmt2)".
//     * @param stmt1: The statement number of the preceding statement.
//     * @param stmt2: The statement number of the following statement.
//     */
//    void insertFollows(int &stmt1, int &stmt2) {
//      followsStore->addRelationship(stmt1, stmt2);
//    }
//
//    /**
//     * @brief Inserts a Follows* relationship "Follows*(stmt1, stmt2)".
//     * @param stmt1: The statement number of the transitively preceding statement.
//     * @param stmt2: The statement number of the transitively following statement.
//     */
//    void insertFollowsT(int &stmt1, int &stmt2) {
//      followsTStore->addRelationship(stmt1, stmt2);
//    }
//
//    /**
//     * @brief Inserts a Parent relationship "Parent(stmt1, stmt2)".
//     * @param stmt1: The statement number of the parent statement.
//     * @param stmt2: The statement number of the child statement.
//     */
//    void insertParent(int &stmt1, int &stmt2) {
//       parentStore->addRelationship(stmt1, stmt2);
//    }
//
//    /**
//     * @brief Inserts a Parent* relationship "Parent*(stmt1, stmt2)".
//     * @param stmt1: The statement number of the transitively parent statement.
//     * @param stmt2: The statement number of the transitively child statement.
//     */
//    void insertParentT(int &stmt1, int &stmt2) {
//      parentTStore->addRelationship(stmt1, stmt2);
//    }
//
//    /**
//     * @brief Inserts a UsesP relationship "UsesP(procedure, variable)".
//     * @param procedure: The name of the procedure.
//     * @param variable: The name of the "Used" variable.
//     */
//    void insertUsesP(std::string &procedure, std::string &variable) {
//      usesPStore->addRelationship(procedure, variable);
//    }
//
//    /**
//     * @brief Inserts a UsesS relationship "UsesS(stmt, variable)".
//     * @param stmt: The statement number.
//     * @param variable: The name of the "Used" variable.
//     */
//    void insertUsesS(int &stmt, std::string &variable) {
//      usesSStore->addRelationship(stmt, variable);
//    }
//
//    /**
//     * @brief Inserts a ModifiesP relationship "ModifiesP(procedure, variable)".
//     * @param procedure: The name of the procedure.
//     * @param variable: The name of "Modified" variable.
//     */
//    void insertModifiesP(std::string &procedure, std::string &variable) {
//      modifiesPStore->addRelationship(procedure, variable);
//    }
//
//    /**
//     * @brief Inserts a ModifiesS relationship "ModifiesS(stmt, variable)".
//     * @param stmt: The statement number.
//     * @param variable: The name of the "Modified" variable.
//     */
//    void insertModifiesS(int &stmt, std::string &variable) {
//      modifiesSStore->addRelationship(stmt, variable);
//    }
//
//    void clear() {
//      followsStore->clear();
//      followsTStore->clear();
//      parentStore->clear();
//      parentTStore->clear();
//      usesPStore->clear();
//      usesSStore->clear();
//      modifiesPStore->clear();
//      modifiesSStore->clear();
//      assignStore->clear();
//      variableStore->clear();
//      constantStore->clear();
//      procedureStore->clear();
//      statementStore->clear();
//      ifStore->clear();
//      whileStore->clear();
//      callStore->clear();
//      readStore->clear();
//      printStore->clear();
//    }
};


