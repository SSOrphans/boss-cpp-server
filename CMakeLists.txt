cmake_minimum_required(VERSION 3.16.0)
project(cppserver VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find all required packages
find_package(Boost 1.77.0 EXACT QUIET MODULE REQUIRED)
find_package(gRPC 1.39.1 EXACT QUIET MODULE REQUIRED)
find_package(LibXml2 2.9.12 EXACT QUIET MODULE REQUIRED)

add_subdirectory(source)
# add_subdirectory(benchmarks)
# add_subdirectory(tests)
