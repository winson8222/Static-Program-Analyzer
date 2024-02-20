#pragma once

#include <string>
#include "pkb/stores/relationships/RelationshipStore.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
/**
 * @class ModifiesPStore
 * Manages "Modifies" relationships for procedures in a SIMPLE program.
 * This store captures relationships where a procedure modifies a certain variable.
 *
 * Inherits from RelationshipStore<std::string, std::string> to provide
 * functionality for managing relationships between procedures (identified by name)
 * and the variables they modify.
 */
class ModifiesPStore : public RelationshipStore<std::string, std::string> {
    // Additional functionality specific to procedure-variable modifications can be added here
};
// ai-gen end
