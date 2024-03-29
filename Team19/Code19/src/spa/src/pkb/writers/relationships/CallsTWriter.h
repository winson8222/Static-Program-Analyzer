#pragma once

#include <memory>
#include <string>
#include "pkb/stores/relationships/IRelationshipWriter.h"
#include "pkb/stores/relationships/types/CallsTStore.h" // Assumes the existence of CallsTStore for transitive calls

// ai-gen start(copilot, 1, e)
// prompt: used copilot
/**
 * @class CallsTWriter
 * @brief Writer for 'Calls*' (transitive calls) relationships, implementing the IRelationshipWriter interface.
 *
 * This class provides functionality to add transitive calls relationships between procedures.
 */
class CallsTWriter : public IRelationshipWriter<std::string, std::string> {
private:
    std::shared_ptr<CallsTStore> callsTStore;

public:
    explicit CallsTWriter(std::shared_ptr<CallsTStore> store);

    void addRelationship( std::string caller,  std::string callee) override;
    void clear() override;

    /**
     * @brief Adds a transitive 'Calls*' relationship between two procedures.
     * @param caller The name of the calling procedure.
     * @param callee The name of the called procedure.
     */
    void addCallsT( std::string caller,  std::string callee);
};
// ai-gen end