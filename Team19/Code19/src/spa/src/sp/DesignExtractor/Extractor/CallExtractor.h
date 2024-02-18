class CallExtractor : public IExtractor {
public:
    void extract(const std::shared_ptr<ASTNode>& node) override;
};