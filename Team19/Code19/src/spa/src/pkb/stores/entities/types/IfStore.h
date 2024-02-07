#pragma once

#include "pkb/stores/entities/EntityStore.h"

/**
 * @class IfStore
 * Specialization of EntityStore for 'If' entity.
 * This store manages the collection of statement numbers in a SIMPLE program
 * that are of type 'If'.
 *
 * Inherits all functionalities from EntityStore.
 * Template parameters are set to int, representing SIMPLE statement numbers.
 */
class IfStore: public EntityStore<int> {
    // This class can be used to instantiate an EntityStore
    // specific for the 'If' Entity.
};
