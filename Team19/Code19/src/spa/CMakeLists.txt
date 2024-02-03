file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")
add_library(spa ${srcs} ${headers})
add_library(spa ${srcs} ${headers} "src/QPS/Token.h" "src/QPS/Token.cpp" "src/QPS/Tokenizer.h" "src/QPS/Tokenizer.cpp" "src/QPS/QueryParser.h" "src/QPS/QueryParser.cpp")
add_library(spa ${srcs} ${headers} "src/sp/DesignExtractor.cpp" "src/sp/Parser.cpp" "src/sp/Parser.h" "src/sp/TNode.cpp" "src/sp/Tokenizer.cpp" "src/sp/Utility.cpp")

# this makes the headers accessible for other projects which uses spa lib
target_include_directories(spa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)


