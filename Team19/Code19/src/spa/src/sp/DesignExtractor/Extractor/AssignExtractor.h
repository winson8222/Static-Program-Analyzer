#include "ExtractorInterface.h"

class AssignExtractor : public IExtractor {
public:
    void extract(const std::shared_ptr<ASTNode>& node) override;
};