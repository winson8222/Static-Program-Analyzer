// Visitor Interface
class IASTVisitor {
public:
    virtual void visit(AssignNode& node) = 0;
    virtual void visit(ReadNode& node) = 0;
    // Add more visit methods for other node types as needed
    virtual ~IASTVisitor() = default;
};