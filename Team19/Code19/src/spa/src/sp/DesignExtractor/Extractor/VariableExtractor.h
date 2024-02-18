#include "sp/DesignExtractor/Extractor/IExtractor.h"

class VariableExtractor : public IExtractor {
public:
	explicit VariableExtractor(std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriterManager> pkbWriterManager)
		: IExtractor(root, pkbWriterManager) {}

	void extract() override;
};