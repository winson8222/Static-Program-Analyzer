#pragma once

#include <string>

#include "pkb/stores/links/LinkStore.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
/**
 * @class CallProcNameStore
 * Specialization of LinkStore for linking "Call" statement numbers to procedure names called
 * in a SIMPLE program.
 * This store manages the collection of links between "Call" statement numbers and
 * their respective called procedure names.
 *
 * Inherits all functionalities from LinkStore.
 * Template parameters are set to int and string, representing SIMPLE statement numbers and procedure names.
 */
class CallProcNameStore: public LinkStore<int, std::string> {
    // This class can be used to instantiate an LinkStore with the template parameters
    // set to int and string.
};
// ai-gen end
