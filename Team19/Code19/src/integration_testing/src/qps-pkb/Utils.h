#pragma once

#include "utility"

#include "pkb/PKBManager.h"
#include "qps/evaluator/QueryEvaluator.h"
#include "qps/parser/QueryParser.h"
#include "sp/SourceProcessor.h"

class Utils {

public:
    static std::unordered_set<std::string> getResultsFromQuery(const std::string& query, std::shared_ptr<PKBReaderManager> pkbReaderManager, std::shared_ptr<PKBCacheManager> pkbCacheManager);
};
