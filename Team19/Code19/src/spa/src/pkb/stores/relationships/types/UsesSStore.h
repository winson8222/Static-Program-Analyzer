#pragma once

#include <string>
#include "pkb/stores/relationships/RelationshipStore.h"

/**
 * @class UsesSStore
 * Manages "Uses" relationships for statements in a SIMPLE program.
 * This store captures relationships where a particular statement (identified by number)
 * uses a certain variable.
 *
 * Inherits from RelationshipStore<int, std::string> to provide
 * functionality for managing relationships between statement numbers and variables.
 */
class UsesSStore : public RelationshipStore<int, std::string> {

};
