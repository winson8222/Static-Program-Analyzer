#pragma once

#include "pkb/stores/entities/EntityStore.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
/**
 * @class CallStore
 * Specialization of EntityStore for 'Call' entity.
 * This store manages the collection of statement numbers in a SIMPLE program
 * that are of type 'Call'.
 *
 * Inherits all functionalities from EntityStore.
 * Template parameters are set to int, representing SIMPLE statement numbers.
 */
class CallStore: public EntityStore<int> {
    // This class can be used to instantiate an EntityStore
    // specific for the 'Call' Entity.
};
// ai-gen end
