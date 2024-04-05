#pragma once

#include <memory>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include "pkb/stores/relationships/IRelationshipReader.h"
#include "pkb/stores/relationships/types/CallsTStore.h" // Assumes the existence of CallsTStore

// ai-gen start(copilot, 2, e)
// prompt: used copilot
/**
 * @class CallsTReader
 * @brief Reader for transitive 'Calls*' relationships, implementing the IRelationshipReader interface.
 *
 * This class facilitates querying operations for the transitive closure of calls relationships
 * between procedures, allowing to determine if a procedure indirectly calls another procedure
 * through a chain of direct calls.
 */
class CallsTReader : public IRelationshipReader<std::string, std::string> {
private:
    std::shared_ptr<CallsTStore> callsTStore; ///< Store for transitive Calls relationships.

public:
    /**
     * @brief ructs a CallsTReader with a specific CallsTStore.
     * @param store Shared pointer to a CallsTStore instance.
     */
    explicit CallsTReader(std::shared_ptr<CallsTStore> store);

    bool isEmpty() override;
    std::unordered_map<std::string, std::unordered_set<std::string>> getKeyValueRelationships() override;
    std::unordered_map<std::string, std::unordered_set<std::string>> getValueKeyRelationships() override;
    std::unordered_set<std::string> getKeys() override;
    std::unordered_set<std::string> getValues() override;
    std::unordered_set<std::string> getRelationshipsByKey(std::string key) override;
    std::unordered_set<std::string> getRelationshipsByValue( std::string value) override;
    bool hasRelationship( std::string key,  std::string value) override;
    int getSize() override;
    int getRelationshipCountByKey(std::string key) override;
    int getRelationshipCountByValue(std::string value) override;

    /**
     * Retrieves all procedures indirectly called by a given procedure.
     * @param key Name of the calling procedure.
     * @return A set containing names of all procedures indirectly called by the key.
     */
    std::unordered_set<std::string> getTransitivelyCalledProcedures( std::string key);

    /**
     * Retrieves all procedures that indirectly call a given procedure.
     * @param value Name of the called procedure.
     * @return A set containing names of all procedures that indirectly call the value.
     */
    std::unordered_set<std::string> getTransitiveCallersOfProcedure( std::string value);

    /**
     * Checks if a procedure indirectly calls another procedure through a chain of direct calls.
     * @param key Name of the calling procedure.
     * @param value Name of the potentially called procedure.
     * @return true if there is a transitive call chain from key to value, false otherwise.
     */
    bool isTransitiveCaller( std::string key,  std::string value);

    /**
     * Retrieves all procedures that indirectly call at least one other procedure.
     * @return A set containing names of all procedures that are transitive callers.
     */
    std::unordered_set<std::string> getAllTransitiveCallers();

    /**
     * Retrieves all procedures that are indirectly called by at least one other procedure.
     * @return A set containing names of all procedures that are transitive callees.
     */
    std::unordered_set<std::string> getAllTransitiveCallees();

    /**
     * Checks if a specific procedure indirectly calls any other procedure.
     * @param key Name of the procedure to check.
     * @return true if the specified procedure indirectly calls any procedure, false otherwise.
     */
    bool hasAnyTransitiveCalls( std::string key);

    /**
     * Checks if a specific procedure is indirectly called by any other procedure.
     * @param value Name of the procedure to check.
     * @return true if the specified procedure is indirectly called by any procedure, false otherwise.
     */
    bool isTransitiveCallee( std::string value);
};
// ai-gen end
