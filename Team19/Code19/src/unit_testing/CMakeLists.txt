<<<<<<< HEAD
file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")
add_executable(unit_testing ${srcs}  "src/TestTokenizer.cpp"
        src/TestQueryParser.cpp)
=======
file(GLOB_RECURSE srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")
file(GLOB sp_files "${CMAKE_CURRENT_SOURCE_DIR}/src/sp/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/sp/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/sp/*.hpp")
add_executable(unit_testing ${srcs} ${headers} ${sp_files})

>>>>>>> b62271ef7f6799d4bc9ce7dc29e990389673ae17

target_link_libraries(unit_testing spa)

