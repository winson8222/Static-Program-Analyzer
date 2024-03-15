#pragma once

#include "pkb/stores/links/LinkStore.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
/**
 * @class ReadVarNameStore
 * Specialization of LinkStore for linking "Read" statement numbers to variable names read
 * in a SIMPLE program.
 * This store manages the collection of links between "Read" statement numbers and
 * their respective called variable names.
 *
 * Inherits all functionalities from LinkStore.
 * Template parameters are set to int and string, representing SIMPLE statement numbers and variable names.
 */
class ReadVarNameStore: public LinkStore<int, std::string> {
    // This class can be used to instantiate an LinkStore with the template parameters
    // set to int and string.
};
// ai-gen end
