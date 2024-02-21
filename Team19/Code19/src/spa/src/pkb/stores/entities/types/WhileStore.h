#pragma once

#include "pkb/stores/entities/EntityStore.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
/**
 * @class WhileStore
 * Specialization of EntityStore for 'While' entity.
 * This store manages the collection of statement numbers in a SIMPLE program
 * that are of type 'While'.
 *
 * Inherits all functionalities from EntityStore.
 * Template parameters are set to int, representing SIMPLE statement numbers.
 */
class WhileStore: public EntityStore<int> {
    // This class can be used to instantiate an EntityStore
    // specific for the 'While' Entity.
};
// ai-gen end
