#include "Grammar.h"
#include "../LexicalTokenType.h"
#include <string>

// ai-gen start(gpt,2,e)
// Prompt: https://platform.openai.com/playground/p/3mLKCsoXcgjIM0eMlvP3rIgb?model=gpt-4&mode=chat
class Stmt : public Grammar {
public:
    Stmt();
    
    void buildTree() const;
    int getStartLine() const;
    int getEndLine() const;

private:
    LexicalTokenType tokenType;
    std::pair<int,int> lines;
};
// ai-gen end