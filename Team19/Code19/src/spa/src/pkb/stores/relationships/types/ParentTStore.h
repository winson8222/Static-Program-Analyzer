#pragma once

#include "pkb/stores/relationships/RelationshipStore.h"

/**
 * @class ParentTStore
 * Specialization of RelationshipStore for transitive 'Parent*' relationships.
 * This store manages the 'Parent*' relationships where one statement
 * is nested within another statement, either directly or indirectly through
 * multiple levels of nesting in a SIMPLE program.
 *
 * Inherits all functionalities from RelationshipStore.
 * Template parameters are set to int, representing SIMPLE statement numbers.
 */
class ParentTStore : public RelationshipStore<int, int> {
    // This class can be used to instantiate a RelationshipStore
    // specific for the 'Parent*' relationship between statements.
};
