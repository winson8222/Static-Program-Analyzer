#include "Program.h"

// ai-gen start(gpt,1,e)
// Prompt: https://platform.openai.com/playground/p/3mLKCsoXcgjIM0eMlvP3rIgb?model=gpt-4&mode=chat
Program::Program() {}

void Program::addProcedure(Procedure p) {
    this->procedures.push_back(p);
}

std::vector<Procedure> Program::getProcedures() const {
    return this->procedures;
}

void Program::buildTree() {
    // build a Master root tree here, then populate all Procedures.
}
// ai-gen end