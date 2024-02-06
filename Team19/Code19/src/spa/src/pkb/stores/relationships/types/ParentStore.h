#pragma once

#include "pkb/stores/relationships/RelationshipStore.h"

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
