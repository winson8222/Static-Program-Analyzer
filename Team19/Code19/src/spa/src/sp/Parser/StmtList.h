#include "Grammar.h"
#include "Stmt.h"
#include <vector>

class StmtList : public Grammar {
public:
    StmtList();

    void addStmt(Stmt stmt);

    void buildTree() const override;
    int getStartLine() const override;
    int getEndLine() const override;

private:
    std::vector<Stmt> statements;
    std::pair<int, int> lines;
};
