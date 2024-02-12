#pragma once

#include "Grammar.h"
#include "CallStmt.h"
#include <vector>

class StmtList : public Grammar {
public:
    StmtList();

    void addStmt(std::shared_ptr<Stmt> stmt);

    std::shared_ptr<ASTNode> buildTree() override;
    int getStartLine() const override;
    int getEndLine() const override;

private:
    std::vector<std::shared_ptr<Stmt>> statements;
    std::pair<int, int> lines;
};
