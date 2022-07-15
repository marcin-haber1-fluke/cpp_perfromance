cmake_minimum_required(VERSION 3.21)
project(cpp_perfromance CXX)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} main.cpp)

target_sources( ${PROJECT_NAME}
        PRIVATE
        1_deduction_auto.cpp
        2_const_and_mutable_reference.cpp
        3_rule_of_five.cpp
        5_pass_by_value.cpp
        7_lambda_as_function_pointer.cpp
        8_lambda_types.cpp
        10_generic_lambdas.cpp
)

find_package( GTest REQUIRED )

target_link_libraries(${PROJECT_NAME}
        PUBLIC
        /usr/local/lib/libgtest.so
        /usr/local/lib/libgtest_main.so
        /usr/local/lib/libgmock.so
        )