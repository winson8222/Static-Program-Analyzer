#pragma once

#include <memory>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include "pkb/stores/relationships/IRelationshipReader.h"
#include "pkb/stores/relationships/types/CallsStore.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
/**
 * @class CallsReader
 * Reader for 'Calls' relationships, implementing the IRelationshipReader interface.
 * Manages reading operations for direct calls between procedures.
 */
class CallsReader : public IRelationshipReader<std::string, std::string> {
private:
    std::shared_ptr<CallsStore> callsStore;

public:
    explicit CallsReader(std::shared_ptr<CallsStore> store);

    bool isEmpty() override;
    std::unordered_map<std::string, std::unordered_set<std::string>> getKeyValueRelationships() override;
    std::unordered_map<std::string, std::unordered_set<std::string>> getValueKeyRelationships() override;
    std::unordered_set<std::string> getKeys() override;
    std::unordered_set<std::string> getValues() override;
    std::unordered_set<std::string> getRelationshipsByKey(std::string key) override;
    std::unordered_set<std::string> getRelationshipsByValue(std::string value) override;
    bool hasRelationship(std::string caller,std::string callee) override;
    int getSize() override;
    int getRelationshipCountByKey(std::string key) override;
    int getRelationshipCountByValue(std::string value) override;

    /**
     * Retrieves all procedures directly called by a given procedure.
     *
     * @param caller The name of the calling procedure.
     * @return A set containing the names of all procedures directly called by the specified caller.
     */
        std::unordered_set<std::string> getDirectlyCalledProcedures(std::string caller);

    /**
     * Retrieves all procedures that directly call a given procedure.
     *
     * @param callee The name of the called procedure.
     * @return A set containing the names of all procedures that directly call the specified callee.
     */
        std::unordered_set<std::string> getDirectCallersOfProcedure(std::string callee);

    /**
     * Checks if a procedure directly calls another procedure.
     *
     * @param caller The name of the calling procedure.
     * @param callee The name of the potentially called procedure.
     * @return true if the caller directly calls the callee, false otherwise.
     */
        bool isDirectCaller(std::string caller, std::string callee);

    /**
     * Retrieves all procedures that directly call at least one other procedure.
     *
     * @return A set containing the names of all procedures that are direct callers.
     */
        std::unordered_set<std::string> getAllDirectCallers();

    /**
     * Retrieves all procedures that are directly called by at least one other procedure.
     *
     * @return A set containing the names of all procedures that are direct callees.
     */
        std::unordered_set<std::string> getAllDirectCallees();

    /**
     * Checks if a specific procedure directly calls any other procedure.
     *
     * @param caller The name of the procedure to check.
     * @return true if the specified procedure directly calls any procedure, false otherwise.
     */
        bool hasAnyDirectCalls(std::string caller);

    /**
     * Checks if a specific procedure is directly called by any other procedure.
     *
     * @param callee The name of the procedure to check.
     * @return true if the specified procedure is directly called by any procedure, false otherwise.
     */
        bool isDirectCallee(std::string callee);

};
// ai-gen end