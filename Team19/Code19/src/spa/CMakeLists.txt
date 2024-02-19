file(GLOB_RECURSE srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")
file(GLOB_RECURSE sp_files "${CMAKE_CURRENT_SOURCE_DIR}/src/sp/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/sp/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/sp/*.hpp")
file(GLOB_RECURSE qps_files "${CMAKE_CURRENT_SOURCE_DIR}/src/qps/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/qps/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/qps/*.hpp")

add_library(spa ${srcs} ${headers} ${sp_files} ${qps_files}
        src/qps/evaluator/suchThatStrategies/SuchThatStrategy.cpp
        src/qps/evaluator/suchThatStrategies/SuchThatStrategy.h
        src/qps/evaluator/suchThatStrategies/StmtStmtStrategy.cpp
        src/qps/evaluator/suchThatStrategies/StmtStmtStrategy.h
        src/qps/evaluator/suchThatStrategies/ParentStrategy.cpp
        src/qps/evaluator/suchThatStrategies/ParentStrategy.h
        src/qps/evaluator/suchThatStrategies/UsesSStrategy.cpp
        src/qps/evaluator/suchThatStrategies/UsesSStrategy.h
        src/qps/evaluator/suchThatStrategies/UsesPStrategy.cpp
        src/qps/evaluator/suchThatStrategies/UsesPStrategy.h
        src/qps/evaluator/suchThatStrategies/ModifiesSStrategy.cpp
        src/qps/evaluator/suchThatStrategies/ModifiesSStrategy.h
        src/qps/evaluator/suchThatStrategies/ModifiesPStrategy.cpp
        src/qps/evaluator/suchThatStrategies/ModifiesPStrategy.h
        src/qps/evaluator/suchThatStrategies/StmtEntStrategy.cpp
        src/qps/evaluator/suchThatStrategies/StmtEntStrategy.h
        src/qps/evaluator/ResultTable.cpp
        src/qps/evaluator/ResultTable.h
)

# this makes the headers accessible for other projects which uses spa lib
target_include_directories(spa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
