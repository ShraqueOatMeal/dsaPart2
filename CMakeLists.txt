cmake_minimum_required(VERSION 3.12)
project(dsaPart2 VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the executable
add_executable(dsaPart2 src/main.cpp)

# If you later add a library, uncomment and modify these lines:
include_directories(${PROJECT_SOURCE_DIR}/include)
add_library(dsaPart2_lib src/bracket_stage.cpp src/game_log.cpp src/group_stage.cpp src/local_time.cpp src/qualifiers.cpp src/registration.cpp)
target_link_libraries(dsaPart2 PRIVATE dsaPart2_lib)

