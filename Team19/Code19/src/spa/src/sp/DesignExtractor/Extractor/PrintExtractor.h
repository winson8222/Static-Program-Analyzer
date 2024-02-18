#include "sp/DesignExtractor/Extractor/IExtractor.h"

class PrintExtractor : public IExtractor {
public:
	explicit PrintExtractor(std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriterManager> pkbWriterManager)
		: IExtractor(root, pkbWriterManager) {}

	void extract() override;
};