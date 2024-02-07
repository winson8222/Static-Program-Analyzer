#include "Grammar.h"
#include <string>

// ai-gen start(gpt,2,e)
// Prompt: https://platform.openai.com/playground/p/3mLKCsoXcgjIM0eMlvP3rIgb?model=gpt-4&mode=chat
class Stmt : public Grammar {
public:
    Stmt();
    
    void buildTree() const override;
    int getStartLine() const override;
    int getEndLine() const override;

private:
    std::string stmtType;
    std::pair<int,int> lines;
};
// ai-gen end