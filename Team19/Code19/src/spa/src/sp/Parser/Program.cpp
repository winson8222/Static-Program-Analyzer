#include "Program.h"

// ai-gen start(gpt,1,e)
// Prompt: https://platform.openai.com/playground/p/3mLKCsoXcgjIM0eMlvP3rIgb?model=gpt-4&mode=chat
Program::Program() {}

void Program::addProcedure(Procedure procedure) {
    this->procedures.push_back(procedure);
}

int Program::getStartLine() const {
    return 0;
    // Do sth
}
      
int Program::getEndLine() const {
    return 0;
    // Do sth
}

std::shared_ptr<ASTNode> Program::buildTree() {
    // build a Master root tree here, then populate all Procedures.
    
    // **IMPORTANT** Placeholder implementation to avoid compilation error.
    std::shared_ptr<ASTNode> tree = std::make_shared<ASTNode>(
        ASTNodeType::ERROR, 0, "Program::buildTree() not implemented."
    );

    return tree;  
}
// ai-gen end
