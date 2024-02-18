#include "sp/DesignExtractor/Extractor/IExtractor.h"

class ModifiesExtractor : public IExtractor {
public:
	explicit ModifiesExtractor(std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriterManager> pkbWriterManager)
		: IExtractor(root, pkbWriterManager) {}

	void extract() override;
};