#pragma once

#include <string>
#include "pkb/stores/relationships/RelationshipStore.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
/**
 * @class UsesPStore
 * Manages "Uses" relationships for procedures in a SIMPLE program.
 * This store captures relationships where a procedure uses a certain variable.
 *
 * Inherits from RelationshipStore<std::string, std::string> to provide
 * functionality for managing relationships between procedures (identified by name)
 * and the variables they use.
 */
class UsesPStore : public RelationshipStore<std::string, std::string> {

};
// ai-gen end
