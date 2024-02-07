#pragma once

#include "pkb/stores/entities/EntityStore.h"

using namespace std;

/**
 * @class ProcedureStore
 * Specialization of EntityStore for 'Procedure' entity.
 * This store manages the collection of procedures declared in a SIMPLE program.
 *
 * Inherits all functionalities from EntityStore.
 * Template parameters are set to string, representing SIMPLE procedure names.
 */
class ProcedureStore: public EntityStore<string> {
    // This class can be used to instantiate an EntityStore
    // specific for the 'Procedure' Entity.
};
