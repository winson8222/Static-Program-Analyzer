#pragma once

#include "Stmt.h"
#include "sp/SPTokenizer/LexicalToken.h"
#include <string>

// ai-gen start(gpt,2,e)
// Prompt: https://platform.openai.com/playground/p/3mLKCsoXcgjIM0eMlvP3rIgb?model=gpt-4&mode=chat
class PrintStmt : public Stmt {
public:
    PrintStmt(const LexicalToken& variable, int start, int end);

    std::shared_ptr<ASTNode> buildTree() override;
    int getStartLine() const override;
    int getEndLine() const override;

private:
    LexicalToken variable;
    std::pair<int, int> lines;
};
// ai-gen end