#pragma once

#include "pkb/stores/relationships/RelationshipStore.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
/**
 * @class CallsStore
 * Specialization of RelationshipStore for 'Calls' relationships.
 * This store manages direct 'Calls' relationships where one procedure
 * directly calls another in a SIMPLE program.
 *
 * Inherits all functionalities from RelationshipStore.
 * Template parameters are set to std::string, representing procedure names.
 */
class CallsStore: public RelationshipStore<std::string, std::string> {
    // This class instantiates a RelationshipStore
    // specific for the 'Calls' relationship between procedures.
};
// ai-gen end