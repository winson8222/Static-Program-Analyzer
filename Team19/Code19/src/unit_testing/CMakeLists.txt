file(GLOB_RECURSE srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")
file(GLOB sp_files "${CMAKE_CURRENT_SOURCE_DIR}/src/sp/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/sp/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/sp/*.hpp")
add_executable(unit_testing ${srcs} ${headers} ${sp_files})


target_link_libraries(unit_testing spa)

