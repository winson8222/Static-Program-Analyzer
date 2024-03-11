#pragma once

#include <memory>
#include <string>
#include "pkb/stores/relationships/IRelationshipWriter.h"
#include "pkb/stores/relationships/types/CallsStore.h"

// ai-gen start(copilot, 1, e)
// prompt: used copilot
/**
 * @class CallsWriter
 * @brief Writer for 'Calls' relationships, implementing the IRelationshipWriter interface.
 *
 * This class provides functionality to add direct calls relationships between procedures.
 */
class CallsWriter : public IRelationshipWriter<std::string, std::string> {
private:
    std::shared_ptr<CallsStore> callsStore;

public:
    CallsWriter(std::shared_ptr<CallsStore> store);

    void addRelationship( std::string caller,  std::string callee) override;
    void clear() override;

    /**
     * @brief Adds a direct 'Calls' relationship between two procedures.
     * @param caller The name of the calling procedure.
     * @param callee The name of the called procedure.
     */
    void addCalls( std::string caller,  std::string callee);
};
// ai-gen end