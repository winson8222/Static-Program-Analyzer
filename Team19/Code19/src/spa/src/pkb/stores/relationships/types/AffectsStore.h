#pragma once

#include <memory>
#include <queue>

#include "pkb/stores/relationships/RelationshipStore.h"
#include "pkb/stores/entities/types/AssignStore.h"
#include "pkb/stores/relationships/types/NextStore.h"
#include "pkb/stores/relationships/types/UsesSStore.h"
#include "pkb/stores/relationships/types/ModifiesSStore.h"
#include "pkb/stores/entities/types/WhileStore.h"
#include "pkb/stores/entities/types/IfStore.h"
// ai-gen start(copilot, 2, e)
// prompt: used copilot
/**
 * @class AffectsStore
 * Specialization of RelationshipStore for 'Affects' relationships.
 * This store manages direct 'Affects' relationships where one statement
 * affects another in a SIMPLE program.
 *
 * Inherits all functionalities from RelationshipStore.
 * Template parameters are set to int, representing statement numbers.
 */
class AffectsStore: public RelationshipStore<int, int> {
    // This class instantiates a RelationshipStore
    // specific for the 'Affects' relationship between statements.
private:
    std::shared_ptr<AssignStore> assignStore;
    std::shared_ptr<NextStore> nextStore;
    std::shared_ptr<UsesSStore> usesSStore;
    std::shared_ptr<ModifiesSStore> modifiesSStore;
	std::shared_ptr<WhileStore> whileStore;
	std::shared_ptr<IfStore> ifStore;
public:
    AffectsStore(
		std::shared_ptr<AssignStore> assignStore,
		std::shared_ptr<NextStore> nextStore,
		std::shared_ptr<UsesSStore> usesSStore,
		std::shared_ptr<ModifiesSStore> modifiesSStore,
		std::shared_ptr<WhileStore> whileStore,
		std::shared_ptr<IfStore> ifStore
	);

    /**
     * Populate the AffectsStore with the 'Affects' relationship between statements.
     */
    void populateAffectsStore();

    /**
     * Populates the AffectsStore with the affects relationship for a given statement
     * @param statement
     */
    void populateAffectByStatement(int statement);

    /**
     * Adds the affects relationship between the given statement and the current statement if the current statement uses the assignedVariable.
     * @param statement The statement to add the affects relationship for
     * @param current The current statement to check for the affects relationship
     * @param assignedVariable The variable assigned by the statement
     * @return True if the current statement modifies the assignedVariable, false otherwise
     */
     bool handleAddAffects(int statement, int current, const std::string& assignedVariable);

     /**
     * Uses the queue to populate the AffectsStore with the affects relationship for a given statement.
     * The queue is used to perform a search on the next relationships of the given statement.
     * If the next statement modifies the assignedVariable, it's next relationships are not added to the queue.
     * @param statement The statement to populate the AffectsStore with
     * @param queue The queue to use for the search
     * @param assignedVariable The variable assigned by the statement
     */
     void populateFromQueue(int statement, std::queue<int>&, const std::string& assignedVariable);
};
// ai-gen end
