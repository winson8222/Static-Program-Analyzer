#pragma once

#include <string>
#include "pkb/stores/entities/EntityStore.h"

/**
 * @class VariableStore
 * Specialization of EntityStore for 'Variable' entity.
 * This store manages the collection of variable names in a SIMPLE program.
 *
 * Inherits all functionalities from EntityStore.
 * Template parameters are set to string, representing SIMPLE variable names.
 */
class VariableStore: public EntityStore<std::string> {
    // This class can be used to instantiate an EntityStore
    // specific for the 'Variable' Entity.
};
