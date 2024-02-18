#include "sp/DesignExtractor/Extractor/IExtractor.h"

class UsesExtractor : public IExtractor {
public:
	explicit UsesExtractor(std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriterManager> pkbWriterManager)
		: IExtractor(root, pkbWriterManager) {}

	void extract() override;
};