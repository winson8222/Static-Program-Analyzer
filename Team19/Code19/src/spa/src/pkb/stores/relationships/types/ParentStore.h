#pragma once

#include "pkb/stores/relationships/RelationshipStore.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
/**
 * @class ParentStore
 * Specialization of RelationshipStore for 'Parent' relationships.
 * This store manages the 'Parent' relationships where one statement
 * is directly nested within another statement in a SIMPLE program.
 *
 * Inherits all functionalities from RelationshipStore.
 * Template parameters are set to int, representing SIMPLE statement numbers.
 */
class ParentStore : public RelationshipStore<int, int> {
    // This class can be used to instantiate a RelationshipStore
    // specific for the 'Parent' relationship between statements.
};
// ai-gen end
