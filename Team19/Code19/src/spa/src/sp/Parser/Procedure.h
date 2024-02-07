#pragma once

#include "Grammar.h"
#include <string>

// ai-gen start(gpt,1,e)
// Prompt: https://platform.openai.com/playground/p/3mLKCsoXcgjIM0eMlvP3rIgb?model=gpt-4&mode=chat
class Procedure : public Grammar {
public:
    Procedure(const std::string& todo);

    int getStartLine() const override;
    int getEndLine() const override;
    void buildTree() const override;

private:
    std::string todo;
    std::pair<int,int> lines const override;
};
// ai-gen end