#include "sp/DesignExtractor/Extractor/RelationshipExtractor/IRelationshipExtractor.h"
#include "sp/ControlFlow/CFGNode.h"

/*
* This class is used to extract the Next relationship between two CFGNodes
* It will call the NextWriter to write the relationship to the PKB
* The Next relationship is a directed edge from cfgnode1 to cfgnode2
* This class is inherits from ICFGExtractor with methods taking from it
*/
class NextExtractor : public ICFGExtractor {
public:
	NextExtractor(std::shared_ptr<CFGNode> cfgnode1,
		std::shared_ptr<CFGNode> cfgnode2,
		std::shared_ptr<NextWriter> nextWriter);
	void extract();

private:
	std::shared_ptr<NextWriter> nextWriter;
};