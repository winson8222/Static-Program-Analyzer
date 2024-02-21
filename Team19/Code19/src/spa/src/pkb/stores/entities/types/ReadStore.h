#pragma once

#include "pkb/stores/entities/EntityStore.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
/**
 * @class ReadStore
 * Specialization of EntityStore for 'Read' entity.
 * This store manages the collection of statement numbers in a SIMPLE program
 * that are of type 'Read'.
 *
 * Inherits all functionalities from EntityStore.
 * Template parameters are set to int, representing SIMPLE statement numbers.
 */
class ReadStore: public EntityStore<int> {
    // This class can be used to instantiate an EntityStore
    // specific for the 'Read' Entity.
};
// ai-gen end
