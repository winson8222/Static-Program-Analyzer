#pragma once
// ai-gen start(gpt,1,e)
// Prompt: https://platform.openai.com/playground/p/3mLKCsoXcgjIM0eMlvP3rIgb?model=gpt-4&mode=chat
#include <utility> // Include necessary header for std::pair

// Define the Grammar class
class Grammar {
protected:
    // Virtual function returning a pair of integers
    std::pair<int, int> lines;

public:
    virtual ~Grammar() {} // Virtual destructor

    // Virtual function for building the tree
    virtual void buildTree() const = 0;

    virtual int getStartLine() const = 0;
    virtual int getEndLine() const = 0;

};
// ai-gen end