////
//// Created by Winson Zheng on 18/2/24.
////
//#include "StmtEntStrategy.h"
//#ifndef SPA_MODIFIESSSTRATEGY_H
//#define SPA_MODIFIESSSTRATEGY_H
//
//
//class ModifiesSStrategy : public StmtEntStrategy{
//private:
//    std::shared_ptr<ModifiesReader> modifiesReader;
//    std::shared_ptr<StatementReader> statementReader;
//
//public:
//    ~ModifiesSStrategy() override = default;
//
//    void processFirstParam(const Token& secondParam, const string& variant,
//                           unordered_set<string>& result) override;
//
//    void processSecondParam(const Token& firstParam, const string& variant,
//                            unordered_set<string>& result) override;
//
//    void processBothParam(const Token& firstParam, const Token& secondParam,
//                          unordered_set<string>& result) override;
//
//    void processIntegerAndIdentParams(const Token& firstParam, const Token& secondParam,
//                                      unordered_set<string>& result) override;
//
//};
//
//
//#endif //SPA_MODIFIESSSTRATEGY_H
