cmake_minimum_required(VERSION 3.21)
project(benchmarks CXX)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} 13_unordered_sets_and_maps.cpp)

find_package(benchmark REQUIRED)

target_sources( ${PROJECT_NAME}
        PRIVATE
        )

target_link_libraries(${PROJECT_NAME}
        PUBLIC
        /usr/local/lib/libgtest.so
        /usr/local/lib/libgtest_main.so
        /usr/local/lib/libgmock.so
        benchmark::benchmark /usr/lib/x86_64-linux-gnu/librt.a
        )