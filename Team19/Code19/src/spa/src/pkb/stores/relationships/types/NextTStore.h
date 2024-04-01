#pragma once

#include <string>
#include <unordered_set>
#include <unordered_map>
#include <memory>

#include "pkb/stores/relationships/RelationshipStore.h"
#include "pkb/stores/relationships/types/NextStore.h"
#include "pkb/stores/relationships/types/ParentTStore.h"
#include "pkb/stores/entities/types/WhileStore.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
/**
 * @class NextTStore
 * Manages "Next" relationships for statements in a SIMPLE program.
 * This store captures relationships where a particular statement (identified by number)
 * modifies a certain variable.
 *
 * Inherits from RelationshipStore<int, int> to provide functionality for managing
 * relationships between statements and the statements that they are next to.
 *
 * Due to the constraints of the project, this class is used only as a cache for the NextT relationships.
 * It is only populated during the NextT query and is cleared after the query is completed.
 */
class NextTStore : public RelationshipStore<int, int> {
private:
	std::shared_ptr<NextStore> nextStore;
	std::shared_ptr<WhileStore> whileStore;
	std::shared_ptr<ParentTStore> parentTStore;
	std::unordered_set<int> nextTPopulated;
	std::unordered_set<int> previousTPopulated;

    /**
     * Adds a relationship between two statements and adds the result to the given set.
     * @param stmt The statement number to add the relationship for.
     * @param result The set to add the result to.
     * @param set The set to add the relationship from.
     * @param reversed Whether to add the relationship in reverse.
     */
	void addRelationshipAndResult(int stmt, std::unordered_set<int>& result, const std::unordered_set<int>& set, bool reversed);

    /**
     * Adds a relationship between two statements.
     * @param stmt The statement number to add the relationship for.
     * @param set The set to add the relationship from.
     * @param reversed Whether to add the relationship in reverse.
     */
    void addRelationshipOnly(int stmt, const std::unordered_set<int>& set, bool reversed);
public:
	NextTStore(std::shared_ptr<NextStore> nextStore, std::shared_ptr<WhileStore> whileStore, std::shared_ptr<ParentTStore> parentTStore);

    /**
     * Checks if the previousT relationships for a given statement are populated.
     * @param stmt The statement number to check.
     * @return True if the previousT relationships are populated, false otherwise.
     */
	bool hasNextTPopulated(int stmt);

    /**
     * Checks if the nextT relationships for a given statement are populated.
     * @param stmt The statement number to check.
     * @return True if the nextT relationships are populated, false otherwise.
     */
	bool hasPreviousTPopulated(int stmt);

    /**
     * Populates the nextT relationships for a given statement.
     * @param stmt The statement number to populate nextT relationships for.
     */
	void logNextTAdded(int stmt);

    /**
     * Populates the previousT relationships for a given statement.
     * @param stmt The statement number to populate previousT relationships for.
     */
	void logPreviousTAdded(int stmt);


    /**
     * Populates and returns all nextT relationships for all statements in the given NextStore.
     * @param reversed Whether to get the nextT relationships in reverse.
     * @return The map of all nextT relationships for all statements in the given NextStore.
     */
	std::unordered_map<int, std::unordered_set<int>> populateAndGetEntireNextTStore(bool reversed);

	// Populate and get
    /**
     * Recursively populates and returns all nextT relationships for a given statement.
     * @param stmt The statement number to populate nextT relationships for.
     * @param visited The set of visited statements to prevent infinite recursion.
     * @return The set of all nextT relationships for the given statement.
     */
	std::unordered_set<int> populateAndGetNextT(int stmt, std::unordered_set<int> visited);

    /**
     * Recursively populates and returns all previousT relationships for a given statement.
     * @param stmt The statement number to populate previousT relationships for.
     * @param visited The set of visited statements to prevent infinite recursion.
     * @return The set of all previousT relationships for the given statement.
     */
	std::unordered_set<int> populateAndGetPreviousT(int stmt, std::unordered_set<int> visited);

    /**
     * Populates and returns all previousT relationships for all statements in the given NextStore.
     * @return The set of all previousT relationships for all statements in the given NextStore.
     */
	std::unordered_set<int> populateAndGetAllPreviousT();

    /**
     * Populates and returns all nextT relationships for all statements in the given NextStore.
     * @return The set of all nextT relationships for all statements in the given NextStore.
     */
	std::unordered_set<int> populateAndGetAllNextT();

    // Populate only
    /**
     * Populates all nextT relationships for all statements in the given NextStore.
     * @param visited The set of visited statements to prevent infinite recursion.
     */
    void populateAllNextT();

    /**
     * Populates all previousT relationships for all statements in the given NextStore.
     * @param visited The set of visited statements to prevent infinite recursion.
     */
    void populateAllPreviousT();

    /**
     * Populates all NextT relationships for the given statement
     * @param stmt The statement number to populate nextT relationships for.
     * @param visited The set of visited statements to prevent infinite recursion.
     */
    void populateNextT(int stmt, std::unordered_set<int> visited);

    /**
     * Populates all previousT relationships for the given statement
     * @param stmt The statement number to populate previousT relationships for.
     * @param visited The set of visited statements to prevent infinite recursion.
     */
    void populatePreviousT(int stmt, std::unordered_set<int> visited);

	// Get only
    /**
     * Gets the nextT relationships for a given statement.
     * @param stmt The statement number to get the nextT relationships for.
     * @return The set of nextT relationships for the given statement.
     */
	std::unordered_set<int> getNextT(int stmt);

    /**
     * Gets the previousT relationships for a given statement.
     * @param stmt The statement number to get the previousT relationships for.
     * @return The set of previousT relationships for the given statement.
     */
	std::unordered_set<int> getPreviousT(int stmt);

    /**
     * Gets all previousT relationships for all statements.
     * @return The set of all previousT relationships for all statements.
     */
	std::unordered_set<int> getAllPreviousT();

    /**
     * Gets all nextT relationships for all statements.
     * @return The set of all nextT relationships for all statements.
     */
	std::unordered_set<int> getAllNextT();

    /**
     * Populates the entire NextTStore with the nextT relationships from the given NextStore.
     * @return true if the entire NextTStore is populated, false otherwise.
     */
	bool populateNextTStore();
    
    /**
     * Clears the store of all relationships.
     */
	void clear() override;
};
// ai-gen end
