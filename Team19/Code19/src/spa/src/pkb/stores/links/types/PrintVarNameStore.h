#pragma once

#include <string>

#include "pkb/stores/links/LinkStore.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
/**
 * @brief PrintVarNameStore
 * Specialization of LinkStore for linking "Print" statement numbers to variable names print
 * in a SIMPLE program.
 * This store manages the collection of links between "Print" statement numbers and
 * their respective called variable names.
 *
 * Inherits all functionalities from LinkStore.
 * Template parameters are set to int and string, representing SIMPLE statement numbers and variable names.
 */
class PrintVarNameStore: public LinkStore<int, std::string> {
    // This class can be used to instantiate an LinkStore with the template parameters
    // set to int and string.
};
// ai-gen end
