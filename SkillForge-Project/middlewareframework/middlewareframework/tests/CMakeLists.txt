cmake_minimum_required(VERSION 3.14)
project(MiddlewareFrameworkTests)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

# -------------------------------
# Google Test Integration
# -------------------------------
include(FetchContent)
enable_testing()

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)

# Add test executable explicitly with files
add_executable(AllTests
    core_tests/messagebus_test.cpp
    # Add new tests here explicitly
)

target_link_libraries(AllTests
    PRIVATE
        middlewarecore
        gtest_main
        pthread
        fmt::fmt
)
target_include_directories(AllTests PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

gtest_discover_tests(AllTests)
