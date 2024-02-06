
file(GLOB_RECURSE srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")
file(GLOB_RECURSE sp_files "${CMAKE_CURRENT_SOURCE_DIR}/src/sp/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/sp/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/sp/*.hpp")
add_library(spa ${srcs} ${headers} ${sp_files} "src/QPS/Token.h" "src/QPS/Token.cpp" "src/QPS/Tokenizer.h" "src/QPS/Tokenizer.cpp" "src/QPS/QueryParser.h" "src/QPS/QueryParser.cpp")

# this makes the headers accessible for other projects which uses spa lib
target_include_directories(spa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
