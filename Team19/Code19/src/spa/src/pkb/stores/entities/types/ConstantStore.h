#pragma once

#include "pkb/stores/entities/EntityStore.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
/**
 * @class ConstantStore
 * Specialization of EntityStore for 'Constant' entity.
 * This store manages the collection of constants used in a SIMPLE program.
 *
 * Inherits all functionalities from EntityStore.
 * Template parameters are set to int, representing SIMPLE constants.
 */
class ConstantStore: public EntityStore<int> {
    // This class can be used to instantiate an EntityStore
    // specific for the 'Constant' Entity.
};
// ai-gen end
