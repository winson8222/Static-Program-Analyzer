file(GLOB_RECURSE srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")
file(GLOB_RECURSE sp_files "${CMAKE_CURRENT_SOURCE_DIR}/src/sp/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/sp/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/sp/*.hpp")
file(GLOB_RECURSE qps_files "${CMAKE_CURRENT_SOURCE_DIR}/src/qps/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/qps/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/qps/*.hpp")

add_executable(unit_testing ${srcs} ${headers} ${sp_files} ${qps_files}

target_link_libraries(unit_testing spa)