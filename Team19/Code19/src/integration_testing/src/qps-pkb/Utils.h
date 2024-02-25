#pragma once

#include "utility"

#include "pkb/PKBManager.h"
#include "qps/Evaluator/QueryEvaluator.h"
#include "qps/Parser/QueryParser.h"
#include "sp/SourceProcessor.h"

class Utils {

public:
    static unordered_set<std::string> getResultsFromQuery(const string& query, std::shared_ptr<PKBReaderManager> pkbReaderManager);
};
