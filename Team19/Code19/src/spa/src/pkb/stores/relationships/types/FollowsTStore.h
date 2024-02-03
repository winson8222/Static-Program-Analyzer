#pragma once

#include "pkb/stores/relationships/RelationshipStore.h"

/**
 * @class FollowsTStore
 * Specialization of RelationshipStore for transitive 'Follows*' relationships.
 * This store manages transitive 'Follows*' relationships where a statement
 * follows another either directly or through a series of statements in a SIMPLE program.
 *
 * Inherits all functionalities from RelationshipStore.
 * Template parameters are set to int, representing SIMPLE statement numbers.
 */
class FollowsTStore: public RelationshipStore<int, int> {
    // This class can be used to instantiate a RelationshipStore
    // specific for the 'Follows*' relationship between statements.
};
