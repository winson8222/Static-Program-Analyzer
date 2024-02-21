#pragma once

#include <string>
#include "pkb/stores/relationships/RelationshipStore.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
/**
 * @class ModifiesSStore
 * Manages "Modifies" relationships for statements in a SIMPLE program.
 * This store captures relationships where a particular statement (identified by number)
 * modifies a certain variable.
 *
 * Inherits from RelationshipStore<int, std::string> to provide
 * functionality for managing relationships between statement numbers and variables.
 */
class ModifiesSStore : public RelationshipStore<int, std::string> {
    // Additional functionality specific to statement-variable modifications can be added here
};
// ai-gen end
