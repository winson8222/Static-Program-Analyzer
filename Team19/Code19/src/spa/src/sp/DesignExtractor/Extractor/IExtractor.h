class IExtractor {
public:
    virtual void extract(const std::shared_ptr<ASTNode>& node) = 0;
};