#pragma once

#include "Grammar.h"
#include "StmtList.h"
#include <vector>
#include <string>

// ai-gen start(gpt,2,e)
// Prompt: https://platform.openai.com/playground/p/3mLKCsoXcgjIM0eMlvP3rIgb?model=gpt-4&mode=chat
class Procedure : public Grammar {
public:
    Procedure();

    void addStmtList(StmtList stmtList);
    void buildTree() const override;
    int getStartLine() const override;
    int getEndLine() const override;

private:
    std::vector<StmtList> statementLists;
    std::pair<int,int> lines;
};
// ai-gen end
