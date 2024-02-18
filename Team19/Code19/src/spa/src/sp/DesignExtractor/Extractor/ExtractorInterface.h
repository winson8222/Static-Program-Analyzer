#include <memory>
#include "sp/AST/ASTNode.h"
#include "pkb/PKBWriterManager.h"

class AssignNode;
class ReadNode;
class PrintNode;
class CallNode;
class WhileNode;
class IfNode;
class VariableNode;
class ConstantNode;
class ProcedureNode;
class StatementListNode;


class IExtractor {
public:
    virtual void extract(const std::shared_ptr<ASTNode>& node) = 0;
};