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
    explicit IExtractor(std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriterManager> pkbWriterManager)
		: root(root), pkbWriterManager(pkbWriterManager) {}

    virtual void extract(AssignNode& node) = 0;
    virtual void extract(ReadNode& node) = 0;
    virtual void extract(PrintNode& node) = 0;
    virtual void extract(CallNode& node) = 0;
    virtual void extract(WhileNode& node) = 0;
    virtual void extract(IfNode& node) = 0;
    virtual void extract(ProcedureNode& node) = 0;
    virtual void extract(StatementListNode& node) = 0;
    virtual void extract(VariableNode& node) = 0;
    virtual void extract(ConstantNode& node) = 0;
};