#pragma once

#include "pkb/stores/relationships/RelationshipStore.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
/**
 * @class FollowsStore
 * Specialization of RelationshipStore for 'Follows' relationships.
 * This store manages direct 'Follows' relationships where one statement
 * directly follows another in a SIMPLE program.
 *
 * Inherits all functionalities from RelationshipStore.
 * Template parameters are set to int, representing SIMPLE statement numbers.
 */
class FollowsStore: public RelationshipStore<int, int> {
    // This class can be used to instantiate a RelationshipStore
    // specific for the 'Follows' relationship between statements.
};
// ai-gen end

