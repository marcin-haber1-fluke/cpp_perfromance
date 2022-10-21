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
        17_standard_algorithms.cpp
        18_projections_in_range_library.cpp
        19_data_structure_that_can_be_used_in_generic_algorithm.cpp
        20_ranges.cpp
        21_placement_new.cpp
        22_alignment.cpp
        # Commented due to error with multiple definition of operator new (same like in 27_optional.cpp)
        # 23_small_objects_optimization.cpp
        24_custom_memory_allocations.cpp
        25_consteval.cpp
        26_constraints_and_concepts.cpp
        27_optional.cpp
        28_tuple.cpp
        29_variadic_parameter_pack.cpp
        30_variants.cpp
        31_proxy_objects.cpp
        32_pipe_operator.cpp
        33_condition_variables.cpp
        34_barriers.cpp
        35_latches.cpp
        36_coroutines.cpp
        37_any.cpp
        38_semaphores.cpp

        37_any.cpp
)

find_package( GTest REQUIRED )

target_link_libraries(${PROJECT_NAME}
        PUBLIC
        /usr/local/lib/libgtest.so
        /usr/local/lib/libgtest_main.so
        /usr/local/lib/libgmock.so
        )