#pragma once

#include "Procedure.h"
#include "Grammar.h"
#include <vector>
// ai-gen start(gpt,1,e)
// Prompt: https://platform.openai.com/playground/p/3mLKCsoXcgjIM0eMlvP3rIgb?model=gpt-4&mode=chat
class Program : public Grammar {
public:
    Program();
    std::pair<int,int> lines;
    void addProcedure(Procedure p);
    std::vector<Procedure> getProcedures() const;
    void buildTree() {};

private:
    std::vector<Procedure> procedures;
};
// ai-gen end