file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")
add_library(spa ${srcs} ${headers} "src/qps/Token.h" "src/qps/Token.cpp" "src/qps/Tokenizer.h" "src/qps/Tokenizer.cpp" "src/qps/QueryParser.h" "src/qps/QueryParser.cpp"
)
# this makes the headers accessible for other projects which uses spa lib
target_include_directories(spa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)


