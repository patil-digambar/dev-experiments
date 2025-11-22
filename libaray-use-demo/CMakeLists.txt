cmake_minimum_required(VERSION 3.10)
project(libaray-use-demo)

set(CMAKE_CXX_STANDARD 17)

add_library(mylib_static STATIC
mylib_static/mylib_static.cpp
)

add_library(mylib_shared SHARED
mylib_shared/mylib_shared.cpp
)

find_package(fmt REQUIRED)

add_executable(libaray-use-demo src/main.cpp)

# Add include paths for both libraries
target_include_directories(libaray-use-demo PRIVATE
    ${CMAKE_SOURCE_DIR}/mylib_static
    ${CMAKE_SOURCE_DIR}/mylib_shared
)
target_link_libraries(libaray-use-demo PRIVATE fmt::fmt  mylib_static mylib_shared)
set_target_properties(libaray-use-demo PROPERTIES
    BUILD_WITH_INSTALL_RPATH TRUE
    INSTALL_RPATH "$ORIGIN/mylib_shared"
)