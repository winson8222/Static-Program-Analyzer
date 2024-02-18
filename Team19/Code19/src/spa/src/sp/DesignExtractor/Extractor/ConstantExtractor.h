#include "sp/DesignExtractor/Extractor/IExtractor.h"

class ConstantExtractor : public IExtractor {
public:
	explicit ConstantExtractor(std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriterManager> pkbWriterManager)
		: IExtractor(root, pkbWriterManager) {}

	void extract() override;
};