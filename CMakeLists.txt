cmake_minimum_required(VERSION 3.0.0)

cmake_policy(VERSION 3.0.0)

project("bantam")

file(GLOB_RECURSE PRJ_HEADERFILES include/*.h)
file(GLOB_RECURSE PRJ_SOURCEFILES src/*.cpp)

add_executable(bantam ${PRJ_HEADERFILES} ${PRJ_SOURCEFILES})
set_target_properties(bantam PROPERTIES CXX_STANDARD 11)
target_include_directories(bantam PRIVATE "${CMAKE_SOURCE_DIR}/include")
