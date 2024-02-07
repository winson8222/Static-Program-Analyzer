#include "Grammar.h"
#include <string>

// ai-gen start(gpt,1,e)
// Prompt: https://platform.openai.com/playground/p/3mLKCsoXcgjIM0eMlvP3rIgb?model=gpt-4&mode=chat
class Stmt : public Grammar {
public:
    Stmt(const std::string& stmtType);
    std::pair<int,int> lines;
    
    void buildTree() const override;

    int getStartLine() const override;
    int getEndLine() const override;

private:
    std::string stmtType;
};
// ai-gen end