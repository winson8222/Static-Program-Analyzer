#pragma once

#include <string>
#include "pkb/stores/relationships/RelationshipStore.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
/**
 * @class NextStore
 * Manages "Next" relationships for statements in a SIMPLE program.
 * This store captures relationships where a particular statement (identified by number)
 * modifies a certain variable.
 *
 * Inherits from RelationshipStore<int, int> to provide functionality for managing
 * relationships between statements and the statements that they are next to.
 */
class NextStore : public RelationshipStore<int, int> {
};
// ai-gen end
