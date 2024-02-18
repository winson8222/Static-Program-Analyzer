#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "pkb/PKBWriterManager.h"
#include "sp/AST/ASTNode.h" // Assuming you have ASTNode defined in ASTNode.h

class DesignExtractor {
public:
	// Constructor taking in the root node of the AST
	std::shared_ptr<ASTNode> root;
	std::shared_ptr<PKBWriterManager> pkbWriterManager;
	explicit DesignExtractor(std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriterManager> pkbWriterManager);
	explicit DesignExtractor(std::shared_ptr<ASTNode> root);
	explicit DesignExtractor(std::shared_ptr<PKBWriterManager> pkbWriterManager);

	void extractAndPopulateAll();
};