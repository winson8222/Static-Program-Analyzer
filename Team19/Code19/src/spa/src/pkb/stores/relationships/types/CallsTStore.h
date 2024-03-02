#pragma once

#include "pkb/stores/relationships/RelationshipStore.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
/**
 * @class CallsTStore
 * Specialization of RelationshipStore for 'Calls*' relationships.
 * This store manages both direct and indirect (transitive) 'Calls' relationships
 * between procedures in a SIMPLE program.
 *
 * Inherits all functionalities from RelationshipStore.
 * Template parameters are set to std::string, representing the names of SIMPLE procedures.
 */
class CallsTStore: public RelationshipStore<std::string, std::string> {
    // This class can be used to instantiate a RelationshipStore
    // specific for the 'Calls*' relationship between procedures.
};
// ai-gen end