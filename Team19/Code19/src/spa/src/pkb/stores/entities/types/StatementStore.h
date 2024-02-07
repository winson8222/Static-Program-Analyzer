#pragma once

#include "pkb/stores/entities/EntityStore.h"

/**
 * @class StatementStore
 * Specialization of EntityStore for 'Statement' entity.
 * This store manages the collection of statement numbers in a SIMPLE program.
 *
 * Inherits all functionalities from EntityStore.
 * Template parameters are set to int, representing SIMPLE statement numbers.
 */
class StatementStore: public EntityStore<int> {
    // This class can be used to instantiate an EntityStore
    // specific for the 'Statement' Entity.
};
